
#ifndef ENVOY_EXTENSIONS_UPSTREAMS_HTTP_V3_HTTP_PROTOCOL_OPTIONS_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_UPSTREAMS_HTTP_V3_HTTP_PROTOCOL_OPTIONS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/upstreams/http/v3/http_protocol_options.upb_minitable.h"

#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/protocol.upb_minitable.h"
#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions { upb_Message UPB_PRIVATE(base); } envoy_extensions_upstreams_http_v3_HttpProtocolOptions;
typedef struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig;
typedef struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig;
typedef struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig { upb_Message UPB_PRIVATE(base); } envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig;
struct envoy_config_core_v3_AlternateProtocolsCacheOptions;
struct envoy_config_core_v3_Http1ProtocolOptions;
struct envoy_config_core_v3_Http2ProtocolOptions;
struct envoy_config_core_v3_Http3ProtocolOptions;
struct envoy_config_core_v3_HttpProtocolOptions;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_config_core_v3_UpstreamHttpProtocolOptions;
struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter;

UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_new(upb_Arena* arena) {
  return (envoy_extensions_upstreams_http_v3_HttpProtocolOptions*)_upb_Message_New(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions_msg_init, arena);
}
UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions* ret = envoy_extensions_upstreams_http_v3_HttpProtocolOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions* ret = envoy_extensions_upstreams_http_v3_HttpProtocolOptions_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_serialize(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_serialize_ex(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_upstream_protocol_options_explicit_http_config = 3,
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_upstream_protocol_options_use_downstream_protocol_config = 4,
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_upstream_protocol_options_auto_config = 5,
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_upstream_protocol_options_NOT_SET = 0
} envoy_extensions_upstreams_http_v3_HttpProtocolOptions_upstream_protocol_options_oneofcases;
UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_upstream_protocol_options_oneofcases envoy_extensions_upstreams_http_v3_HttpProtocolOptions_upstream_protocol_options_case(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_upstreams_http_v3_HttpProtocolOptions_upstream_protocol_options_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_clear_upstream_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions_msg_init, &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_clear_common_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HttpProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_common_http_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const struct envoy_config_core_v3_HttpProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_HttpProtocolOptions* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HttpProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_has_common_http_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_clear_upstream_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_UpstreamHttpProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_upstream_http_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const struct envoy_config_core_v3_UpstreamHttpProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_UpstreamHttpProtocolOptions* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__UpstreamHttpProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_has_upstream_http_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_clear_explicit_http_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_explicit_http_config(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* default_val = NULL;
  const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_has_explicit_http_config(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_clear_use_downstream_protocol_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_use_downstream_protocol_config(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* default_val = NULL;
  const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_has_use_downstream_protocol_config(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_clear_auto_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_auto_config(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* default_val = NULL;
  const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_has_auto_config(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_clear_http_filters(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 32), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* const* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_http_filters(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 32), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_upstreams_http_v3_HttpProtocolOptions_http_filters_upb_array(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 32), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_upstreams_http_v3_HttpProtocolOptions_http_filters_mutable_upb_array(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 32), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_clear_header_validation_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 40), 66, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_header_validation_config(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(24, 40), 66, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_has_header_validation_config(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 40), 66, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_common_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions *msg, struct envoy_config_core_v3_HttpProtocolOptions* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HttpProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HttpProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_mutable_common_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HttpProtocolOptions* sub = (struct envoy_config_core_v3_HttpProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_common_http_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HttpProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__HttpProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_common_http_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_upstream_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions *msg, struct envoy_config_core_v3_UpstreamHttpProtocolOptions* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__UpstreamHttpProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_UpstreamHttpProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_mutable_upstream_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_UpstreamHttpProtocolOptions* sub = (struct envoy_config_core_v3_UpstreamHttpProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_upstream_http_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_UpstreamHttpProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__UpstreamHttpProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_upstream_http_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_explicit_http_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions *msg, envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_mutable_explicit_http_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, upb_Arena* arena) {
  struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* sub = (struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_explicit_http_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig*)_upb_Message_New(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_explicit_http_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_use_downstream_protocol_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions *msg, envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_mutable_use_downstream_protocol_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, upb_Arena* arena) {
  struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* sub = (struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_use_downstream_protocol_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig*)_upb_Message_New(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_use_downstream_protocol_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_auto_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions *msg, envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(32, 48), UPB_SIZE(-29, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_mutable_auto_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, upb_Arena* arena) {
  struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* sub = (struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_auto_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig*)_upb_Message_New(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_auto_config(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter** envoy_extensions_upstreams_http_v3_HttpProtocolOptions_mutable_http_filters(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 32), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter** envoy_extensions_upstreams_http_v3_HttpProtocolOptions_resize_http_filters(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 32), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_add_http_filters(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 32), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter* sub = (struct envoy_extensions_filters_network_http_connection_manager_v3_HttpFilter*)_upb_Message_New(&envoy__extensions__filters__network__http_0connection_0manager__v3__HttpFilter_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_header_validation_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 40), 66, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_mutable_header_validation_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_header_validation_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_set_header_validation_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_new(upb_Arena* arena) {
  return (envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig*)_upb_Message_New(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* ret = envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* ret = envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_serialize(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_serialize_ex(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_protocol_config_http_protocol_options = 1,
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_protocol_config_http2_protocol_options = 2,
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_protocol_config_http3_protocol_options = 3,
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_protocol_config_NOT_SET = 0
} envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_protocol_config_oneofcases;
UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_protocol_config_oneofcases envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_protocol_config_case(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_protocol_config_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_clear_protocol_config(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__ExplicitHttpConfig_msg_init, &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_clear_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http1ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_http_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const struct envoy_config_core_v3_Http1ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http1ProtocolOptions* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http1ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_has_http_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_clear_http2_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http2ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_http2_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const struct envoy_config_core_v3_Http2ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http2ProtocolOptions* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http2ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_has_http2_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_clear_http3_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http3ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_http3_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const struct envoy_config_core_v3_Http3ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http3ProtocolOptions* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http3ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_has_http3_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_set_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig *msg, struct envoy_config_core_v3_Http1ProtocolOptions* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http1ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http1ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_mutable_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http1ProtocolOptions* sub = (struct envoy_config_core_v3_Http1ProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_http_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http1ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http1ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_set_http_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_set_http2_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig *msg, struct envoy_config_core_v3_Http2ProtocolOptions* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http2ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http2ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_mutable_http2_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http2ProtocolOptions* sub = (struct envoy_config_core_v3_Http2ProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_http2_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http2ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http2ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_set_http2_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_set_http3_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig *msg, struct envoy_config_core_v3_Http3ProtocolOptions* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http3ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http3ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_mutable_http3_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http3ProtocolOptions* sub = (struct envoy_config_core_v3_Http3ProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_http3_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http3ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http3ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_ExplicitHttpConfig_set_http3_protocol_options(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_new(upb_Arena* arena) {
  return (envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig*)_upb_Message_New(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* ret = envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* ret = envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_serialize(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_serialize_ex(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__UseDownstreamHttpConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_clear_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http1ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_http_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg) {
  const struct envoy_config_core_v3_Http1ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http1ProtocolOptions* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http1ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_has_http_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_clear_http2_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http2ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_http2_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg) {
  const struct envoy_config_core_v3_Http2ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http2ProtocolOptions* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http2ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_has_http2_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_clear_http3_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http3ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_http3_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg) {
  const struct envoy_config_core_v3_Http3ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http3ProtocolOptions* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http3ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_has_http3_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_set_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig *msg, struct envoy_config_core_v3_Http1ProtocolOptions* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http1ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http1ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_mutable_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http1ProtocolOptions* sub = (struct envoy_config_core_v3_Http1ProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_http_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http1ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http1ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_set_http_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_set_http2_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig *msg, struct envoy_config_core_v3_Http2ProtocolOptions* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http2ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http2ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_mutable_http2_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http2ProtocolOptions* sub = (struct envoy_config_core_v3_Http2ProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_http2_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http2ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http2ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_set_http2_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_set_http3_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig *msg, struct envoy_config_core_v3_Http3ProtocolOptions* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http3ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http3ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_mutable_http3_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http3ProtocolOptions* sub = (struct envoy_config_core_v3_Http3ProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_http3_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http3ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http3ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_UseDownstreamHttpConfig_set_http3_protocol_options(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_new(upb_Arena* arena) {
  return (envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig*)_upb_Message_New(&envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init, arena);
}
UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* ret = envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* ret = envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_serialize(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_serialize_ex(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__upstreams__http__v3__HttpProtocolOptions__AutoHttpConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_clear_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http1ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_http_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const struct envoy_config_core_v3_Http1ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http1ProtocolOptions* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http1ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_has_http_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_clear_http2_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http2ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_http2_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const struct envoy_config_core_v3_Http2ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http2ProtocolOptions* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http2ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_has_http2_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_clear_http3_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Http3ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_http3_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const struct envoy_config_core_v3_Http3ProtocolOptions* default_val = NULL;
  const struct envoy_config_core_v3_Http3ProtocolOptions* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http3ProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_has_http3_protocol_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_clear_alternate_protocols_cache_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_AlternateProtocolsCacheOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_alternate_protocols_cache_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const struct envoy_config_core_v3_AlternateProtocolsCacheOptions* default_val = NULL;
  const struct envoy_config_core_v3_AlternateProtocolsCacheOptions* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__AlternateProtocolsCacheOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_has_alternate_protocols_cache_options(const envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_set_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig *msg, struct envoy_config_core_v3_Http1ProtocolOptions* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http1ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http1ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_mutable_http_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http1ProtocolOptions* sub = (struct envoy_config_core_v3_Http1ProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_http_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http1ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http1ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_set_http_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_set_http2_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig *msg, struct envoy_config_core_v3_Http2ProtocolOptions* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http2ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http2ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_mutable_http2_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http2ProtocolOptions* sub = (struct envoy_config_core_v3_Http2ProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_http2_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http2ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http2ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_set_http2_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_set_http3_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig *msg, struct envoy_config_core_v3_Http3ProtocolOptions* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Http3ProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Http3ProtocolOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_mutable_http3_protocol_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Http3ProtocolOptions* sub = (struct envoy_config_core_v3_Http3ProtocolOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_http3_protocol_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Http3ProtocolOptions*)_upb_Message_New(&envoy__config__core__v3__Http3ProtocolOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_set_http3_protocol_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_set_alternate_protocols_cache_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig *msg, struct envoy_config_core_v3_AlternateProtocolsCacheOptions* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__AlternateProtocolsCacheOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_AlternateProtocolsCacheOptions* envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_mutable_alternate_protocols_cache_options(envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_AlternateProtocolsCacheOptions* sub = (struct envoy_config_core_v3_AlternateProtocolsCacheOptions*)envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_alternate_protocols_cache_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_AlternateProtocolsCacheOptions*)_upb_Message_New(&envoy__config__core__v3__AlternateProtocolsCacheOptions_msg_init, arena);
    if (sub) envoy_extensions_upstreams_http_v3_HttpProtocolOptions_AutoHttpConfig_set_alternate_protocols_cache_options(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
