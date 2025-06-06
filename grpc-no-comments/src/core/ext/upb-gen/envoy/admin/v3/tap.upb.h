
#ifndef ENVOY_ADMIN_V3_TAP_PROTO_UPB_H__UPB_H_
#define ENVOY_ADMIN_V3_TAP_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/admin/v3/tap.upb_minitable.h"

#include "envoy/config/tap/v3/common.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_admin_v3_TapRequest { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_TapRequest;
struct envoy_config_tap_v3_TapConfig;

UPB_INLINE envoy_admin_v3_TapRequest* envoy_admin_v3_TapRequest_new(upb_Arena* arena) {
  return (envoy_admin_v3_TapRequest*)_upb_Message_New(&envoy__admin__v3__TapRequest_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_TapRequest* envoy_admin_v3_TapRequest_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_TapRequest* ret = envoy_admin_v3_TapRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__TapRequest_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_TapRequest* envoy_admin_v3_TapRequest_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_TapRequest* ret = envoy_admin_v3_TapRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__TapRequest_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_TapRequest_serialize(const envoy_admin_v3_TapRequest* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__TapRequest_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_TapRequest_serialize_ex(const envoy_admin_v3_TapRequest* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__TapRequest_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_TapRequest_clear_config_id(envoy_admin_v3_TapRequest* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_TapRequest_config_id(const envoy_admin_v3_TapRequest* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_TapRequest_clear_tap_config(envoy_admin_v3_TapRequest* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_tap_v3_TapConfig* envoy_admin_v3_TapRequest_tap_config(const envoy_admin_v3_TapRequest* msg) {
  const struct envoy_config_tap_v3_TapConfig* default_val = NULL;
  const struct envoy_config_tap_v3_TapConfig* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__tap__v3__TapConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_TapRequest_has_tap_config(const envoy_admin_v3_TapRequest* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_TapRequest_set_config_id(envoy_admin_v3_TapRequest *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_TapRequest_set_tap_config(envoy_admin_v3_TapRequest *msg, struct envoy_config_tap_v3_TapConfig* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__tap__v3__TapConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_tap_v3_TapConfig* envoy_admin_v3_TapRequest_mutable_tap_config(envoy_admin_v3_TapRequest* msg, upb_Arena* arena) {
  struct envoy_config_tap_v3_TapConfig* sub = (struct envoy_config_tap_v3_TapConfig*)envoy_admin_v3_TapRequest_tap_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_tap_v3_TapConfig*)_upb_Message_New(&envoy__config__tap__v3__TapConfig_msg_init, arena);
    if (sub) envoy_admin_v3_TapRequest_set_tap_config(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
