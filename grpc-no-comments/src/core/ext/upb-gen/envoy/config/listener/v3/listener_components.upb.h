
#ifndef ENVOY_CONFIG_LISTENER_V3_LISTENER_COMPONENTS_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_LISTENER_V3_LISTENER_COMPONENTS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/listener/v3/listener_components.upb_minitable.h"

#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "envoy/type/v3/range.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_listener_v3_Filter { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_Filter;
typedef struct envoy_config_listener_v3_FilterChainMatch { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_FilterChainMatch;
typedef struct envoy_config_listener_v3_FilterChain { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_FilterChain;
typedef struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_ListenerFilterChainMatchPredicate;
typedef struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet;
typedef struct envoy_config_listener_v3_ListenerFilter { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_ListenerFilter;
struct envoy_config_core_v3_CidrRange;
struct envoy_config_core_v3_ExtensionConfigSource;
struct envoy_config_core_v3_Metadata;
struct envoy_config_core_v3_TransportSocket;
struct envoy_type_v3_Int32Range;
struct google_protobuf_Any;
struct google_protobuf_BoolValue;
struct google_protobuf_Duration;
struct google_protobuf_UInt32Value;

typedef enum {
  envoy_config_listener_v3_FilterChainMatch_ANY = 0,
  envoy_config_listener_v3_FilterChainMatch_SAME_IP_OR_LOOPBACK = 1,
  envoy_config_listener_v3_FilterChainMatch_EXTERNAL = 2
} envoy_config_listener_v3_FilterChainMatch_ConnectionSourceType;

UPB_INLINE envoy_config_listener_v3_Filter* envoy_config_listener_v3_Filter_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_Filter*)_upb_Message_New(&envoy__config__listener__v3__Filter_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_Filter* envoy_config_listener_v3_Filter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_Filter* ret = envoy_config_listener_v3_Filter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Filter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_Filter* envoy_config_listener_v3_Filter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_Filter* ret = envoy_config_listener_v3_Filter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__Filter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_Filter_serialize(const envoy_config_listener_v3_Filter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Filter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_Filter_serialize_ex(const envoy_config_listener_v3_Filter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__Filter_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_listener_v3_Filter_config_type_typed_config = 4,
  envoy_config_listener_v3_Filter_config_type_config_discovery = 5,
  envoy_config_listener_v3_Filter_config_type_NOT_SET = 0
} envoy_config_listener_v3_Filter_config_type_oneofcases;
UPB_INLINE envoy_config_listener_v3_Filter_config_type_oneofcases envoy_config_listener_v3_Filter_config_type_case(const envoy_config_listener_v3_Filter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_listener_v3_Filter_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Filter_clear_config_type(envoy_config_listener_v3_Filter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__listener__v3__Filter_msg_init, &field);
}
UPB_INLINE void envoy_config_listener_v3_Filter_clear_name(envoy_config_listener_v3_Filter* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_listener_v3_Filter_name(const envoy_config_listener_v3_Filter* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_Filter_clear_typed_config(envoy_config_listener_v3_Filter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_listener_v3_Filter_typed_config(const envoy_config_listener_v3_Filter* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Filter_has_typed_config(const envoy_config_listener_v3_Filter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_Filter_clear_config_discovery(envoy_config_listener_v3_Filter* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ExtensionConfigSource* envoy_config_listener_v3_Filter_config_discovery(const envoy_config_listener_v3_Filter* msg) {
  const struct envoy_config_core_v3_ExtensionConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ExtensionConfigSource* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ExtensionConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_Filter_has_config_discovery(const envoy_config_listener_v3_Filter* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_listener_v3_Filter_set_name(envoy_config_listener_v3_Filter *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_Filter_set_typed_config(envoy_config_listener_v3_Filter *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_listener_v3_Filter_mutable_typed_config(envoy_config_listener_v3_Filter* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_listener_v3_Filter_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_listener_v3_Filter_set_typed_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_Filter_set_config_discovery(envoy_config_listener_v3_Filter *msg, struct envoy_config_core_v3_ExtensionConfigSource* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ExtensionConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ExtensionConfigSource* envoy_config_listener_v3_Filter_mutable_config_discovery(envoy_config_listener_v3_Filter* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ExtensionConfigSource* sub = (struct envoy_config_core_v3_ExtensionConfigSource*)envoy_config_listener_v3_Filter_config_discovery(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ExtensionConfigSource*)_upb_Message_New(&envoy__config__core__v3__ExtensionConfigSource_msg_init, arena);
    if (sub) envoy_config_listener_v3_Filter_set_config_discovery(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_listener_v3_FilterChainMatch* envoy_config_listener_v3_FilterChainMatch_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_FilterChainMatch*)_upb_Message_New(&envoy__config__listener__v3__FilterChainMatch_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_FilterChainMatch* envoy_config_listener_v3_FilterChainMatch_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_FilterChainMatch* ret = envoy_config_listener_v3_FilterChainMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__FilterChainMatch_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_FilterChainMatch* envoy_config_listener_v3_FilterChainMatch_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_FilterChainMatch* ret = envoy_config_listener_v3_FilterChainMatch_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__FilterChainMatch_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_FilterChainMatch_serialize(const envoy_config_listener_v3_FilterChainMatch* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__FilterChainMatch_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_FilterChainMatch_serialize_ex(const envoy_config_listener_v3_FilterChainMatch* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__FilterChainMatch_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_CidrRange* const* envoy_config_listener_v3_FilterChainMatch_prefix_ranges(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_CidrRange* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_FilterChainMatch_prefix_ranges_upb_array(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_FilterChainMatch_prefix_ranges_mutable_upb_array(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_address_suffix(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_listener_v3_FilterChainMatch_address_suffix(const envoy_config_listener_v3_FilterChainMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(48, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_suffix_len(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_listener_v3_FilterChainMatch_suffix_len(const envoy_config_listener_v3_FilterChainMatch* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_FilterChainMatch_has_suffix_len(const envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_source_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_CidrRange* const* envoy_config_listener_v3_FilterChainMatch_source_prefix_ranges(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_CidrRange* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_FilterChainMatch_source_prefix_ranges_upb_array(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_FilterChainMatch_source_prefix_ranges_mutable_upb_array(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_source_ports(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t const* envoy_config_listener_v3_FilterChainMatch_source_ports(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_FilterChainMatch_source_ports_upb_array(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_FilterChainMatch_source_ports_mutable_upb_array(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_destination_port(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 80), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_listener_v3_FilterChainMatch_destination_port(const envoy_config_listener_v3_FilterChainMatch* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(28, 80), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_FilterChainMatch_has_destination_port(const envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 80), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_transport_protocol(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(56, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_listener_v3_FilterChainMatch_transport_protocol(const envoy_config_listener_v3_FilterChainMatch* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {9, UPB_SIZE(56, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_application_protocols(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_listener_v3_FilterChainMatch_application_protocols(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_FilterChainMatch_application_protocols_upb_array(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_FilterChainMatch_application_protocols_mutable_upb_array(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {10, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_server_names(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_listener_v3_FilterChainMatch_server_names(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_FilterChainMatch_server_names_upb_array(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_FilterChainMatch_server_names_mutable_upb_array(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {11, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_source_type(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(40, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_listener_v3_FilterChainMatch_source_type(const envoy_config_listener_v3_FilterChainMatch* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {12, UPB_SIZE(40, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_clear_direct_source_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(44, 104), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_CidrRange* const* envoy_config_listener_v3_FilterChainMatch_direct_source_prefix_ranges(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(44, 104), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_CidrRange* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_FilterChainMatch_direct_source_prefix_ranges_upb_array(const envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  const upb_MiniTableField field = {13, UPB_SIZE(44, 104), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_FilterChainMatch_direct_source_prefix_ranges_mutable_upb_array(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {13, UPB_SIZE(44, 104), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_config_listener_v3_FilterChainMatch_mutable_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_CidrRange**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_config_listener_v3_FilterChainMatch_resize_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_CidrRange**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange* envoy_config_listener_v3_FilterChainMatch_add_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_CidrRange* sub = (struct envoy_config_core_v3_CidrRange*)_upb_Message_New(&envoy__config__core__v3__CidrRange_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_set_address_suffix(envoy_config_listener_v3_FilterChainMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_set_suffix_len(envoy_config_listener_v3_FilterChainMatch *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_listener_v3_FilterChainMatch_mutable_suffix_len(envoy_config_listener_v3_FilterChainMatch* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_listener_v3_FilterChainMatch_suffix_len(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_listener_v3_FilterChainMatch_set_suffix_len(msg, sub);
  }
  return sub;
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_config_listener_v3_FilterChainMatch_mutable_source_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_CidrRange**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_config_listener_v3_FilterChainMatch_resize_source_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_CidrRange**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange* envoy_config_listener_v3_FilterChainMatch_add_source_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(20, 64), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_CidrRange* sub = (struct envoy_config_core_v3_CidrRange*)_upb_Message_New(&envoy__config__core__v3__CidrRange_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE uint32_t* envoy_config_listener_v3_FilterChainMatch_mutable_source_ports(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  upb_MiniTableField field = {7, UPB_SIZE(24, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (uint32_t*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE uint32_t* envoy_config_listener_v3_FilterChainMatch_resize_source_ports(envoy_config_listener_v3_FilterChainMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(24, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (uint32_t*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_listener_v3_FilterChainMatch_add_source_ports(envoy_config_listener_v3_FilterChainMatch* msg, uint32_t val, upb_Arena* arena) {
  upb_MiniTableField field = {7, UPB_SIZE(24, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_set_destination_port(envoy_config_listener_v3_FilterChainMatch *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(28, 80), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_listener_v3_FilterChainMatch_mutable_destination_port(envoy_config_listener_v3_FilterChainMatch* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_listener_v3_FilterChainMatch_destination_port(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_listener_v3_FilterChainMatch_set_destination_port(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_set_transport_protocol(envoy_config_listener_v3_FilterChainMatch *msg, upb_StringView value) {
  const upb_MiniTableField field = {9, UPB_SIZE(56, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* envoy_config_listener_v3_FilterChainMatch_mutable_application_protocols(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  upb_MiniTableField field = {10, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_listener_v3_FilterChainMatch_resize_application_protocols(envoy_config_listener_v3_FilterChainMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_listener_v3_FilterChainMatch_add_application_protocols(envoy_config_listener_v3_FilterChainMatch* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE upb_StringView* envoy_config_listener_v3_FilterChainMatch_mutable_server_names(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  upb_MiniTableField field = {11, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_listener_v3_FilterChainMatch_resize_server_names(envoy_config_listener_v3_FilterChainMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_listener_v3_FilterChainMatch_add_server_names(envoy_config_listener_v3_FilterChainMatch* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_config_listener_v3_FilterChainMatch_set_source_type(envoy_config_listener_v3_FilterChainMatch *msg, int32_t value) {
  const upb_MiniTableField field = {12, UPB_SIZE(40, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_config_listener_v3_FilterChainMatch_mutable_direct_source_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg, size_t* size) {
  upb_MiniTableField field = {13, UPB_SIZE(44, 104), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_CidrRange**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_CidrRange** envoy_config_listener_v3_FilterChainMatch_resize_direct_source_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(44, 104), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_CidrRange**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_CidrRange* envoy_config_listener_v3_FilterChainMatch_add_direct_source_prefix_ranges(envoy_config_listener_v3_FilterChainMatch* msg, upb_Arena* arena) {
  upb_MiniTableField field = {13, UPB_SIZE(44, 104), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__CidrRange_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_CidrRange* sub = (struct envoy_config_core_v3_CidrRange*)_upb_Message_New(&envoy__config__core__v3__CidrRange_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_listener_v3_FilterChain* envoy_config_listener_v3_FilterChain_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_FilterChain*)_upb_Message_New(&envoy__config__listener__v3__FilterChain_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_FilterChain* envoy_config_listener_v3_FilterChain_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_FilterChain* ret = envoy_config_listener_v3_FilterChain_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__FilterChain_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_FilterChain* envoy_config_listener_v3_FilterChain_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_FilterChain* ret = envoy_config_listener_v3_FilterChain_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__FilterChain_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_FilterChain_serialize(const envoy_config_listener_v3_FilterChain* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__FilterChain_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_FilterChain_serialize_ex(const envoy_config_listener_v3_FilterChain* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__FilterChain_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_clear_filter_chain_match(envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_FilterChainMatch* envoy_config_listener_v3_FilterChain_filter_chain_match(const envoy_config_listener_v3_FilterChain* msg) {
  const envoy_config_listener_v3_FilterChainMatch* default_val = NULL;
  const envoy_config_listener_v3_FilterChainMatch* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__FilterChainMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_FilterChain_has_filter_chain_match(const envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_clear_filters(envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_Filter* const* envoy_config_listener_v3_FilterChain_filters(const envoy_config_listener_v3_FilterChain* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Filter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_listener_v3_Filter* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_FilterChain_filters_upb_array(const envoy_config_listener_v3_FilterChain* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Filter_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_FilterChain_filters_mutable_upb_array(envoy_config_listener_v3_FilterChain* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Filter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_clear_use_proxy_proto(envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_listener_v3_FilterChain_use_proxy_proto(const envoy_config_listener_v3_FilterChain* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_FilterChain_has_use_proxy_proto(const envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_clear_metadata(envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Metadata* envoy_config_listener_v3_FilterChain_metadata(const envoy_config_listener_v3_FilterChain* msg) {
  const struct envoy_config_core_v3_Metadata* default_val = NULL;
  const struct envoy_config_core_v3_Metadata* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_FilterChain_has_metadata(const envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_clear_transport_socket(envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TransportSocket* envoy_config_listener_v3_FilterChain_transport_socket(const envoy_config_listener_v3_FilterChain* msg) {
  const struct envoy_config_core_v3_TransportSocket* default_val = NULL;
  const struct envoy_config_core_v3_TransportSocket* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TransportSocket_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_FilterChain_has_transport_socket(const envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_clear_name(envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_listener_v3_FilterChain_name(const envoy_config_listener_v3_FilterChain* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, UPB_SIZE(36, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_clear_transport_socket_connect_timeout(envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 72), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* envoy_config_listener_v3_FilterChain_transport_socket_connect_timeout(const envoy_config_listener_v3_FilterChain* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {9, UPB_SIZE(32, 72), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_FilterChain_has_transport_socket_connect_timeout(const envoy_config_listener_v3_FilterChain* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 72), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_listener_v3_FilterChain_set_filter_chain_match(envoy_config_listener_v3_FilterChain *msg, envoy_config_listener_v3_FilterChainMatch* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__FilterChainMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_FilterChainMatch* envoy_config_listener_v3_FilterChain_mutable_filter_chain_match(envoy_config_listener_v3_FilterChain* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_FilterChainMatch* sub = (struct envoy_config_listener_v3_FilterChainMatch*)envoy_config_listener_v3_FilterChain_filter_chain_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_FilterChainMatch*)_upb_Message_New(&envoy__config__listener__v3__FilterChainMatch_msg_init, arena);
    if (sub) envoy_config_listener_v3_FilterChain_set_filter_chain_match(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_listener_v3_Filter** envoy_config_listener_v3_FilterChain_mutable_filters(envoy_config_listener_v3_FilterChain* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Filter_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_listener_v3_Filter**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_listener_v3_Filter** envoy_config_listener_v3_FilterChain_resize_filters(envoy_config_listener_v3_FilterChain* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_listener_v3_Filter**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_listener_v3_Filter* envoy_config_listener_v3_FilterChain_add_filters(envoy_config_listener_v3_FilterChain* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__Filter_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_listener_v3_Filter* sub = (struct envoy_config_listener_v3_Filter*)_upb_Message_New(&envoy__config__listener__v3__Filter_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_set_use_proxy_proto(envoy_config_listener_v3_FilterChain *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_listener_v3_FilterChain_mutable_use_proxy_proto(envoy_config_listener_v3_FilterChain* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_listener_v3_FilterChain_use_proxy_proto(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_listener_v3_FilterChain_set_use_proxy_proto(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_set_metadata(envoy_config_listener_v3_FilterChain *msg, struct envoy_config_core_v3_Metadata* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Metadata* envoy_config_listener_v3_FilterChain_mutable_metadata(envoy_config_listener_v3_FilterChain* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Metadata* sub = (struct envoy_config_core_v3_Metadata*)envoy_config_listener_v3_FilterChain_metadata(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Metadata*)_upb_Message_New(&envoy__config__core__v3__Metadata_msg_init, arena);
    if (sub) envoy_config_listener_v3_FilterChain_set_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_set_transport_socket(envoy_config_listener_v3_FilterChain *msg, struct envoy_config_core_v3_TransportSocket* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 64), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TransportSocket_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TransportSocket* envoy_config_listener_v3_FilterChain_mutable_transport_socket(envoy_config_listener_v3_FilterChain* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TransportSocket* sub = (struct envoy_config_core_v3_TransportSocket*)envoy_config_listener_v3_FilterChain_transport_socket(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TransportSocket*)_upb_Message_New(&envoy__config__core__v3__TransportSocket_msg_init, arena);
    if (sub) envoy_config_listener_v3_FilterChain_set_transport_socket(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_set_name(envoy_config_listener_v3_FilterChain *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, UPB_SIZE(36, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_FilterChain_set_transport_socket_connect_timeout(envoy_config_listener_v3_FilterChain *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {9, UPB_SIZE(32, 72), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* envoy_config_listener_v3_FilterChain_mutable_transport_socket_connect_timeout(envoy_config_listener_v3_FilterChain* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)envoy_config_listener_v3_FilterChain_transport_socket_connect_timeout(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) envoy_config_listener_v3_FilterChain_set_transport_socket_connect_timeout(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_listener_v3_ListenerFilterChainMatchPredicate* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_ListenerFilterChainMatchPredicate*)_upb_Message_New(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_ListenerFilterChainMatchPredicate* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_ListenerFilterChainMatchPredicate* ret = envoy_config_listener_v3_ListenerFilterChainMatchPredicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_ListenerFilterChainMatchPredicate* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_ListenerFilterChainMatchPredicate* ret = envoy_config_listener_v3_ListenerFilterChainMatchPredicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_serialize(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_serialize_ex(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_listener_v3_ListenerFilterChainMatchPredicate_rule_or_match = 1,
  envoy_config_listener_v3_ListenerFilterChainMatchPredicate_rule_and_match = 2,
  envoy_config_listener_v3_ListenerFilterChainMatchPredicate_rule_not_match = 3,
  envoy_config_listener_v3_ListenerFilterChainMatchPredicate_rule_any_match = 4,
  envoy_config_listener_v3_ListenerFilterChainMatchPredicate_rule_destination_port_range = 5,
  envoy_config_listener_v3_ListenerFilterChainMatchPredicate_rule_NOT_SET = 0
} envoy_config_listener_v3_ListenerFilterChainMatchPredicate_rule_oneofcases;
UPB_INLINE envoy_config_listener_v3_ListenerFilterChainMatchPredicate_rule_oneofcases envoy_config_listener_v3_ListenerFilterChainMatchPredicate_rule_case(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_listener_v3_ListenerFilterChainMatchPredicate_rule_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_clear_rule(envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init, &field);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_clear_or_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_or_match(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* default_val = NULL;
  const envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_ListenerFilterChainMatchPredicate_has_or_match(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_clear_and_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_and_match(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* default_val = NULL;
  const envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_ListenerFilterChainMatchPredicate_has_and_match(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_clear_not_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_not_match(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* default_val = NULL;
  const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_ListenerFilterChainMatchPredicate_has_not_match(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_clear_any_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_listener_v3_ListenerFilterChainMatchPredicate_any_match(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_ListenerFilterChainMatchPredicate_has_any_match(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_clear_destination_port_range(envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Int32Range* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_destination_port_range(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const struct envoy_type_v3_Int32Range* default_val = NULL;
  const struct envoy_type_v3_Int32Range* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int32Range_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_ListenerFilterChainMatchPredicate_has_destination_port_range(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_set_or_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate *msg, envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_mutable_or_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* sub = (struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet*)envoy_config_listener_v3_ListenerFilterChainMatchPredicate_or_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet*)_upb_Message_New(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init, arena);
    if (sub) envoy_config_listener_v3_ListenerFilterChainMatchPredicate_set_or_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_set_and_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate *msg, envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_mutable_and_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* sub = (struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet*)envoy_config_listener_v3_ListenerFilterChainMatchPredicate_and_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet*)_upb_Message_New(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init, arena);
    if (sub) envoy_config_listener_v3_ListenerFilterChainMatchPredicate_set_and_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_set_not_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate *msg, envoy_config_listener_v3_ListenerFilterChainMatchPredicate* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_mutable_not_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate* sub = (struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate*)envoy_config_listener_v3_ListenerFilterChainMatchPredicate_not_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate*)_upb_Message_New(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init, arena);
    if (sub) envoy_config_listener_v3_ListenerFilterChainMatchPredicate_set_not_match(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_set_any_match(envoy_config_listener_v3_ListenerFilterChainMatchPredicate *msg, bool value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_set_destination_port_range(envoy_config_listener_v3_ListenerFilterChainMatchPredicate *msg, struct envoy_type_v3_Int32Range* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Int32Range_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Int32Range* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_mutable_destination_port_range(envoy_config_listener_v3_ListenerFilterChainMatchPredicate* msg, upb_Arena* arena) {
  struct envoy_type_v3_Int32Range* sub = (struct envoy_type_v3_Int32Range*)envoy_config_listener_v3_ListenerFilterChainMatchPredicate_destination_port_range(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Int32Range*)_upb_Message_New(&envoy__type__v3__Int32Range_msg_init, arena);
    if (sub) envoy_config_listener_v3_ListenerFilterChainMatchPredicate_set_destination_port_range(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet*)_upb_Message_New(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* ret = envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* ret = envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_serialize(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_serialize_ex(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerFilterChainMatchPredicate__MatchSet_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_clear_rules(envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* const* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_rules(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_rules_upb_array(const envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_rules_mutable_upb_array(envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_listener_v3_ListenerFilterChainMatchPredicate** envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_mutable_rules(envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_listener_v3_ListenerFilterChainMatchPredicate**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_listener_v3_ListenerFilterChainMatchPredicate** envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_resize_rules(envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_listener_v3_ListenerFilterChainMatchPredicate**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate* envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet_add_rules(envoy_config_listener_v3_ListenerFilterChainMatchPredicate_MatchSet* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate* sub = (struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate*)_upb_Message_New(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_listener_v3_ListenerFilter* envoy_config_listener_v3_ListenerFilter_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_ListenerFilter*)_upb_Message_New(&envoy__config__listener__v3__ListenerFilter_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_ListenerFilter* envoy_config_listener_v3_ListenerFilter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_ListenerFilter* ret = envoy_config_listener_v3_ListenerFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ListenerFilter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_ListenerFilter* envoy_config_listener_v3_ListenerFilter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_ListenerFilter* ret = envoy_config_listener_v3_ListenerFilter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ListenerFilter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_ListenerFilter_serialize(const envoy_config_listener_v3_ListenerFilter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerFilter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_ListenerFilter_serialize_ex(const envoy_config_listener_v3_ListenerFilter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerFilter_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_listener_v3_ListenerFilter_config_type_typed_config = 3,
  envoy_config_listener_v3_ListenerFilter_config_type_config_discovery = 5,
  envoy_config_listener_v3_ListenerFilter_config_type_NOT_SET = 0
} envoy_config_listener_v3_ListenerFilter_config_type_oneofcases;
UPB_INLINE envoy_config_listener_v3_ListenerFilter_config_type_oneofcases envoy_config_listener_v3_ListenerFilter_config_type_case(const envoy_config_listener_v3_ListenerFilter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_listener_v3_ListenerFilter_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilter_clear_config_type(envoy_config_listener_v3_ListenerFilter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__listener__v3__ListenerFilter_msg_init, &field);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilter_clear_name(envoy_config_listener_v3_ListenerFilter* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_listener_v3_ListenerFilter_name(const envoy_config_listener_v3_ListenerFilter* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilter_clear_typed_config(envoy_config_listener_v3_ListenerFilter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_listener_v3_ListenerFilter_typed_config(const envoy_config_listener_v3_ListenerFilter* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_ListenerFilter_has_typed_config(const envoy_config_listener_v3_ListenerFilter* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilter_clear_filter_disabled(envoy_config_listener_v3_ListenerFilter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* envoy_config_listener_v3_ListenerFilter_filter_disabled(const envoy_config_listener_v3_ListenerFilter* msg) {
  const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* default_val = NULL;
  const envoy_config_listener_v3_ListenerFilterChainMatchPredicate* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_ListenerFilter_has_filter_disabled(const envoy_config_listener_v3_ListenerFilter* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilter_clear_config_discovery(envoy_config_listener_v3_ListenerFilter* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_ExtensionConfigSource* envoy_config_listener_v3_ListenerFilter_config_discovery(const envoy_config_listener_v3_ListenerFilter* msg) {
  const struct envoy_config_core_v3_ExtensionConfigSource* default_val = NULL;
  const struct envoy_config_core_v3_ExtensionConfigSource* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ExtensionConfigSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_ListenerFilter_has_config_discovery(const envoy_config_listener_v3_ListenerFilter* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_listener_v3_ListenerFilter_set_name(envoy_config_listener_v3_ListenerFilter *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilter_set_typed_config(envoy_config_listener_v3_ListenerFilter *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_listener_v3_ListenerFilter_mutable_typed_config(envoy_config_listener_v3_ListenerFilter* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_listener_v3_ListenerFilter_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_listener_v3_ListenerFilter_set_typed_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilter_set_filter_disabled(envoy_config_listener_v3_ListenerFilter *msg, envoy_config_listener_v3_ListenerFilterChainMatchPredicate* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate* envoy_config_listener_v3_ListenerFilter_mutable_filter_disabled(envoy_config_listener_v3_ListenerFilter* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate* sub = (struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate*)envoy_config_listener_v3_ListenerFilter_filter_disabled(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_ListenerFilterChainMatchPredicate*)_upb_Message_New(&envoy__config__listener__v3__ListenerFilterChainMatchPredicate_msg_init, arena);
    if (sub) envoy_config_listener_v3_ListenerFilter_set_filter_disabled(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_ListenerFilter_set_config_discovery(envoy_config_listener_v3_ListenerFilter *msg, struct envoy_config_core_v3_ExtensionConfigSource* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__ExtensionConfigSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_ExtensionConfigSource* envoy_config_listener_v3_ListenerFilter_mutable_config_discovery(envoy_config_listener_v3_ListenerFilter* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_ExtensionConfigSource* sub = (struct envoy_config_core_v3_ExtensionConfigSource*)envoy_config_listener_v3_ListenerFilter_config_discovery(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_ExtensionConfigSource*)_upb_Message_New(&envoy__config__core__v3__ExtensionConfigSource_msg_init, arena);
    if (sub) envoy_config_listener_v3_ListenerFilter_set_config_discovery(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
