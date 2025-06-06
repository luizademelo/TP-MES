
#ifndef ENVOY_ADMIN_V3_CONFIG_DUMP_PROTO_UPB_H__UPB_H_
#define ENVOY_ADMIN_V3_CONFIG_DUMP_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/admin/v3/config_dump.upb_minitable.h"

#include "envoy/admin/v3/config_dump_shared.upb_minitable.h"
#include "envoy/config/bootstrap/v3/bootstrap.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_admin_v3_ConfigDump { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_ConfigDump;
typedef struct envoy_admin_v3_BootstrapConfigDump { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_BootstrapConfigDump;
typedef struct envoy_admin_v3_SecretsConfigDump { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_SecretsConfigDump;
typedef struct envoy_admin_v3_SecretsConfigDump_DynamicSecret { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_SecretsConfigDump_DynamicSecret;
typedef struct envoy_admin_v3_SecretsConfigDump_StaticSecret { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_SecretsConfigDump_StaticSecret;
struct envoy_admin_v3_UpdateFailureState;
struct envoy_config_bootstrap_v3_Bootstrap;
struct google_protobuf_Any;
struct google_protobuf_Timestamp;

UPB_INLINE envoy_admin_v3_ConfigDump* envoy_admin_v3_ConfigDump_new(upb_Arena* arena) {
  return (envoy_admin_v3_ConfigDump*)_upb_Message_New(&envoy__admin__v3__ConfigDump_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_ConfigDump* envoy_admin_v3_ConfigDump_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_ConfigDump* ret = envoy_admin_v3_ConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ConfigDump_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_ConfigDump* envoy_admin_v3_ConfigDump_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_ConfigDump* ret = envoy_admin_v3_ConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__ConfigDump_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_ConfigDump_serialize(const envoy_admin_v3_ConfigDump* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ConfigDump_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_ConfigDump_serialize_ex(const envoy_admin_v3_ConfigDump* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__ConfigDump_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_ConfigDump_clear_configs(envoy_admin_v3_ConfigDump* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* const* envoy_admin_v3_ConfigDump_configs(const envoy_admin_v3_ConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct google_protobuf_Any* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_ConfigDump_configs_upb_array(const envoy_admin_v3_ConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_ConfigDump_configs_mutable_upb_array(envoy_admin_v3_ConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE struct google_protobuf_Any** envoy_admin_v3_ConfigDump_mutable_configs(envoy_admin_v3_ConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct google_protobuf_Any**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct google_protobuf_Any** envoy_admin_v3_ConfigDump_resize_configs(envoy_admin_v3_ConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct google_protobuf_Any**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_ConfigDump_add_configs(envoy_admin_v3_ConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_BootstrapConfigDump* envoy_admin_v3_BootstrapConfigDump_new(upb_Arena* arena) {
  return (envoy_admin_v3_BootstrapConfigDump*)_upb_Message_New(&envoy__admin__v3__BootstrapConfigDump_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_BootstrapConfigDump* envoy_admin_v3_BootstrapConfigDump_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_BootstrapConfigDump* ret = envoy_admin_v3_BootstrapConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__BootstrapConfigDump_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_BootstrapConfigDump* envoy_admin_v3_BootstrapConfigDump_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_BootstrapConfigDump* ret = envoy_admin_v3_BootstrapConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__BootstrapConfigDump_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_BootstrapConfigDump_serialize(const envoy_admin_v3_BootstrapConfigDump* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__BootstrapConfigDump_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_BootstrapConfigDump_serialize_ex(const envoy_admin_v3_BootstrapConfigDump* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__BootstrapConfigDump_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_BootstrapConfigDump_clear_bootstrap(envoy_admin_v3_BootstrapConfigDump* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_bootstrap_v3_Bootstrap* envoy_admin_v3_BootstrapConfigDump_bootstrap(const envoy_admin_v3_BootstrapConfigDump* msg) {
  const struct envoy_config_bootstrap_v3_Bootstrap* default_val = NULL;
  const struct envoy_config_bootstrap_v3_Bootstrap* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_BootstrapConfigDump_has_bootstrap(const envoy_admin_v3_BootstrapConfigDump* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_BootstrapConfigDump_clear_last_updated(envoy_admin_v3_BootstrapConfigDump* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_BootstrapConfigDump_last_updated(const envoy_admin_v3_BootstrapConfigDump* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_BootstrapConfigDump_has_last_updated(const envoy_admin_v3_BootstrapConfigDump* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_BootstrapConfigDump_set_bootstrap(envoy_admin_v3_BootstrapConfigDump *msg, struct envoy_config_bootstrap_v3_Bootstrap* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__bootstrap__v3__Bootstrap_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_bootstrap_v3_Bootstrap* envoy_admin_v3_BootstrapConfigDump_mutable_bootstrap(envoy_admin_v3_BootstrapConfigDump* msg, upb_Arena* arena) {
  struct envoy_config_bootstrap_v3_Bootstrap* sub = (struct envoy_config_bootstrap_v3_Bootstrap*)envoy_admin_v3_BootstrapConfigDump_bootstrap(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_bootstrap_v3_Bootstrap*)_upb_Message_New(&envoy__config__bootstrap__v3__Bootstrap_msg_init, arena);
    if (sub) envoy_admin_v3_BootstrapConfigDump_set_bootstrap(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_BootstrapConfigDump_set_last_updated(envoy_admin_v3_BootstrapConfigDump *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_BootstrapConfigDump_mutable_last_updated(envoy_admin_v3_BootstrapConfigDump* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_BootstrapConfigDump_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_BootstrapConfigDump_set_last_updated(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_SecretsConfigDump* envoy_admin_v3_SecretsConfigDump_new(upb_Arena* arena) {
  return (envoy_admin_v3_SecretsConfigDump*)_upb_Message_New(&envoy__admin__v3__SecretsConfigDump_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump* envoy_admin_v3_SecretsConfigDump_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_SecretsConfigDump* ret = envoy_admin_v3_SecretsConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__SecretsConfigDump_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump* envoy_admin_v3_SecretsConfigDump_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_SecretsConfigDump* ret = envoy_admin_v3_SecretsConfigDump_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__SecretsConfigDump_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_SecretsConfigDump_serialize(const envoy_admin_v3_SecretsConfigDump* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__SecretsConfigDump_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_SecretsConfigDump_serialize_ex(const envoy_admin_v3_SecretsConfigDump* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__SecretsConfigDump_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_clear_static_secrets(envoy_admin_v3_SecretsConfigDump* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_SecretsConfigDump_StaticSecret* const* envoy_admin_v3_SecretsConfigDump_static_secrets(const envoy_admin_v3_SecretsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_SecretsConfigDump_StaticSecret* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_SecretsConfigDump_static_secrets_upb_array(const envoy_admin_v3_SecretsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_SecretsConfigDump_static_secrets_mutable_upb_array(envoy_admin_v3_SecretsConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_clear_dynamic_active_secrets(envoy_admin_v3_SecretsConfigDump* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_SecretsConfigDump_DynamicSecret* const* envoy_admin_v3_SecretsConfigDump_dynamic_active_secrets(const envoy_admin_v3_SecretsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_SecretsConfigDump_DynamicSecret* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_SecretsConfigDump_dynamic_active_secrets_upb_array(const envoy_admin_v3_SecretsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_SecretsConfigDump_dynamic_active_secrets_mutable_upb_array(envoy_admin_v3_SecretsConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_clear_dynamic_warming_secrets(envoy_admin_v3_SecretsConfigDump* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_SecretsConfigDump_DynamicSecret* const* envoy_admin_v3_SecretsConfigDump_dynamic_warming_secrets(const envoy_admin_v3_SecretsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_SecretsConfigDump_DynamicSecret* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_SecretsConfigDump_dynamic_warming_secrets_upb_array(const envoy_admin_v3_SecretsConfigDump* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_SecretsConfigDump_dynamic_warming_secrets_mutable_upb_array(envoy_admin_v3_SecretsConfigDump* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_admin_v3_SecretsConfigDump_StaticSecret** envoy_admin_v3_SecretsConfigDump_mutable_static_secrets(envoy_admin_v3_SecretsConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_SecretsConfigDump_StaticSecret**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump_StaticSecret** envoy_admin_v3_SecretsConfigDump_resize_static_secrets(envoy_admin_v3_SecretsConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_SecretsConfigDump_StaticSecret**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_SecretsConfigDump_StaticSecret* envoy_admin_v3_SecretsConfigDump_add_static_secrets(envoy_admin_v3_SecretsConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_SecretsConfigDump_StaticSecret* sub = (struct envoy_admin_v3_SecretsConfigDump_StaticSecret*)_upb_Message_New(&envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump_DynamicSecret** envoy_admin_v3_SecretsConfigDump_mutable_dynamic_active_secrets(envoy_admin_v3_SecretsConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_SecretsConfigDump_DynamicSecret**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump_DynamicSecret** envoy_admin_v3_SecretsConfigDump_resize_dynamic_active_secrets(envoy_admin_v3_SecretsConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_SecretsConfigDump_DynamicSecret**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_SecretsConfigDump_DynamicSecret* envoy_admin_v3_SecretsConfigDump_add_dynamic_active_secrets(envoy_admin_v3_SecretsConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_SecretsConfigDump_DynamicSecret* sub = (struct envoy_admin_v3_SecretsConfigDump_DynamicSecret*)_upb_Message_New(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump_DynamicSecret** envoy_admin_v3_SecretsConfigDump_mutable_dynamic_warming_secrets(envoy_admin_v3_SecretsConfigDump* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_SecretsConfigDump_DynamicSecret**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump_DynamicSecret** envoy_admin_v3_SecretsConfigDump_resize_dynamic_warming_secrets(envoy_admin_v3_SecretsConfigDump* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_SecretsConfigDump_DynamicSecret**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_SecretsConfigDump_DynamicSecret* envoy_admin_v3_SecretsConfigDump_add_dynamic_warming_secrets(envoy_admin_v3_SecretsConfigDump* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_SecretsConfigDump_DynamicSecret* sub = (struct envoy_admin_v3_SecretsConfigDump_DynamicSecret*)_upb_Message_New(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_SecretsConfigDump_DynamicSecret* envoy_admin_v3_SecretsConfigDump_DynamicSecret_new(upb_Arena* arena) {
  return (envoy_admin_v3_SecretsConfigDump_DynamicSecret*)_upb_Message_New(&envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump_DynamicSecret* envoy_admin_v3_SecretsConfigDump_DynamicSecret_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_SecretsConfigDump_DynamicSecret* ret = envoy_admin_v3_SecretsConfigDump_DynamicSecret_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump_DynamicSecret* envoy_admin_v3_SecretsConfigDump_DynamicSecret_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_SecretsConfigDump_DynamicSecret* ret = envoy_admin_v3_SecretsConfigDump_DynamicSecret_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_SecretsConfigDump_DynamicSecret_serialize(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_SecretsConfigDump_DynamicSecret_serialize_ex(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_clear_name(envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_SecretsConfigDump_DynamicSecret_name(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_clear_version_info(envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_SecretsConfigDump_DynamicSecret_version_info(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_clear_last_updated(envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_SecretsConfigDump_DynamicSecret_last_updated(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_SecretsConfigDump_DynamicSecret_has_last_updated(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_clear_secret(envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_SecretsConfigDump_DynamicSecret_secret(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_SecretsConfigDump_DynamicSecret_has_secret(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_clear_error_state(envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_admin_v3_UpdateFailureState* envoy_admin_v3_SecretsConfigDump_DynamicSecret_error_state(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const struct envoy_admin_v3_UpdateFailureState* default_val = NULL;
  const struct envoy_admin_v3_UpdateFailureState* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_SecretsConfigDump_DynamicSecret_has_error_state(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_clear_client_status(envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_admin_v3_SecretsConfigDump_DynamicSecret_client_status(const envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {6, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_set_name(envoy_admin_v3_SecretsConfigDump_DynamicSecret *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_set_version_info(envoy_admin_v3_SecretsConfigDump_DynamicSecret *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_set_last_updated(envoy_admin_v3_SecretsConfigDump_DynamicSecret *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_SecretsConfigDump_DynamicSecret_mutable_last_updated(envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_SecretsConfigDump_DynamicSecret_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_SecretsConfigDump_DynamicSecret_set_last_updated(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_set_secret(envoy_admin_v3_SecretsConfigDump_DynamicSecret *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_SecretsConfigDump_DynamicSecret_mutable_secret(envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_SecretsConfigDump_DynamicSecret_secret(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_SecretsConfigDump_DynamicSecret_set_secret(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_set_error_state(envoy_admin_v3_SecretsConfigDump_DynamicSecret *msg, struct envoy_admin_v3_UpdateFailureState* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__UpdateFailureState_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_UpdateFailureState* envoy_admin_v3_SecretsConfigDump_DynamicSecret_mutable_error_state(envoy_admin_v3_SecretsConfigDump_DynamicSecret* msg, upb_Arena* arena) {
  struct envoy_admin_v3_UpdateFailureState* sub = (struct envoy_admin_v3_UpdateFailureState*)envoy_admin_v3_SecretsConfigDump_DynamicSecret_error_state(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_UpdateFailureState*)_upb_Message_New(&envoy__admin__v3__UpdateFailureState_msg_init, arena);
    if (sub) envoy_admin_v3_SecretsConfigDump_DynamicSecret_set_error_state(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_DynamicSecret_set_client_status(envoy_admin_v3_SecretsConfigDump_DynamicSecret *msg, int32_t value) {
  const upb_MiniTableField field = {6, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_admin_v3_SecretsConfigDump_StaticSecret* envoy_admin_v3_SecretsConfigDump_StaticSecret_new(upb_Arena* arena) {
  return (envoy_admin_v3_SecretsConfigDump_StaticSecret*)_upb_Message_New(&envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump_StaticSecret* envoy_admin_v3_SecretsConfigDump_StaticSecret_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_SecretsConfigDump_StaticSecret* ret = envoy_admin_v3_SecretsConfigDump_StaticSecret_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_SecretsConfigDump_StaticSecret* envoy_admin_v3_SecretsConfigDump_StaticSecret_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_SecretsConfigDump_StaticSecret* ret = envoy_admin_v3_SecretsConfigDump_StaticSecret_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_SecretsConfigDump_StaticSecret_serialize(const envoy_admin_v3_SecretsConfigDump_StaticSecret* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_SecretsConfigDump_StaticSecret_serialize_ex(const envoy_admin_v3_SecretsConfigDump_StaticSecret* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_StaticSecret_clear_name(envoy_admin_v3_SecretsConfigDump_StaticSecret* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_SecretsConfigDump_StaticSecret_name(const envoy_admin_v3_SecretsConfigDump_StaticSecret* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_StaticSecret_clear_last_updated(envoy_admin_v3_SecretsConfigDump_StaticSecret* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_SecretsConfigDump_StaticSecret_last_updated(const envoy_admin_v3_SecretsConfigDump_StaticSecret* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_SecretsConfigDump_StaticSecret_has_last_updated(const envoy_admin_v3_SecretsConfigDump_StaticSecret* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_StaticSecret_clear_secret(envoy_admin_v3_SecretsConfigDump_StaticSecret* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_admin_v3_SecretsConfigDump_StaticSecret_secret(const envoy_admin_v3_SecretsConfigDump_StaticSecret* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_SecretsConfigDump_StaticSecret_has_secret(const envoy_admin_v3_SecretsConfigDump_StaticSecret* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_SecretsConfigDump_StaticSecret_set_name(envoy_admin_v3_SecretsConfigDump_StaticSecret *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_StaticSecret_set_last_updated(envoy_admin_v3_SecretsConfigDump_StaticSecret *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_SecretsConfigDump_StaticSecret_mutable_last_updated(envoy_admin_v3_SecretsConfigDump_StaticSecret* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_SecretsConfigDump_StaticSecret_last_updated(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_SecretsConfigDump_StaticSecret_set_last_updated(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_SecretsConfigDump_StaticSecret_set_secret(envoy_admin_v3_SecretsConfigDump_StaticSecret *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_admin_v3_SecretsConfigDump_StaticSecret_mutable_secret(envoy_admin_v3_SecretsConfigDump_StaticSecret* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_admin_v3_SecretsConfigDump_StaticSecret_secret(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_admin_v3_SecretsConfigDump_StaticSecret_set_secret(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
