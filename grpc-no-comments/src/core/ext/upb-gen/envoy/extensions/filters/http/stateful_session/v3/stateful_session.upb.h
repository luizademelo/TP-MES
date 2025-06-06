
#ifndef ENVOY_EXTENSIONS_FILTERS_HTTP_STATEFUL_SESSION_V3_STATEFUL_SESSION_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_FILTERS_HTTP_STATEFUL_SESSION_V3_STATEFUL_SESSION_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/filters/http/stateful_session/v3/stateful_session.upb_minitable.h"

#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_filters_http_stateful_session_v3_StatefulSession { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_stateful_session_v3_StatefulSession;
typedef struct envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute;
struct envoy_config_core_v3_TypedExtensionConfig;

UPB_INLINE envoy_extensions_filters_http_stateful_session_v3_StatefulSession* envoy_extensions_filters_http_stateful_session_v3_StatefulSession_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_stateful_session_v3_StatefulSession*)_upb_Message_New(&envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_stateful_session_v3_StatefulSession* envoy_extensions_filters_http_stateful_session_v3_StatefulSession_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_stateful_session_v3_StatefulSession* ret = envoy_extensions_filters_http_stateful_session_v3_StatefulSession_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_stateful_session_v3_StatefulSession* envoy_extensions_filters_http_stateful_session_v3_StatefulSession_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_stateful_session_v3_StatefulSession* ret = envoy_extensions_filters_http_stateful_session_v3_StatefulSession_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_stateful_session_v3_StatefulSession_serialize(const envoy_extensions_filters_http_stateful_session_v3_StatefulSession* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_stateful_session_v3_StatefulSession_serialize_ex(const envoy_extensions_filters_http_stateful_session_v3_StatefulSession* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_http_stateful_session_v3_StatefulSession_clear_session_state(envoy_extensions_filters_http_stateful_session_v3_StatefulSession* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_filters_http_stateful_session_v3_StatefulSession_session_state(const envoy_extensions_filters_http_stateful_session_v3_StatefulSession* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_stateful_session_v3_StatefulSession_has_session_state(const envoy_extensions_filters_http_stateful_session_v3_StatefulSession* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_stateful_session_v3_StatefulSession_clear_strict(envoy_extensions_filters_http_stateful_session_v3_StatefulSession* msg) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_http_stateful_session_v3_StatefulSession_strict(const envoy_extensions_filters_http_stateful_session_v3_StatefulSession* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_extensions_filters_http_stateful_session_v3_StatefulSession_set_session_state(envoy_extensions_filters_http_stateful_session_v3_StatefulSession *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_extensions_filters_http_stateful_session_v3_StatefulSession_mutable_session_state(envoy_extensions_filters_http_stateful_session_v3_StatefulSession* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_extensions_filters_http_stateful_session_v3_StatefulSession_session_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_extensions_filters_http_stateful_session_v3_StatefulSession_set_session_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_stateful_session_v3_StatefulSession_set_strict(envoy_extensions_filters_http_stateful_session_v3_StatefulSession *msg, bool value) {
  const upb_MiniTableField field = {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute*)_upb_Message_New(&envoy__extensions__filters__http__stateful_0session__v3__StatefulSessionPerRoute_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* ret = envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__stateful_0session__v3__StatefulSessionPerRoute_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* ret = envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__stateful_0session__v3__StatefulSessionPerRoute_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_serialize(const envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__stateful_0session__v3__StatefulSessionPerRoute_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_serialize_ex(const envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__stateful_0session__v3__StatefulSessionPerRoute_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_override_disabled = 1,
  envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_override_stateful_session = 2,
  envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_override_NOT_SET = 0
} envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_override_oneofcases;
UPB_INLINE envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_override_oneofcases envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_override_case(const envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_override_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_clear_override(envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__filters__http__stateful_0session__v3__StatefulSessionPerRoute_msg_init, &field);
}
UPB_INLINE void envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_clear_disabled(envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_disabled(const envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_has_disabled(const envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_clear_stateful_session(envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_http_stateful_session_v3_StatefulSession* envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_stateful_session(const envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg) {
  const envoy_extensions_filters_http_stateful_session_v3_StatefulSession* default_val = NULL;
  const envoy_extensions_filters_http_stateful_session_v3_StatefulSession* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_has_stateful_session(const envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_set_disabled(envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute *msg, bool value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_set_stateful_session(envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute *msg, envoy_extensions_filters_http_stateful_session_v3_StatefulSession* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_http_stateful_session_v3_StatefulSession* envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_mutable_stateful_session(envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_http_stateful_session_v3_StatefulSession* sub = (struct envoy_extensions_filters_http_stateful_session_v3_StatefulSession*)envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_stateful_session(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_http_stateful_session_v3_StatefulSession*)_upb_Message_New(&envoy__extensions__filters__http__stateful_0session__v3__StatefulSession_msg_init, arena);
    if (sub) envoy_extensions_filters_http_stateful_session_v3_StatefulSessionPerRoute_set_stateful_session(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
