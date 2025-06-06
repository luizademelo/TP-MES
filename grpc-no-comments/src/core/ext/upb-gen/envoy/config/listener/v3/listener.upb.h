
#ifndef ENVOY_CONFIG_LISTENER_V3_LISTENER_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_LISTENER_V3_LISTENER_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/listener/v3/listener.upb_minitable.h"

#include "envoy/config/accesslog/v3/accesslog.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/socket_option.upb_minitable.h"
#include "envoy/config/listener/v3/api_listener.upb_minitable.h"
#include "envoy/config/listener/v3/listener_components.upb_minitable.h"
#include "envoy/config/listener/v3/udp_listener_config.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/core/v3/collection_entry.upb_minitable.h"
#include "xds/type/matcher/v3/matcher.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/security.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_listener_v3_AdditionalAddress { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_AdditionalAddress;
typedef struct envoy_config_listener_v3_ListenerCollection { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_ListenerCollection;
typedef struct envoy_config_listener_v3_Listener { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_Listener;
typedef struct envoy_config_listener_v3_Listener_DeprecatedV1 { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_Listener_DeprecatedV1;
typedef struct envoy_config_listener_v3_Listener_ConnectionBalanceConfig { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_Listener_ConnectionBalanceConfig;
typedef struct envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance;
typedef struct envoy_config_listener_v3_Listener_InternalListenerConfig { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_Listener_InternalListenerConfig;
typedef struct envoy_config_listener_v3_ListenerManager { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_ListenerManager;
typedef struct envoy_config_listener_v3_ValidationListenerManager { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_ValidationListenerManager;
typedef struct envoy_config_listener_v3_ApiListenerManager { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_ApiListenerManager;
struct envoy_config_accesslog_v3_AccessLog;
struct envoy_config_core_v3_Address;
struct envoy_config_core_v3_Metadata;
struct envoy_config_core_v3_SocketOption;
struct envoy_config_core_v3_SocketOptionsOverride;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_config_listener_v3_ApiListener;
struct envoy_config_listener_v3_FilterChain;
struct envoy_config_listener_v3_ListenerFilter;
struct envoy_config_listener_v3_UdpListenerConfig;
struct google_protobuf_BoolValue;
struct google_protobuf_Duration;
struct google_protobuf_UInt32Value;
struct xds_core_v3_CollectionEntry;
struct xds_type_matcher_v3_Matcher;

typedef enum {
  envoy_config_listener_v3_Listener_DEFAULT = 0,
  envoy_config_listener_v3_Listener_MODIFY_ONLY = 1
} envoy_config_listener_v3_Listener_DrainType;

UPB_INLINE envoy_config_listener_v3_AdditionalAddress* envoy_config_listener_v3_AdditionalAddress_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_AdditionalAddress*)_upb_Message_New(&envoy__config__listener__v3__AdditionalAddress_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_AdditionalAddress* envoy_config_listener_v3_AdditionalAddress_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_AdditionalAddress* ret = envoy_config_listener_v3_AdditionalAddress_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__AdditionalAddress_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_AdditionalAddress* envoy_config_listener_v3_AdditionalAddress_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_AdditionalAddress* ret = envoy_config_listener_v3_AdditionalAddress_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__AdditionalAddress_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_AdditionalAddress_serialize(const envoy_config_listener_v3_AdditionalAddress* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__AdditionalAddress_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_AdditionalAddress_serialize_ex(const envoy_config_listener_v3_AdditionalAddress* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__AdditionalAddress_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_listener_v3_AdditionalAddress_clear_address(envoy_config_listener_v3_AdditionalAddress* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_config_listener_v3_AdditionalAddress_address(const envoy_config_listener_v3_AdditionalAddress* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_AdditionalAddress_has_address(const envoy_config_listener_v3_AdditionalAddress* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_AdditionalAddress_clear_socket_options(envoy_config_listener_v3_AdditionalAddress* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_SocketOptionsOverride* envoy_config_listener_v3_AdditionalAddress_socket_options(const envoy_config_listener_v3_AdditionalAddress* msg) {
  const struct envoy_config_core_v3_SocketOptionsOverride* default_val = NULL;
  const struct envoy_config_core_v3_SocketOptionsOverride* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOptionsOverride_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_AdditionalAddress_has_socket_options(const envoy_config_listener_v3_AdditionalAddress* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_listener_v3_AdditionalAddress_set_address(envoy_config_listener_v3_AdditionalAddress *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_config_listener_v3_AdditionalAddress_mutable_address(envoy_config_listener_v3_AdditionalAddress* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_config_listener_v3_AdditionalAddress_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_config_listener_v3_AdditionalAddress_set_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_AdditionalAddress_set_socket_options(envoy_config_listener_v3_AdditionalAddress *msg, struct envoy_config_core_v3_SocketOptionsOverride* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOptionsOverride_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_SocketOptionsOverride* envoy_config_listener_v3_AdditionalAddress_mutable_socket_options(envoy_config_listener_v3_AdditionalAddress* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_SocketOptionsOverride* sub = (struct envoy_config_core_v3_SocketOptionsOverride*)envoy_config_listener_v3_AdditionalAddress_socket_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_SocketOptionsOverride*)_upb_Message_New(&envoy__config__core__v3__SocketOptionsOverride_msg_init, arena);
    if (sub) envoy_config_listener_v3_AdditionalAddress_set_socket_options(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_listener_v3_ListenerCollection* envoy_config_listener_v3_ListenerCollection_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_ListenerCollection*)_upb_Message_New(&envoy__config__listener__v3__ListenerCollection_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_ListenerCollection* envoy_config_listener_v3_ListenerCollection_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_ListenerCollection* ret = envoy_config_listener_v3_ListenerCollection_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ListenerCollection_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_ListenerCollection* envoy_config_listener_v3_ListenerCollection_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_ListenerCollection* ret = envoy_config_listener_v3_ListenerCollection_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ListenerCollection_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_ListenerCollection_serialize(const envoy_config_listener_v3_ListenerCollection* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerCollection_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_ListenerCollection_serialize_ex(const envoy_config_listener_v3_ListenerCollection* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerCollection_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_listener_v3_ListenerCollection_clear_entries(envoy_config_listener_v3_ListenerCollection* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_core_v3_CollectionEntry* const* envoy_config_listener_v3_ListenerCollection_entries(const envoy_config_listener_v3_ListenerCollection* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__CollectionEntry_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct xds_core_v3_CollectionEntry* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_ListenerCollection_entries_upb_array(const envoy_config_listener_v3_ListenerCollection* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__CollectionEntry_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_ListenerCollection_entries_mutable_upb_array(envoy_config_listener_v3_ListenerCollection* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__CollectionEntry_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE struct xds_core_v3_CollectionEntry** envoy_config_listener_v3_ListenerCollection_mutable_entries(envoy_config_listener_v3_ListenerCollection* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__CollectionEntry_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct xds_core_v3_CollectionEntry**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct xds_core_v3_CollectionEntry** envoy_config_listener_v3_ListenerCollection_resize_entries(envoy_config_listener_v3_ListenerCollection* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct xds_core_v3_CollectionEntry**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct xds_core_v3_CollectionEntry* envoy_config_listener_v3_ListenerCollection_add_entries(envoy_config_listener_v3_ListenerCollection* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__CollectionEntry_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct xds_core_v3_CollectionEntry* sub = (struct xds_core_v3_CollectionEntry*)_upb_Message_New(&xds__core__v3__CollectionEntry_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_listener_v3_Listener* envoy_config_listener_v3_Listener_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_Listener*)_upb_Message_New(&envoy__config__listener__v3__Listener_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_Listener* envoy_config_listener_v3_Listener_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_Listener* ret = envoy_config_listener_v3_Listener_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Listener_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_Listener* envoy_config_listener_v3_Listener_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_Listener* ret = envoy_config_listener_v3_Listener_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Listener_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_Listener_serialize(const envoy_config_listener_v3_Listener* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_Listener_serialize_ex(const envoy_config_listener_v3_Listener* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_listener_v3_Listener_listener_specifier_internal_listener = 27,
  envoy_config_listener_v3_Listener_listener_specifier_NOT_SET = 0
} envoy_config_listener_v3_Listener_listener_specifier_oneofcases;
UPB_INLINE envoy_config_listener_v3_Listener_listener_specifier_oneofcases envoy_config_listener_v3_Listener_listener_specifier_case(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {27, UPB_SIZE(120, 248), UPB_SIZE(-117, -25), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_listener_v3_Listener_listener_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_listener_specifier(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {27, UPB_SIZE(120, 248), UPB_SIZE(-117, -25), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener_msg_init, &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_name(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(124, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_listener_v3_Listener_name(const envoy_config_listener_v3_Listener* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(124, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_address(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_config_listener_v3_Listener_address(const envoy_config_listener_v3_Listener* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_address(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_filter_chains(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_listener_v3_FilterChain* const* envoy_config_listener_v3_Listener_filter_chains(const envoy_config_listener_v3_Listener* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__FilterChain_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_listener_v3_FilterChain* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_Listener_filter_chains_upb_array(const envoy_config_listener_v3_Listener* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__FilterChain_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_Listener_filter_chains_mutable_upb_array(envoy_config_listener_v3_Listener* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__FilterChain_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_use_original_dst(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_use_original_dst(const envoy_config_listener_v3_Listener* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(24, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_use_original_dst(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_per_connection_buffer_limit_bytes(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_listener_v3_Listener_per_connection_buffer_limit_bytes(const envoy_config_listener_v3_Listener* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(28, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_per_connection_buffer_limit_bytes(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_metadata(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 96), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Metadata* envoy_config_listener_v3_Listener_metadata(const envoy_config_listener_v3_Listener* msg) {
  const struct envoy_config_core_v3_Metadata* default_val = NULL;
  const struct envoy_config_core_v3_Metadata* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(32, 96), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_metadata(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 96), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_deprecated_v1(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 104), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_Listener_DeprecatedV1* envoy_config_listener_v3_Listener_deprecated_v1(const envoy_config_listener_v3_Listener* msg) {
  const envoy_config_listener_v3_Listener_DeprecatedV1* default_val = NULL;
  const envoy_config_listener_v3_Listener_DeprecatedV1* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(36, 104), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener__DeprecatedV1_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_deprecated_v1(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 104), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_drain_type(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_listener_v3_Listener_drain_type(const envoy_config_listener_v3_Listener* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {8, UPB_SIZE(40, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_listener_filters(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 112), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_listener_v3_ListenerFilter* const* envoy_config_listener_v3_Listener_listener_filters(const envoy_config_listener_v3_Listener* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 112), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_listener_v3_ListenerFilter* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_Listener_listener_filters_upb_array(const envoy_config_listener_v3_Listener* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 112), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_Listener_listener_filters_mutable_upb_array(envoy_config_listener_v3_Listener* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {9, UPB_SIZE(44, 112), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_transparent(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(48, 120), 69, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_transparent(const envoy_config_listener_v3_Listener* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {10, UPB_SIZE(48, 120), 69, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_transparent(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(48, 120), 69, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_freebind(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(52, 128), 70, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_freebind(const envoy_config_listener_v3_Listener* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {11, UPB_SIZE(52, 128), 70, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_freebind(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(52, 128), 70, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_tcp_fast_open_queue_length(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(56, 136), 71, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_listener_v3_Listener_tcp_fast_open_queue_length(const envoy_config_listener_v3_Listener* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {12, UPB_SIZE(56, 136), 71, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_tcp_fast_open_queue_length(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(56, 136), 71, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_socket_options(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(60, 144), 0, 10, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_SocketOption* const* envoy_config_listener_v3_Listener_socket_options(const envoy_config_listener_v3_Listener* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(60, 144), 0, 10, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_SocketOption* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_Listener_socket_options_upb_array(const envoy_config_listener_v3_Listener* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(60, 144), 0, 10, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOption_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_Listener_socket_options_mutable_upb_array(envoy_config_listener_v3_Listener* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {13, UPB_SIZE(60, 144), 0, 10, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_listener_filters_timeout(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(64, 152), 72, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_listener_v3_Listener_listener_filters_timeout(const envoy_config_listener_v3_Listener* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {15, UPB_SIZE(64, 152), 72, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_listener_filters_timeout(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {15, UPB_SIZE(64, 152), 72, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_traffic_direction(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(68, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_listener_v3_Listener_traffic_direction(const envoy_config_listener_v3_Listener* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {16, UPB_SIZE(68, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_continue_on_listener_filters_timeout(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {17, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_listener_v3_Listener_continue_on_listener_filters_timeout(const envoy_config_listener_v3_Listener* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {17, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_udp_listener_config(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(72, 160), 73, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_listener_v3_UdpListenerConfig* envoy_config_listener_v3_Listener_udp_listener_config(const envoy_config_listener_v3_Listener* msg) {
  const struct envoy_config_listener_v3_UdpListenerConfig* default_val = NULL;
  const struct envoy_config_listener_v3_UdpListenerConfig* ret;
  const upb_MiniTableField field = {18, UPB_SIZE(72, 160), 73, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__UdpListenerConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_udp_listener_config(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {18, UPB_SIZE(72, 160), 73, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_api_listener(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(76, 168), 74, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_listener_v3_ApiListener* envoy_config_listener_v3_Listener_api_listener(const envoy_config_listener_v3_Listener* msg) {
  const struct envoy_config_listener_v3_ApiListener* default_val = NULL;
  const struct envoy_config_listener_v3_ApiListener* ret;
  const upb_MiniTableField field = {19, UPB_SIZE(76, 168), 74, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ApiListener_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_api_listener(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {19, UPB_SIZE(76, 168), 74, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_connection_balance_config(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(80, 176), 75, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_Listener_ConnectionBalanceConfig* envoy_config_listener_v3_Listener_connection_balance_config(const envoy_config_listener_v3_Listener* msg) {
  const envoy_config_listener_v3_Listener_ConnectionBalanceConfig* default_val = NULL;
  const envoy_config_listener_v3_Listener_ConnectionBalanceConfig* ret;
  const upb_MiniTableField field = {20, UPB_SIZE(80, 176), 75, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_connection_balance_config(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {20, UPB_SIZE(80, 176), 75, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_reuse_port(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {21, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_listener_v3_Listener_reuse_port(const envoy_config_listener_v3_Listener* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {21, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_access_log(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {22, UPB_SIZE(84, 184), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_accesslog_v3_AccessLog* const* envoy_config_listener_v3_Listener_access_log(const envoy_config_listener_v3_Listener* msg, size_t* size) {
  const upb_MiniTableField field = {22, UPB_SIZE(84, 184), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_accesslog_v3_AccessLog* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_Listener_access_log_upb_array(const envoy_config_listener_v3_Listener* msg, size_t* size) {
  const upb_MiniTableField field = {22, UPB_SIZE(84, 184), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_Listener_access_log_mutable_upb_array(envoy_config_listener_v3_Listener* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {22, UPB_SIZE(84, 184), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_tcp_backlog_size(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(88, 192), 76, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_listener_v3_Listener_tcp_backlog_size(const envoy_config_listener_v3_Listener* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {24, UPB_SIZE(88, 192), 76, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_tcp_backlog_size(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {24, UPB_SIZE(88, 192), 76, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_default_filter_chain(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(92, 200), 77, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_listener_v3_FilterChain* envoy_config_listener_v3_Listener_default_filter_chain(const envoy_config_listener_v3_Listener* msg) {
  const struct envoy_config_listener_v3_FilterChain* default_val = NULL;
  const struct envoy_config_listener_v3_FilterChain* ret;
  const upb_MiniTableField field = {25, UPB_SIZE(92, 200), 77, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__FilterChain_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_default_filter_chain(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {25, UPB_SIZE(92, 200), 77, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_bind_to_port(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {26, UPB_SIZE(96, 208), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_bind_to_port(const envoy_config_listener_v3_Listener* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {26, UPB_SIZE(96, 208), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_bind_to_port(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {26, UPB_SIZE(96, 208), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_internal_listener(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {27, UPB_SIZE(120, 248), UPB_SIZE(-117, -25), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_Listener_InternalListenerConfig* envoy_config_listener_v3_Listener_internal_listener(const envoy_config_listener_v3_Listener* msg) {
  const envoy_config_listener_v3_Listener_InternalListenerConfig* default_val = NULL;
  const envoy_config_listener_v3_Listener_InternalListenerConfig* ret;
  const upb_MiniTableField field = {27, UPB_SIZE(120, 248), UPB_SIZE(-117, -25), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_internal_listener(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {27, UPB_SIZE(120, 248), UPB_SIZE(-117, -25), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_stat_prefix(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {28, UPB_SIZE(132, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_listener_v3_Listener_stat_prefix(const envoy_config_listener_v3_Listener* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {28, UPB_SIZE(132, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_enable_reuse_port(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {29, UPB_SIZE(100, 216), 79, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_enable_reuse_port(const envoy_config_listener_v3_Listener* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {29, UPB_SIZE(100, 216), 79, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_enable_reuse_port(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {29, UPB_SIZE(100, 216), 79, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_enable_mptcp(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {30, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_listener_v3_Listener_enable_mptcp(const envoy_config_listener_v3_Listener* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {30, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_ignore_global_conn_limit(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {31, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_listener_v3_Listener_ignore_global_conn_limit(const envoy_config_listener_v3_Listener* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {31, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_filter_chain_matcher(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {32, UPB_SIZE(104, 224), 80, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_matcher_v3_Matcher* envoy_config_listener_v3_Listener_filter_chain_matcher(const envoy_config_listener_v3_Listener* msg) {
  const struct xds_type_matcher_v3_Matcher* default_val = NULL;
  const struct xds_type_matcher_v3_Matcher* ret;
  const upb_MiniTableField field = {32, UPB_SIZE(104, 224), 80, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_filter_chain_matcher(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {32, UPB_SIZE(104, 224), 80, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_additional_addresses(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {33, UPB_SIZE(108, 232), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_AdditionalAddress* const* envoy_config_listener_v3_Listener_additional_addresses(const envoy_config_listener_v3_Listener* msg, size_t* size) {
  const upb_MiniTableField field = {33, UPB_SIZE(108, 232), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__AdditionalAddress_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_listener_v3_AdditionalAddress* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_Listener_additional_addresses_upb_array(const envoy_config_listener_v3_Listener* msg, size_t* size) {
  const upb_MiniTableField field = {33, UPB_SIZE(108, 232), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__AdditionalAddress_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_Listener_additional_addresses_mutable_upb_array(envoy_config_listener_v3_Listener* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {33, UPB_SIZE(108, 232), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__AdditionalAddress_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_max_connections_to_accept_per_socket_event(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {34, UPB_SIZE(112, 240), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_listener_v3_Listener_max_connections_to_accept_per_socket_event(const envoy_config_listener_v3_Listener* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {34, UPB_SIZE(112, 240), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_has_max_connections_to_accept_per_socket_event(const envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {34, UPB_SIZE(112, 240), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_clear_bypass_overload_manager(envoy_config_listener_v3_Listener* msg) {
  const upb_MiniTableField field = {35, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_listener_v3_Listener_bypass_overload_manager(const envoy_config_listener_v3_Listener* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {35, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_listener_v3_Listener_set_name(envoy_config_listener_v3_Listener *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(124, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_address(envoy_config_listener_v3_Listener *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_config_listener_v3_Listener_mutable_address(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_config_listener_v3_Listener_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_address(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_listener_v3_FilterChain** envoy_config_listener_v3_Listener_mutable_filter_chains(envoy_config_listener_v3_Listener* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__FilterChain_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_listener_v3_FilterChain**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_listener_v3_FilterChain** envoy_config_listener_v3_Listener_resize_filter_chains(envoy_config_listener_v3_Listener* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_listener_v3_FilterChain**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_listener_v3_FilterChain* envoy_config_listener_v3_Listener_add_filter_chains(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(20, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__FilterChain_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_listener_v3_FilterChain* sub = (struct envoy_config_listener_v3_FilterChain*)_upb_Message_New(&envoy__config__listener__v3__FilterChain_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_use_original_dst(envoy_config_listener_v3_Listener *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_mutable_use_original_dst(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_listener_v3_Listener_use_original_dst(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_use_original_dst(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_per_connection_buffer_limit_bytes(envoy_config_listener_v3_Listener *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(28, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_listener_v3_Listener_mutable_per_connection_buffer_limit_bytes(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_listener_v3_Listener_per_connection_buffer_limit_bytes(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_per_connection_buffer_limit_bytes(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_metadata(envoy_config_listener_v3_Listener *msg, struct envoy_config_core_v3_Metadata* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(32, 96), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Metadata* envoy_config_listener_v3_Listener_mutable_metadata(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Metadata* sub = (struct envoy_config_core_v3_Metadata*)envoy_config_listener_v3_Listener_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Metadata*)_upb_Message_New(&envoy__config__core__v3__Metadata_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_deprecated_v1(envoy_config_listener_v3_Listener *msg, envoy_config_listener_v3_Listener_DeprecatedV1* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 104), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener__DeprecatedV1_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_Listener_DeprecatedV1* envoy_config_listener_v3_Listener_mutable_deprecated_v1(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_Listener_DeprecatedV1* sub = (struct envoy_config_listener_v3_Listener_DeprecatedV1*)envoy_config_listener_v3_Listener_deprecated_v1(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_Listener_DeprecatedV1*)_upb_Message_New(&envoy__config__listener__v3__Listener__DeprecatedV1_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_deprecated_v1(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_drain_type(envoy_config_listener_v3_Listener *msg, int32_t value) {
  const upb_MiniTableField field = {8, UPB_SIZE(40, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_ListenerFilter** envoy_config_listener_v3_Listener_mutable_listener_filters(envoy_config_listener_v3_Listener* msg, size_t* size) {
  upb_MiniTableField field = {9, UPB_SIZE(44, 112), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilter_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_listener_v3_ListenerFilter**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_listener_v3_ListenerFilter** envoy_config_listener_v3_Listener_resize_listener_filters(envoy_config_listener_v3_Listener* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(44, 112), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_listener_v3_ListenerFilter**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_listener_v3_ListenerFilter* envoy_config_listener_v3_Listener_add_listener_filters(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(44, 112), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_listener_v3_ListenerFilter* sub = (struct envoy_config_listener_v3_ListenerFilter*)_upb_Message_New(&envoy__config__listener__v3__ListenerFilter_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_transparent(envoy_config_listener_v3_Listener *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {10, UPB_SIZE(48, 120), 69, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_mutable_transparent(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_listener_v3_Listener_transparent(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_transparent(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_freebind(envoy_config_listener_v3_Listener *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {11, UPB_SIZE(52, 128), 70, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_mutable_freebind(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_listener_v3_Listener_freebind(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_freebind(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_tcp_fast_open_queue_length(envoy_config_listener_v3_Listener *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {12, UPB_SIZE(56, 136), 71, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_listener_v3_Listener_mutable_tcp_fast_open_queue_length(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_listener_v3_Listener_tcp_fast_open_queue_length(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_tcp_fast_open_queue_length(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_SocketOption** envoy_config_listener_v3_Listener_mutable_socket_options(envoy_config_listener_v3_Listener* msg, size_t* size) {
  upb_MiniTableField field = {13, UPB_SIZE(60, 144), 0, 10, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOption_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_SocketOption**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_SocketOption** envoy_config_listener_v3_Listener_resize_socket_options(envoy_config_listener_v3_Listener* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(60, 144), 0, 10, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_SocketOption**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_SocketOption* envoy_config_listener_v3_Listener_add_socket_options(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(60, 144), 0, 10, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__SocketOption_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_SocketOption* sub = (struct envoy_config_core_v3_SocketOption*)_upb_Message_New(&envoy__config__core__v3__SocketOption_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_listener_filters_timeout(envoy_config_listener_v3_Listener *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {15, UPB_SIZE(64, 152), 72, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_listener_v3_Listener_mutable_listener_filters_timeout(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_listener_v3_Listener_listener_filters_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_listener_filters_timeout(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_traffic_direction(envoy_config_listener_v3_Listener *msg, int32_t value) {
  const upb_MiniTableField field = {16, UPB_SIZE(68, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_continue_on_listener_filters_timeout(envoy_config_listener_v3_Listener *msg, bool value) {
  const upb_MiniTableField field = {17, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_udp_listener_config(envoy_config_listener_v3_Listener *msg, struct envoy_config_listener_v3_UdpListenerConfig* value) {
  const upb_MiniTableField field = {18, UPB_SIZE(72, 160), 73, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__UdpListenerConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_UdpListenerConfig* envoy_config_listener_v3_Listener_mutable_udp_listener_config(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_UdpListenerConfig* sub = (struct envoy_config_listener_v3_UdpListenerConfig*)envoy_config_listener_v3_Listener_udp_listener_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_UdpListenerConfig*)_upb_Message_New(&envoy__config__listener__v3__UdpListenerConfig_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_udp_listener_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_api_listener(envoy_config_listener_v3_Listener *msg, struct envoy_config_listener_v3_ApiListener* value) {
  const upb_MiniTableField field = {19, UPB_SIZE(76, 168), 74, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ApiListener_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_ApiListener* envoy_config_listener_v3_Listener_mutable_api_listener(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_ApiListener* sub = (struct envoy_config_listener_v3_ApiListener*)envoy_config_listener_v3_Listener_api_listener(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_ApiListener*)_upb_Message_New(&envoy__config__listener__v3__ApiListener_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_api_listener(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_connection_balance_config(envoy_config_listener_v3_Listener *msg, envoy_config_listener_v3_Listener_ConnectionBalanceConfig* value) {
  const upb_MiniTableField field = {20, UPB_SIZE(80, 176), 75, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_Listener_ConnectionBalanceConfig* envoy_config_listener_v3_Listener_mutable_connection_balance_config(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_Listener_ConnectionBalanceConfig* sub = (struct envoy_config_listener_v3_Listener_ConnectionBalanceConfig*)envoy_config_listener_v3_Listener_connection_balance_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_Listener_ConnectionBalanceConfig*)_upb_Message_New(&envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_connection_balance_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_reuse_port(envoy_config_listener_v3_Listener *msg, bool value) {
  const upb_MiniTableField field = {21, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLog** envoy_config_listener_v3_Listener_mutable_access_log(envoy_config_listener_v3_Listener* msg, size_t* size) {
  upb_MiniTableField field = {22, UPB_SIZE(84, 184), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_accesslog_v3_AccessLog**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLog** envoy_config_listener_v3_Listener_resize_access_log(envoy_config_listener_v3_Listener* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {22, UPB_SIZE(84, 184), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_accesslog_v3_AccessLog**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_accesslog_v3_AccessLog* envoy_config_listener_v3_Listener_add_access_log(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  upb_MiniTableField field = {22, UPB_SIZE(84, 184), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__accesslog__v3__AccessLog_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_accesslog_v3_AccessLog* sub = (struct envoy_config_accesslog_v3_AccessLog*)_upb_Message_New(&envoy__config__accesslog__v3__AccessLog_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_tcp_backlog_size(envoy_config_listener_v3_Listener *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {24, UPB_SIZE(88, 192), 76, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_listener_v3_Listener_mutable_tcp_backlog_size(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_listener_v3_Listener_tcp_backlog_size(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_tcp_backlog_size(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_default_filter_chain(envoy_config_listener_v3_Listener *msg, struct envoy_config_listener_v3_FilterChain* value) {
  const upb_MiniTableField field = {25, UPB_SIZE(92, 200), 77, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__FilterChain_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_FilterChain* envoy_config_listener_v3_Listener_mutable_default_filter_chain(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_FilterChain* sub = (struct envoy_config_listener_v3_FilterChain*)envoy_config_listener_v3_Listener_default_filter_chain(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_FilterChain*)_upb_Message_New(&envoy__config__listener__v3__FilterChain_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_default_filter_chain(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_bind_to_port(envoy_config_listener_v3_Listener *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {26, UPB_SIZE(96, 208), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_mutable_bind_to_port(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_listener_v3_Listener_bind_to_port(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_bind_to_port(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_internal_listener(envoy_config_listener_v3_Listener *msg, envoy_config_listener_v3_Listener_InternalListenerConfig* value) {
  const upb_MiniTableField field = {27, UPB_SIZE(120, 248), UPB_SIZE(-117, -25), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_Listener_InternalListenerConfig* envoy_config_listener_v3_Listener_mutable_internal_listener(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_Listener_InternalListenerConfig* sub = (struct envoy_config_listener_v3_Listener_InternalListenerConfig*)envoy_config_listener_v3_Listener_internal_listener(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_Listener_InternalListenerConfig*)_upb_Message_New(&envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_internal_listener(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_stat_prefix(envoy_config_listener_v3_Listener *msg, upb_StringView value) {
  const upb_MiniTableField field = {28, UPB_SIZE(132, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_enable_reuse_port(envoy_config_listener_v3_Listener *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {29, UPB_SIZE(100, 216), 79, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_mutable_enable_reuse_port(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_listener_v3_Listener_enable_reuse_port(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_enable_reuse_port(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_enable_mptcp(envoy_config_listener_v3_Listener *msg, bool value) {
  const upb_MiniTableField field = {30, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_ignore_global_conn_limit(envoy_config_listener_v3_Listener *msg, bool value) {
  const upb_MiniTableField field = {31, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_filter_chain_matcher(envoy_config_listener_v3_Listener *msg, struct xds_type_matcher_v3_Matcher* value) {
  const upb_MiniTableField field = {32, UPB_SIZE(104, 224), 80, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_type_matcher_v3_Matcher* envoy_config_listener_v3_Listener_mutable_filter_chain_matcher(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct xds_type_matcher_v3_Matcher* sub = (struct xds_type_matcher_v3_Matcher*)envoy_config_listener_v3_Listener_filter_chain_matcher(msg);
  if (sub == NULL) {
    sub = (struct xds_type_matcher_v3_Matcher*)_upb_Message_New(&xds__type__matcher__v3__Matcher_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_filter_chain_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_listener_v3_AdditionalAddress** envoy_config_listener_v3_Listener_mutable_additional_addresses(envoy_config_listener_v3_Listener* msg, size_t* size) {
  upb_MiniTableField field = {33, UPB_SIZE(108, 232), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__AdditionalAddress_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_listener_v3_AdditionalAddress**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_listener_v3_AdditionalAddress** envoy_config_listener_v3_Listener_resize_additional_addresses(envoy_config_listener_v3_Listener* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {33, UPB_SIZE(108, 232), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_listener_v3_AdditionalAddress**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_listener_v3_AdditionalAddress* envoy_config_listener_v3_Listener_add_additional_addresses(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  upb_MiniTableField field = {33, UPB_SIZE(108, 232), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__AdditionalAddress_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_listener_v3_AdditionalAddress* sub = (struct envoy_config_listener_v3_AdditionalAddress*)_upb_Message_New(&envoy__config__listener__v3__AdditionalAddress_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_max_connections_to_accept_per_socket_event(envoy_config_listener_v3_Listener *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {34, UPB_SIZE(112, 240), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_listener_v3_Listener_mutable_max_connections_to_accept_per_socket_event(envoy_config_listener_v3_Listener* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_listener_v3_Listener_max_connections_to_accept_per_socket_event(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_set_max_connections_to_accept_per_socket_event(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_set_bypass_overload_manager(envoy_config_listener_v3_Listener *msg, bool value) {
  const upb_MiniTableField field = {35, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_listener_v3_Listener_DeprecatedV1* envoy_config_listener_v3_Listener_DeprecatedV1_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_Listener_DeprecatedV1*)_upb_Message_New(&envoy__config__listener__v3__Listener__DeprecatedV1_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_Listener_DeprecatedV1* envoy_config_listener_v3_Listener_DeprecatedV1_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_Listener_DeprecatedV1* ret = envoy_config_listener_v3_Listener_DeprecatedV1_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Listener__DeprecatedV1_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_Listener_DeprecatedV1* envoy_config_listener_v3_Listener_DeprecatedV1_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_Listener_DeprecatedV1* ret = envoy_config_listener_v3_Listener_DeprecatedV1_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Listener__DeprecatedV1_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_Listener_DeprecatedV1_serialize(const envoy_config_listener_v3_Listener_DeprecatedV1* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener__DeprecatedV1_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_Listener_DeprecatedV1_serialize_ex(const envoy_config_listener_v3_Listener_DeprecatedV1* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener__DeprecatedV1_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_listener_v3_Listener_DeprecatedV1_clear_bind_to_port(envoy_config_listener_v3_Listener_DeprecatedV1* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_DeprecatedV1_bind_to_port(const envoy_config_listener_v3_Listener_DeprecatedV1* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_DeprecatedV1_has_bind_to_port(const envoy_config_listener_v3_Listener_DeprecatedV1* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_listener_v3_Listener_DeprecatedV1_set_bind_to_port(envoy_config_listener_v3_Listener_DeprecatedV1 *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_listener_v3_Listener_DeprecatedV1_mutable_bind_to_port(envoy_config_listener_v3_Listener_DeprecatedV1* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_listener_v3_Listener_DeprecatedV1_bind_to_port(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_DeprecatedV1_set_bind_to_port(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_listener_v3_Listener_ConnectionBalanceConfig* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_Listener_ConnectionBalanceConfig*)_upb_Message_New(&envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_Listener_ConnectionBalanceConfig* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_Listener_ConnectionBalanceConfig* ret = envoy_config_listener_v3_Listener_ConnectionBalanceConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_Listener_ConnectionBalanceConfig* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_Listener_ConnectionBalanceConfig* ret = envoy_config_listener_v3_Listener_ConnectionBalanceConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_serialize(const envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_serialize_ex(const envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_listener_v3_Listener_ConnectionBalanceConfig_balance_type_exact_balance = 1,
  envoy_config_listener_v3_Listener_ConnectionBalanceConfig_balance_type_extend_balance = 2,
  envoy_config_listener_v3_Listener_ConnectionBalanceConfig_balance_type_NOT_SET = 0
} envoy_config_listener_v3_Listener_ConnectionBalanceConfig_balance_type_oneofcases;
UPB_INLINE envoy_config_listener_v3_Listener_ConnectionBalanceConfig_balance_type_oneofcases envoy_config_listener_v3_Listener_ConnectionBalanceConfig_balance_type_case(const envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_listener_v3_Listener_ConnectionBalanceConfig_balance_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_ConnectionBalanceConfig_clear_balance_type(envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init, &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_ConnectionBalanceConfig_clear_exact_balance(envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_exact_balance(const envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg) {
  const envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* default_val = NULL;
  const envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_ConnectionBalanceConfig_has_exact_balance(const envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Listener_ConnectionBalanceConfig_clear_extend_balance(envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_extend_balance(const envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Listener_ConnectionBalanceConfig_has_extend_balance(const envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_listener_v3_Listener_ConnectionBalanceConfig_set_exact_balance(envoy_config_listener_v3_Listener_ConnectionBalanceConfig *msg, envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_mutable_exact_balance(envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* sub = (struct envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance*)envoy_config_listener_v3_Listener_ConnectionBalanceConfig_exact_balance(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance*)_upb_Message_New(&envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_ConnectionBalanceConfig_set_exact_balance(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Listener_ConnectionBalanceConfig_set_extend_balance(envoy_config_listener_v3_Listener_ConnectionBalanceConfig *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_mutable_extend_balance(envoy_config_listener_v3_Listener_ConnectionBalanceConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_listener_v3_Listener_ConnectionBalanceConfig_extend_balance(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_listener_v3_Listener_ConnectionBalanceConfig_set_extend_balance(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance*)_upb_Message_New(&envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* ret = envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* ret = envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance_serialize(const envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance_serialize_ex(const envoy_config_listener_v3_Listener_ConnectionBalanceConfig_ExactBalance* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_listener_v3_Listener_InternalListenerConfig* envoy_config_listener_v3_Listener_InternalListenerConfig_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_Listener_InternalListenerConfig*)_upb_Message_New(&envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_Listener_InternalListenerConfig* envoy_config_listener_v3_Listener_InternalListenerConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_Listener_InternalListenerConfig* ret = envoy_config_listener_v3_Listener_InternalListenerConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_Listener_InternalListenerConfig* envoy_config_listener_v3_Listener_InternalListenerConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_Listener_InternalListenerConfig* ret = envoy_config_listener_v3_Listener_InternalListenerConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_Listener_InternalListenerConfig_serialize(const envoy_config_listener_v3_Listener_InternalListenerConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_Listener_InternalListenerConfig_serialize_ex(const envoy_config_listener_v3_Listener_InternalListenerConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_listener_v3_ListenerManager* envoy_config_listener_v3_ListenerManager_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_ListenerManager*)_upb_Message_New(&envoy__config__listener__v3__ListenerManager_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_ListenerManager* envoy_config_listener_v3_ListenerManager_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_ListenerManager* ret = envoy_config_listener_v3_ListenerManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ListenerManager_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_ListenerManager* envoy_config_listener_v3_ListenerManager_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_ListenerManager* ret = envoy_config_listener_v3_ListenerManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ListenerManager_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_ListenerManager_serialize(const envoy_config_listener_v3_ListenerManager* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerManager_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_ListenerManager_serialize_ex(const envoy_config_listener_v3_ListenerManager* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerManager_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_listener_v3_ValidationListenerManager* envoy_config_listener_v3_ValidationListenerManager_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_ValidationListenerManager*)_upb_Message_New(&envoy__config__listener__v3__ValidationListenerManager_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_ValidationListenerManager* envoy_config_listener_v3_ValidationListenerManager_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_ValidationListenerManager* ret = envoy_config_listener_v3_ValidationListenerManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ValidationListenerManager_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_ValidationListenerManager* envoy_config_listener_v3_ValidationListenerManager_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_ValidationListenerManager* ret = envoy_config_listener_v3_ValidationListenerManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ValidationListenerManager_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_ValidationListenerManager_serialize(const envoy_config_listener_v3_ValidationListenerManager* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ValidationListenerManager_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_ValidationListenerManager_serialize_ex(const envoy_config_listener_v3_ValidationListenerManager* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ValidationListenerManager_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_config_listener_v3_ApiListenerManager* envoy_config_listener_v3_ApiListenerManager_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_ApiListenerManager*)_upb_Message_New(&envoy__config__listener__v3__ApiListenerManager_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_ApiListenerManager* envoy_config_listener_v3_ApiListenerManager_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_ApiListenerManager* ret = envoy_config_listener_v3_ApiListenerManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ApiListenerManager_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_ApiListenerManager* envoy_config_listener_v3_ApiListenerManager_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_ApiListenerManager* ret = envoy_config_listener_v3_ApiListenerManager_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ApiListenerManager_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_ApiListenerManager_serialize(const envoy_config_listener_v3_ApiListenerManager* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ApiListenerManager_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_ApiListenerManager_serialize_ex(const envoy_config_listener_v3_ApiListenerManager* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ApiListenerManager_msg_init, options, arena, &ptr, len);
  return ptr;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
