
#ifndef ENVOY_CONFIG_CLUSTER_V3_FILTER_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CLUSTER_V3_FILTER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/cluster/v3/filter.upb_minitable.h"

#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_cluster_v3_Filter { upb_Message UPB_PRIVATE(base); } envoy_config_cluster_v3_Filter;
struct envoy_config_core_v3_ExtensionConfigSource;
struct google_protobuf_Any;

UPB_INLINE envoy_config_cluster_v3_Filter* envoy_config_cluster_v3_Filter_new(upb_Arena* arena) {
  return (envoy_config_cluster_v3_Filter*)_upb_Message_New(&envoy__config__cluster__v3__Filter_msg_init, arena);
}
UPB_INLINE envoy_config_cluster_v3_Filter* envoy_config_cluster_v3_Filter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_cluster_v3_Filter* ret = envoy_config_cluster_v3_Filter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Filter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_cluster_v3_Filter* envoy_config_cluster_v3_Filter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_cluster_v3_Filter* ret = envoy_config_cluster_v3_Filter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__cluster__v3__Filter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_cluster_v3_Filter_serialize(const envoy_config_cluster_v3_Filter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Filter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_cluster_v3_Filter_serialize_ex(const envoy_config_cluster_v3_Filter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__cluster__v3__Filter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_cluster_v3_Filter_clear_name(envoy_config_cluster_v3_Filter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_cluster_v3_Filter_name(const envoy_config_cluster_v3_Filter* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_cluster_v3_Filter_clear_typed_config(envoy_config_cluster_v3_Filter* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_cluster_v3_Filter_typed_config(const envoy_config_cluster_v3_Filter* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Filter_has_typed_config(const envoy_config_cluster_v3_Filter* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_cluster_v3_Filter_clear_config_discovery(envoy_config_cluster_v3_Filter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ExtensionConfigSource* envoy_config_cluster_v3_Filter_config_discovery(const envoy_config_cluster_v3_Filter* msg) {
  const struct envoy_config_core_v3_ExtensionConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ExtensionConfigSource* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ExtensionConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_cluster_v3_Filter_has_config_discovery(const envoy_config_cluster_v3_Filter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_cluster_v3_Filter_set_name(envoy_config_cluster_v3_Filter *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_cluster_v3_Filter_set_typed_config(envoy_config_cluster_v3_Filter *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_cluster_v3_Filter_mutable_typed_config(envoy_config_cluster_v3_Filter* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_cluster_v3_Filter_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Filter_set_typed_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_cluster_v3_Filter_set_config_discovery(envoy_config_cluster_v3_Filter *msg, struct envoy_config_core_v3_ExtensionConfigSource* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ExtensionConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ExtensionConfigSource* envoy_config_cluster_v3_Filter_mutable_config_discovery(envoy_config_cluster_v3_Filter* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ExtensionConfigSource* sub = (struct envoy_config_core_v3_ExtensionConfigSource*)envoy_config_cluster_v3_Filter_config_discovery(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ExtensionConfigSource*)_upb_Message_New(&envoy__config__core__v3__ExtensionConfigSource_msg_init, arena);
    if (sub) envoy_config_cluster_v3_Filter_set_config_discovery(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
