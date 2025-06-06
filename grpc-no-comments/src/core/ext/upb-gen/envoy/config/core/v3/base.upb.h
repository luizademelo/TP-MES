
#ifndef ENVOY_CONFIG_CORE_V3_BASE_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_CORE_V3_BASE_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/core/v3/base.upb_minitable.h"

#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/backoff.upb_minitable.h"
#include "envoy/config/core/v3/http_uri.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "envoy/type/v3/semantic_version.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "xds/core/v3/context_params.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_core_v3_Locality { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_Locality;
typedef struct envoy_config_core_v3_BuildVersion { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_BuildVersion;
typedef struct envoy_config_core_v3_Extension { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_Extension;
typedef struct envoy_config_core_v3_Node { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_Node;
typedef struct envoy_config_core_v3_Metadata { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_Metadata;
typedef struct envoy_config_core_v3_RuntimeUInt32 { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_RuntimeUInt32;
typedef struct envoy_config_core_v3_RuntimePercent { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_RuntimePercent;
typedef struct envoy_config_core_v3_RuntimeDouble { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_RuntimeDouble;
typedef struct envoy_config_core_v3_RuntimeFeatureFlag { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_RuntimeFeatureFlag;
typedef struct envoy_config_core_v3_KeyValue { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_KeyValue;
typedef struct envoy_config_core_v3_KeyValuePair { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_KeyValuePair;
typedef struct envoy_config_core_v3_KeyValueAppend { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_KeyValueAppend;
typedef struct envoy_config_core_v3_KeyValueMutation { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_KeyValueMutation;
typedef struct envoy_config_core_v3_QueryParameter { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_QueryParameter;
typedef struct envoy_config_core_v3_HeaderValue { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HeaderValue;
typedef struct envoy_config_core_v3_HeaderValueOption { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HeaderValueOption;
typedef struct envoy_config_core_v3_HeaderMap { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_HeaderMap;
typedef struct envoy_config_core_v3_WatchedDirectory { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_WatchedDirectory;
typedef struct envoy_config_core_v3_DataSource { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_DataSource;
typedef struct envoy_config_core_v3_RetryPolicy { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_RetryPolicy;
typedef struct envoy_config_core_v3_RetryPolicy_RetryPriority { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_RetryPolicy_RetryPriority;
typedef struct envoy_config_core_v3_RetryPolicy_RetryHostPredicate { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_RetryPolicy_RetryHostPredicate;
typedef struct envoy_config_core_v3_RemoteDataSource { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_RemoteDataSource;
typedef struct envoy_config_core_v3_AsyncDataSource { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_AsyncDataSource;
typedef struct envoy_config_core_v3_TransportSocket { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_TransportSocket;
typedef struct envoy_config_core_v3_RuntimeFractionalPercent { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_RuntimeFractionalPercent;
typedef struct envoy_config_core_v3_ControlPlane { upb_Message UPB_PRIVATE(base); } envoy_config_core_v3_ControlPlane;
struct envoy_config_core_v3_Address;
struct envoy_config_core_v3_BackoffStrategy;
struct envoy_config_core_v3_HttpUri;
struct envoy_type_v3_FractionalPercent;
struct envoy_type_v3_Percent;
struct envoy_type_v3_SemanticVersion;
struct google_protobuf_Any;
struct google_protobuf_BoolValue;
struct google_protobuf_Struct;
struct google_protobuf_UInt32Value;
struct google_protobuf_Value;

typedef enum {
  envoy_config_core_v3_HeaderValueOption_APPEND_IF_EXISTS_OR_ADD = 0,
  envoy_config_core_v3_HeaderValueOption_ADD_IF_ABSENT = 1,
  envoy_config_core_v3_HeaderValueOption_OVERWRITE_IF_EXISTS_OR_ADD = 2,
  envoy_config_core_v3_HeaderValueOption_OVERWRITE_IF_EXISTS = 3
} envoy_config_core_v3_HeaderValueOption_HeaderAppendAction;

typedef enum {
  envoy_config_core_v3_KeyValueAppend_APPEND_IF_EXISTS_OR_ADD = 0,
  envoy_config_core_v3_KeyValueAppend_ADD_IF_ABSENT = 1,
  envoy_config_core_v3_KeyValueAppend_OVERWRITE_IF_EXISTS_OR_ADD = 2,
  envoy_config_core_v3_KeyValueAppend_OVERWRITE_IF_EXISTS = 3
} envoy_config_core_v3_KeyValueAppend_KeyValueAppendAction;

typedef enum {
  envoy_config_core_v3_METHOD_UNSPECIFIED = 0,
  envoy_config_core_v3_GET = 1,
  envoy_config_core_v3_HEAD = 2,
  envoy_config_core_v3_POST = 3,
  envoy_config_core_v3_PUT = 4,
  envoy_config_core_v3_DELETE = 5,
  envoy_config_core_v3_CONNECT = 6,
  envoy_config_core_v3_OPTIONS = 7,
  envoy_config_core_v3_TRACE = 8,
  envoy_config_core_v3_PATCH = 9
} envoy_config_core_v3_RequestMethod;

typedef enum {
  envoy_config_core_v3_DEFAULT = 0,
  envoy_config_core_v3_HIGH = 1
} envoy_config_core_v3_RoutingPriority;

typedef enum {
  envoy_config_core_v3_UNSPECIFIED = 0,
  envoy_config_core_v3_INBOUND = 1,
  envoy_config_core_v3_OUTBOUND = 2
} envoy_config_core_v3_TrafficDirection;

UPB_INLINE envoy_config_core_v3_Locality* envoy_config_core_v3_Locality_new(upb_Arena* arena) {
  return (envoy_config_core_v3_Locality*)_upb_Message_New(&envoy__config__core__v3__Locality_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_Locality* envoy_config_core_v3_Locality_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_Locality* ret = envoy_config_core_v3_Locality_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__Locality_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_Locality* envoy_config_core_v3_Locality_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_Locality* ret = envoy_config_core_v3_Locality_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__Locality_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_Locality_serialize(const envoy_config_core_v3_Locality* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__Locality_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_Locality_serialize_ex(const envoy_config_core_v3_Locality* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__Locality_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_Locality_clear_region(envoy_config_core_v3_Locality* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_Locality_region(const envoy_config_core_v3_Locality* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_Locality_clear_zone(envoy_config_core_v3_Locality* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_Locality_zone(const envoy_config_core_v3_Locality* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_Locality_clear_sub_zone(envoy_config_core_v3_Locality* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_Locality_sub_zone(const envoy_config_core_v3_Locality* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_Locality_set_region(envoy_config_core_v3_Locality *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_Locality_set_zone(envoy_config_core_v3_Locality *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_Locality_set_sub_zone(envoy_config_core_v3_Locality *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_BuildVersion* envoy_config_core_v3_BuildVersion_new(upb_Arena* arena) {
  return (envoy_config_core_v3_BuildVersion*)_upb_Message_New(&envoy__config__core__v3__BuildVersion_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_BuildVersion* envoy_config_core_v3_BuildVersion_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_BuildVersion* ret = envoy_config_core_v3_BuildVersion_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__BuildVersion_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_BuildVersion* envoy_config_core_v3_BuildVersion_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_BuildVersion* ret = envoy_config_core_v3_BuildVersion_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__BuildVersion_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_BuildVersion_serialize(const envoy_config_core_v3_BuildVersion* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__BuildVersion_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_BuildVersion_serialize_ex(const envoy_config_core_v3_BuildVersion* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__BuildVersion_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_BuildVersion_clear_version(envoy_config_core_v3_BuildVersion* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_SemanticVersion* envoy_config_core_v3_BuildVersion_version(const envoy_config_core_v3_BuildVersion* msg) {
  const struct envoy_type_v3_SemanticVersion* default_val = NULL;
  const struct envoy_type_v3_SemanticVersion* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__SemanticVersion_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_BuildVersion_has_version(const envoy_config_core_v3_BuildVersion* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_BuildVersion_clear_metadata(envoy_config_core_v3_BuildVersion* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_core_v3_BuildVersion_metadata(const envoy_config_core_v3_BuildVersion* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_BuildVersion_has_metadata(const envoy_config_core_v3_BuildVersion* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_BuildVersion_set_version(envoy_config_core_v3_BuildVersion *msg, struct envoy_type_v3_SemanticVersion* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__SemanticVersion_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_SemanticVersion* envoy_config_core_v3_BuildVersion_mutable_version(envoy_config_core_v3_BuildVersion* msg, upb_Arena* arena) {
  struct envoy_type_v3_SemanticVersion* sub = (struct envoy_type_v3_SemanticVersion*)envoy_config_core_v3_BuildVersion_version(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_SemanticVersion*)_upb_Message_New(&envoy__type__v3__SemanticVersion_msg_init, arena);
    if (sub) envoy_config_core_v3_BuildVersion_set_version(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_BuildVersion_set_metadata(envoy_config_core_v3_BuildVersion *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_core_v3_BuildVersion_mutable_metadata(envoy_config_core_v3_BuildVersion* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_core_v3_BuildVersion_metadata(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_core_v3_BuildVersion_set_metadata(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_Extension* envoy_config_core_v3_Extension_new(upb_Arena* arena) {
  return (envoy_config_core_v3_Extension*)_upb_Message_New(&envoy__config__core__v3__Extension_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_Extension* envoy_config_core_v3_Extension_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_Extension* ret = envoy_config_core_v3_Extension_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__Extension_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_Extension* envoy_config_core_v3_Extension_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_Extension* ret = envoy_config_core_v3_Extension_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__Extension_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_Extension_serialize(const envoy_config_core_v3_Extension* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__Extension_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_Extension_serialize_ex(const envoy_config_core_v3_Extension* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__Extension_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_Extension_clear_name(envoy_config_core_v3_Extension* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_Extension_name(const envoy_config_core_v3_Extension* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_Extension_clear_category(envoy_config_core_v3_Extension* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_Extension_category(const envoy_config_core_v3_Extension* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_Extension_clear_type_descriptor(envoy_config_core_v3_Extension* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(36, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_Extension_type_descriptor(const envoy_config_core_v3_Extension* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(36, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_Extension_clear_version(envoy_config_core_v3_Extension* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_BuildVersion* envoy_config_core_v3_Extension_version(const envoy_config_core_v3_Extension* msg) {
  const envoy_config_core_v3_BuildVersion* default_val = NULL;
  const envoy_config_core_v3_BuildVersion* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__BuildVersion_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_Extension_has_version(const envoy_config_core_v3_Extension* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_Extension_clear_disabled(envoy_config_core_v3_Extension* msg) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_core_v3_Extension_disabled(const envoy_config_core_v3_Extension* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_Extension_clear_type_urls(envoy_config_core_v3_Extension* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_core_v3_Extension_type_urls(const envoy_config_core_v3_Extension* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_Extension_type_urls_upb_array(const envoy_config_core_v3_Extension* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_Extension_type_urls_mutable_upb_array(envoy_config_core_v3_Extension* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(16, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_core_v3_Extension_set_name(envoy_config_core_v3_Extension *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_Extension_set_category(envoy_config_core_v3_Extension *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_Extension_set_type_descriptor(envoy_config_core_v3_Extension *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(36, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_Extension_set_version(envoy_config_core_v3_Extension *msg, envoy_config_core_v3_BuildVersion* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__BuildVersion_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_BuildVersion* envoy_config_core_v3_Extension_mutable_version(envoy_config_core_v3_Extension* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_BuildVersion* sub = (struct envoy_config_core_v3_BuildVersion*)envoy_config_core_v3_Extension_version(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_BuildVersion*)_upb_Message_New(&envoy__config__core__v3__BuildVersion_msg_init, arena);
    if (sub) envoy_config_core_v3_Extension_set_version(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_Extension_set_disabled(envoy_config_core_v3_Extension *msg, bool value) {
  const upb_MiniTableField field = {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE upb_StringView* envoy_config_core_v3_Extension_mutable_type_urls(envoy_config_core_v3_Extension* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(16, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_core_v3_Extension_resize_type_urls(envoy_config_core_v3_Extension* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(16, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_core_v3_Extension_add_type_urls(envoy_config_core_v3_Extension* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(16, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

UPB_INLINE envoy_config_core_v3_Node* envoy_config_core_v3_Node_new(upb_Arena* arena) {
  return (envoy_config_core_v3_Node*)_upb_Message_New(&envoy__config__core__v3__Node_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_Node* envoy_config_core_v3_Node_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_Node* ret = envoy_config_core_v3_Node_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__Node_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_Node* envoy_config_core_v3_Node_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_Node* ret = envoy_config_core_v3_Node_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__Node_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_Node_serialize(const envoy_config_core_v3_Node* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__Node_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_Node_serialize_ex(const envoy_config_core_v3_Node* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__Node_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_Node_user_agent_version_type_user_agent_version = 7,
  envoy_config_core_v3_Node_user_agent_version_type_user_agent_build_version = 8,
  envoy_config_core_v3_Node_user_agent_version_type_NOT_SET = 0
} envoy_config_core_v3_Node_user_agent_version_type_oneofcases;
UPB_INLINE envoy_config_core_v3_Node_user_agent_version_type_oneofcases envoy_config_core_v3_Node_user_agent_version_type_case(const envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {7, 64, UPB_SIZE(-37, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_Node_user_agent_version_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_Node_clear_user_agent_version_type(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {7, 64, UPB_SIZE(-37, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__Node_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_Node_clear_id(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_Node_id(const envoy_config_core_v3_Node* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_Node_clear_cluster(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_Node_cluster(const envoy_config_core_v3_Node* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_Node_clear_metadata(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_config_core_v3_Node_metadata(const envoy_config_core_v3_Node* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_Node_has_metadata(const envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_Node_clear_locality(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 88), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_Locality* envoy_config_core_v3_Node_locality(const envoy_config_core_v3_Node* msg) {
  const envoy_config_core_v3_Locality* default_val = NULL;
  const envoy_config_core_v3_Locality* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(16, 88), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Locality_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_Node_has_locality(const envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 88), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_Node_clear_user_agent_name(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_Node_user_agent_name(const envoy_config_core_v3_Node* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {6, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_Node_clear_user_agent_version(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {7, 64, UPB_SIZE(-37, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_Node_user_agent_version(const envoy_config_core_v3_Node* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {7, 64, UPB_SIZE(-37, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_Node_has_user_agent_version(const envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {7, 64, UPB_SIZE(-37, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_Node_clear_user_agent_build_version(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {8, 64, UPB_SIZE(-37, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_BuildVersion* envoy_config_core_v3_Node_user_agent_build_version(const envoy_config_core_v3_Node* msg) {
  const envoy_config_core_v3_BuildVersion* default_val = NULL;
  const envoy_config_core_v3_BuildVersion* ret;
  const upb_MiniTableField field = {8, 64, UPB_SIZE(-37, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__BuildVersion_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_Node_has_user_agent_build_version(const envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {8, 64, UPB_SIZE(-37, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_Node_clear_extensions(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_Extension* const* envoy_config_core_v3_Node_extensions(const envoy_config_core_v3_Node* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Extension_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_core_v3_Extension* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_Node_extensions_upb_array(const envoy_config_core_v3_Node* msg, size_t* size) {
  const upb_MiniTableField field = {9, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Extension_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_Node_extensions_mutable_upb_array(envoy_config_core_v3_Node* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {9, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Extension_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_Node_clear_client_features(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {10, UPB_SIZE(24, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_config_core_v3_Node_client_features(const envoy_config_core_v3_Node* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(24, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_Node_client_features_upb_array(const envoy_config_core_v3_Node* msg, size_t* size) {
  const upb_MiniTableField field = {10, UPB_SIZE(24, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_Node_client_features_mutable_upb_array(envoy_config_core_v3_Node* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {10, UPB_SIZE(24, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_Node_clear_listening_addresses(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(28, 112), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* const* envoy_config_core_v3_Node_listening_addresses(const envoy_config_core_v3_Node* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(28, 112), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_core_v3_Address* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_Node_listening_addresses_upb_array(const envoy_config_core_v3_Node* msg, size_t* size) {
  const upb_MiniTableField field = {11, UPB_SIZE(28, 112), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_Node_listening_addresses_mutable_upb_array(envoy_config_core_v3_Node* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {11, UPB_SIZE(28, 112), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_Node_clear_dynamic_parameters(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 120), 0, 5, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_core_v3_Node_dynamic_parameters_size(const envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 120), 0, 5, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_core_v3_Node_dynamic_parameters_get(const envoy_config_core_v3_Node* msg, upb_StringView key, struct xds_core_v3_ContextParams** val) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 120), 0, 5, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node__DynamicParametersEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_core_v3_Node_dynamic_parameters_next(const envoy_config_core_v3_Node* msg, upb_StringView* key, const struct xds_core_v3_ContextParams** val,
                           size_t* iter) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 120), 0, 5, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node__DynamicParametersEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_config_core_v3_Node_dynamic_parameters_upb_map(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 120), 0, 5, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node__DynamicParametersEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_core_v3_Node_dynamic_parameters_mutable_upb_map(envoy_config_core_v3_Node* msg, upb_Arena* a) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 120), 0, 5, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node__DynamicParametersEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(struct xds_core_v3_ContextParams*), a);
}

UPB_INLINE void envoy_config_core_v3_Node_set_id(envoy_config_core_v3_Node *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_Node_set_cluster(envoy_config_core_v3_Node *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_Node_set_metadata(envoy_config_core_v3_Node *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_config_core_v3_Node_mutable_metadata(envoy_config_core_v3_Node* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_config_core_v3_Node_metadata(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_config_core_v3_Node_set_metadata(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_Node_set_locality(envoy_config_core_v3_Node *msg, envoy_config_core_v3_Locality* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(16, 88), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Locality_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Locality* envoy_config_core_v3_Node_mutable_locality(envoy_config_core_v3_Node* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Locality* sub = (struct envoy_config_core_v3_Locality*)envoy_config_core_v3_Node_locality(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Locality*)_upb_Message_New(&envoy__config__core__v3__Locality_msg_init, arena);
    if (sub) envoy_config_core_v3_Node_set_locality(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_Node_set_user_agent_name(envoy_config_core_v3_Node *msg, upb_StringView value) {
  const upb_MiniTableField field = {6, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_Node_set_user_agent_version(envoy_config_core_v3_Node *msg, upb_StringView value) {
  const upb_MiniTableField field = {7, 64, UPB_SIZE(-37, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_Node_set_user_agent_build_version(envoy_config_core_v3_Node *msg, envoy_config_core_v3_BuildVersion* value) {
  const upb_MiniTableField field = {8, 64, UPB_SIZE(-37, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__BuildVersion_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_BuildVersion* envoy_config_core_v3_Node_mutable_user_agent_build_version(envoy_config_core_v3_Node* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_BuildVersion* sub = (struct envoy_config_core_v3_BuildVersion*)envoy_config_core_v3_Node_user_agent_build_version(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_BuildVersion*)_upb_Message_New(&envoy__config__core__v3__BuildVersion_msg_init, arena);
    if (sub) envoy_config_core_v3_Node_set_user_agent_build_version(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_core_v3_Extension** envoy_config_core_v3_Node_mutable_extensions(envoy_config_core_v3_Node* msg, size_t* size) {
  upb_MiniTableField field = {9, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Extension_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_core_v3_Extension**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_core_v3_Extension** envoy_config_core_v3_Node_resize_extensions(envoy_config_core_v3_Node* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_Extension**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_Extension* envoy_config_core_v3_Node_add_extensions(envoy_config_core_v3_Node* msg, upb_Arena* arena) {
  upb_MiniTableField field = {9, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Extension_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_Extension* sub = (struct envoy_config_core_v3_Extension*)_upb_Message_New(&envoy__config__core__v3__Extension_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE upb_StringView* envoy_config_core_v3_Node_mutable_client_features(envoy_config_core_v3_Node* msg, size_t* size) {
  upb_MiniTableField field = {10, UPB_SIZE(24, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_config_core_v3_Node_resize_client_features(envoy_config_core_v3_Node* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(24, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_core_v3_Node_add_client_features(envoy_config_core_v3_Node* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {10, UPB_SIZE(24, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE struct envoy_config_core_v3_Address** envoy_config_core_v3_Node_mutable_listening_addresses(envoy_config_core_v3_Node* msg, size_t* size) {
  upb_MiniTableField field = {11, UPB_SIZE(28, 112), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_core_v3_Address**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_core_v3_Address** envoy_config_core_v3_Node_resize_listening_addresses(envoy_config_core_v3_Node* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(28, 112), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_core_v3_Address**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_config_core_v3_Node_add_listening_addresses(envoy_config_core_v3_Node* msg, upb_Arena* arena) {
  upb_MiniTableField field = {11, UPB_SIZE(28, 112), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_core_v3_Node_dynamic_parameters_clear(envoy_config_core_v3_Node* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 120), 0, 5, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_core_v3_Node_dynamic_parameters_set(envoy_config_core_v3_Node* msg, upb_StringView key, struct xds_core_v3_ContextParams* val, upb_Arena* a) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 120), 0, 5, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Node__DynamicParametersEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_core_v3_Node_dynamic_parameters_delete(envoy_config_core_v3_Node* msg, upb_StringView key) {
  const upb_MiniTableField field = {12, UPB_SIZE(32, 120), 0, 5, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}

UPB_INLINE envoy_config_core_v3_Metadata* envoy_config_core_v3_Metadata_new(upb_Arena* arena) {
  return (envoy_config_core_v3_Metadata*)_upb_Message_New(&envoy__config__core__v3__Metadata_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_Metadata* envoy_config_core_v3_Metadata_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_Metadata* ret = envoy_config_core_v3_Metadata_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__Metadata_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_Metadata* envoy_config_core_v3_Metadata_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_Metadata* ret = envoy_config_core_v3_Metadata_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__Metadata_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_Metadata_serialize(const envoy_config_core_v3_Metadata* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__Metadata_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_Metadata_serialize_ex(const envoy_config_core_v3_Metadata* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__Metadata_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_Metadata_clear_filter_metadata(envoy_config_core_v3_Metadata* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_core_v3_Metadata_filter_metadata_size(const envoy_config_core_v3_Metadata* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_core_v3_Metadata_filter_metadata_get(const envoy_config_core_v3_Metadata* msg, upb_StringView key, struct google_protobuf_Struct** val) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata__FilterMetadataEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_core_v3_Metadata_filter_metadata_next(const envoy_config_core_v3_Metadata* msg, upb_StringView* key, const struct google_protobuf_Struct** val,
                           size_t* iter) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata__FilterMetadataEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _envoy_config_core_v3_Metadata_filter_metadata_upb_map(envoy_config_core_v3_Metadata* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata__FilterMetadataEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_core_v3_Metadata_filter_metadata_mutable_upb_map(envoy_config_core_v3_Metadata* msg, upb_Arena* a) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata__FilterMetadataEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(struct google_protobuf_Struct*), a);
}
UPB_INLINE void envoy_config_core_v3_Metadata_clear_typed_filter_metadata(envoy_config_core_v3_Metadata* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t envoy_config_core_v3_Metadata_typed_filter_metadata_size(const envoy_config_core_v3_Metadata* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool envoy_config_core_v3_Metadata_typed_filter_metadata_get(const envoy_config_core_v3_Metadata* msg, upb_StringView key, struct google_protobuf_Any** val) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata__TypedFilterMetadataEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool envoy_config_core_v3_Metadata_typed_filter_metadata_next(const envoy_config_core_v3_Metadata* msg, upb_StringView* key, const struct google_protobuf_Any** val,
                           size_t* iter) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata__TypedFilterMetadataEntry_msg_init);
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
UPB_INLINE const upb_Map* _envoy_config_core_v3_Metadata_typed_filter_metadata_upb_map(envoy_config_core_v3_Metadata* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata__TypedFilterMetadataEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _envoy_config_core_v3_Metadata_typed_filter_metadata_mutable_upb_map(envoy_config_core_v3_Metadata* msg, upb_Arena* a) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata__TypedFilterMetadataEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(struct google_protobuf_Any*), a);
}

UPB_INLINE void envoy_config_core_v3_Metadata_filter_metadata_clear(envoy_config_core_v3_Metadata* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_core_v3_Metadata_filter_metadata_set(envoy_config_core_v3_Metadata* msg, upb_StringView key, struct google_protobuf_Struct* val, upb_Arena* a) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata__FilterMetadataEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_core_v3_Metadata_filter_metadata_delete(envoy_config_core_v3_Metadata* msg, upb_StringView key) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void envoy_config_core_v3_Metadata_typed_filter_metadata_clear(envoy_config_core_v3_Metadata* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool envoy_config_core_v3_Metadata_typed_filter_metadata_set(envoy_config_core_v3_Metadata* msg, upb_StringView key, struct google_protobuf_Any* val, upb_Arena* a) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Metadata__TypedFilterMetadataEntry_msg_init);
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool envoy_config_core_v3_Metadata_typed_filter_metadata_delete(envoy_config_core_v3_Metadata* msg, upb_StringView key) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}

UPB_INLINE envoy_config_core_v3_RuntimeUInt32* envoy_config_core_v3_RuntimeUInt32_new(upb_Arena* arena) {
  return (envoy_config_core_v3_RuntimeUInt32*)_upb_Message_New(&envoy__config__core__v3__RuntimeUInt32_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_RuntimeUInt32* envoy_config_core_v3_RuntimeUInt32_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_RuntimeUInt32* ret = envoy_config_core_v3_RuntimeUInt32_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RuntimeUInt32_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_RuntimeUInt32* envoy_config_core_v3_RuntimeUInt32_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_RuntimeUInt32* ret = envoy_config_core_v3_RuntimeUInt32_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RuntimeUInt32_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_RuntimeUInt32_serialize(const envoy_config_core_v3_RuntimeUInt32* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RuntimeUInt32_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_RuntimeUInt32_serialize_ex(const envoy_config_core_v3_RuntimeUInt32* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RuntimeUInt32_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_RuntimeUInt32_clear_default_value(envoy_config_core_v3_RuntimeUInt32* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_config_core_v3_RuntimeUInt32_default_value(const envoy_config_core_v3_RuntimeUInt32* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_RuntimeUInt32_clear_runtime_key(envoy_config_core_v3_RuntimeUInt32* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_RuntimeUInt32_runtime_key(const envoy_config_core_v3_RuntimeUInt32* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_RuntimeUInt32_set_default_value(envoy_config_core_v3_RuntimeUInt32 *msg, uint32_t value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_RuntimeUInt32_set_runtime_key(envoy_config_core_v3_RuntimeUInt32 *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_RuntimePercent* envoy_config_core_v3_RuntimePercent_new(upb_Arena* arena) {
  return (envoy_config_core_v3_RuntimePercent*)_upb_Message_New(&envoy__config__core__v3__RuntimePercent_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_RuntimePercent* envoy_config_core_v3_RuntimePercent_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_RuntimePercent* ret = envoy_config_core_v3_RuntimePercent_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RuntimePercent_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_RuntimePercent* envoy_config_core_v3_RuntimePercent_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_RuntimePercent* ret = envoy_config_core_v3_RuntimePercent_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RuntimePercent_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_RuntimePercent_serialize(const envoy_config_core_v3_RuntimePercent* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RuntimePercent_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_RuntimePercent_serialize_ex(const envoy_config_core_v3_RuntimePercent* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RuntimePercent_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_RuntimePercent_clear_default_value(envoy_config_core_v3_RuntimePercent* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_Percent* envoy_config_core_v3_RuntimePercent_default_value(const envoy_config_core_v3_RuntimePercent* msg) {
  const struct envoy_type_v3_Percent* default_val = NULL;
  const struct envoy_type_v3_Percent* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_RuntimePercent_has_default_value(const envoy_config_core_v3_RuntimePercent* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_RuntimePercent_clear_runtime_key(envoy_config_core_v3_RuntimePercent* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_RuntimePercent_runtime_key(const envoy_config_core_v3_RuntimePercent* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_RuntimePercent_set_default_value(envoy_config_core_v3_RuntimePercent *msg, struct envoy_type_v3_Percent* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__Percent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_Percent* envoy_config_core_v3_RuntimePercent_mutable_default_value(envoy_config_core_v3_RuntimePercent* msg, upb_Arena* arena) {
  struct envoy_type_v3_Percent* sub = (struct envoy_type_v3_Percent*)envoy_config_core_v3_RuntimePercent_default_value(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_Percent*)_upb_Message_New(&envoy__type__v3__Percent_msg_init, arena);
    if (sub) envoy_config_core_v3_RuntimePercent_set_default_value(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_RuntimePercent_set_runtime_key(envoy_config_core_v3_RuntimePercent *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_RuntimeDouble* envoy_config_core_v3_RuntimeDouble_new(upb_Arena* arena) {
  return (envoy_config_core_v3_RuntimeDouble*)_upb_Message_New(&envoy__config__core__v3__RuntimeDouble_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_RuntimeDouble* envoy_config_core_v3_RuntimeDouble_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_RuntimeDouble* ret = envoy_config_core_v3_RuntimeDouble_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RuntimeDouble_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_RuntimeDouble* envoy_config_core_v3_RuntimeDouble_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_RuntimeDouble* ret = envoy_config_core_v3_RuntimeDouble_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RuntimeDouble_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_RuntimeDouble_serialize(const envoy_config_core_v3_RuntimeDouble* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RuntimeDouble_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_RuntimeDouble_serialize_ex(const envoy_config_core_v3_RuntimeDouble* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RuntimeDouble_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_RuntimeDouble_clear_default_value(envoy_config_core_v3_RuntimeDouble* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double envoy_config_core_v3_RuntimeDouble_default_value(const envoy_config_core_v3_RuntimeDouble* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {1, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_RuntimeDouble_clear_runtime_key(envoy_config_core_v3_RuntimeDouble* msg) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_RuntimeDouble_runtime_key(const envoy_config_core_v3_RuntimeDouble* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_RuntimeDouble_set_default_value(envoy_config_core_v3_RuntimeDouble *msg, double value) {
  const upb_MiniTableField field = {1, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_RuntimeDouble_set_runtime_key(envoy_config_core_v3_RuntimeDouble *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_RuntimeFeatureFlag* envoy_config_core_v3_RuntimeFeatureFlag_new(upb_Arena* arena) {
  return (envoy_config_core_v3_RuntimeFeatureFlag*)_upb_Message_New(&envoy__config__core__v3__RuntimeFeatureFlag_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_RuntimeFeatureFlag* envoy_config_core_v3_RuntimeFeatureFlag_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_RuntimeFeatureFlag* ret = envoy_config_core_v3_RuntimeFeatureFlag_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RuntimeFeatureFlag_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_RuntimeFeatureFlag* envoy_config_core_v3_RuntimeFeatureFlag_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_RuntimeFeatureFlag* ret = envoy_config_core_v3_RuntimeFeatureFlag_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RuntimeFeatureFlag_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_RuntimeFeatureFlag_serialize(const envoy_config_core_v3_RuntimeFeatureFlag* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RuntimeFeatureFlag_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_RuntimeFeatureFlag_serialize_ex(const envoy_config_core_v3_RuntimeFeatureFlag* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RuntimeFeatureFlag_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_RuntimeFeatureFlag_clear_default_value(envoy_config_core_v3_RuntimeFeatureFlag* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_core_v3_RuntimeFeatureFlag_default_value(const envoy_config_core_v3_RuntimeFeatureFlag* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_RuntimeFeatureFlag_has_default_value(const envoy_config_core_v3_RuntimeFeatureFlag* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_RuntimeFeatureFlag_clear_runtime_key(envoy_config_core_v3_RuntimeFeatureFlag* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_RuntimeFeatureFlag_runtime_key(const envoy_config_core_v3_RuntimeFeatureFlag* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_RuntimeFeatureFlag_set_default_value(envoy_config_core_v3_RuntimeFeatureFlag *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_core_v3_RuntimeFeatureFlag_mutable_default_value(envoy_config_core_v3_RuntimeFeatureFlag* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_core_v3_RuntimeFeatureFlag_default_value(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_core_v3_RuntimeFeatureFlag_set_default_value(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_RuntimeFeatureFlag_set_runtime_key(envoy_config_core_v3_RuntimeFeatureFlag *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_KeyValue* envoy_config_core_v3_KeyValue_new(upb_Arena* arena) {
  return (envoy_config_core_v3_KeyValue*)_upb_Message_New(&envoy__config__core__v3__KeyValue_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_KeyValue* envoy_config_core_v3_KeyValue_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_KeyValue* ret = envoy_config_core_v3_KeyValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__KeyValue_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_KeyValue* envoy_config_core_v3_KeyValue_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_KeyValue* ret = envoy_config_core_v3_KeyValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__KeyValue_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_KeyValue_serialize(const envoy_config_core_v3_KeyValue* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__KeyValue_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_KeyValue_serialize_ex(const envoy_config_core_v3_KeyValue* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__KeyValue_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_KeyValue_clear_key(envoy_config_core_v3_KeyValue* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_KeyValue_key(const envoy_config_core_v3_KeyValue* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_KeyValue_clear_value(envoy_config_core_v3_KeyValue* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_KeyValue_value(const envoy_config_core_v3_KeyValue* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_KeyValue_set_key(envoy_config_core_v3_KeyValue *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_KeyValue_set_value(envoy_config_core_v3_KeyValue *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_KeyValuePair* envoy_config_core_v3_KeyValuePair_new(upb_Arena* arena) {
  return (envoy_config_core_v3_KeyValuePair*)_upb_Message_New(&envoy__config__core__v3__KeyValuePair_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_KeyValuePair* envoy_config_core_v3_KeyValuePair_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_KeyValuePair* ret = envoy_config_core_v3_KeyValuePair_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__KeyValuePair_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_KeyValuePair* envoy_config_core_v3_KeyValuePair_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_KeyValuePair* ret = envoy_config_core_v3_KeyValuePair_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__KeyValuePair_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_KeyValuePair_serialize(const envoy_config_core_v3_KeyValuePair* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__KeyValuePair_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_KeyValuePair_serialize_ex(const envoy_config_core_v3_KeyValuePair* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__KeyValuePair_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_KeyValuePair_clear_key(envoy_config_core_v3_KeyValuePair* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_KeyValuePair_key(const envoy_config_core_v3_KeyValuePair* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_KeyValuePair_clear_value(envoy_config_core_v3_KeyValuePair* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Value* envoy_config_core_v3_KeyValuePair_value(const envoy_config_core_v3_KeyValuePair* msg) {
  const struct google_protobuf_Value* default_val = NULL;
  const struct google_protobuf_Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_KeyValuePair_has_value(const envoy_config_core_v3_KeyValuePair* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_KeyValuePair_set_key(envoy_config_core_v3_KeyValuePair *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_KeyValuePair_set_value(envoy_config_core_v3_KeyValuePair *msg, struct google_protobuf_Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Value* envoy_config_core_v3_KeyValuePair_mutable_value(envoy_config_core_v3_KeyValuePair* msg, upb_Arena* arena) {
  struct google_protobuf_Value* sub = (struct google_protobuf_Value*)envoy_config_core_v3_KeyValuePair_value(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Value*)_upb_Message_New(&google__protobuf__Value_msg_init, arena);
    if (sub) envoy_config_core_v3_KeyValuePair_set_value(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_KeyValueAppend* envoy_config_core_v3_KeyValueAppend_new(upb_Arena* arena) {
  return (envoy_config_core_v3_KeyValueAppend*)_upb_Message_New(&envoy__config__core__v3__KeyValueAppend_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_KeyValueAppend* envoy_config_core_v3_KeyValueAppend_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_KeyValueAppend* ret = envoy_config_core_v3_KeyValueAppend_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__KeyValueAppend_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_KeyValueAppend* envoy_config_core_v3_KeyValueAppend_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_KeyValueAppend* ret = envoy_config_core_v3_KeyValueAppend_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__KeyValueAppend_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_KeyValueAppend_serialize(const envoy_config_core_v3_KeyValueAppend* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__KeyValueAppend_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_KeyValueAppend_serialize_ex(const envoy_config_core_v3_KeyValueAppend* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__KeyValueAppend_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_KeyValueAppend_clear_entry(envoy_config_core_v3_KeyValueAppend* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_KeyValue* envoy_config_core_v3_KeyValueAppend_entry(const envoy_config_core_v3_KeyValueAppend* msg) {
  const envoy_config_core_v3_KeyValue* default_val = NULL;
  const envoy_config_core_v3_KeyValue* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__KeyValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_KeyValueAppend_has_entry(const envoy_config_core_v3_KeyValueAppend* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_KeyValueAppend_clear_action(envoy_config_core_v3_KeyValueAppend* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_core_v3_KeyValueAppend_action(const envoy_config_core_v3_KeyValueAppend* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_KeyValueAppend_clear_record(envoy_config_core_v3_KeyValueAppend* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_KeyValuePair* envoy_config_core_v3_KeyValueAppend_record(const envoy_config_core_v3_KeyValueAppend* msg) {
  const envoy_config_core_v3_KeyValuePair* default_val = NULL;
  const envoy_config_core_v3_KeyValuePair* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__KeyValuePair_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_KeyValueAppend_has_record(const envoy_config_core_v3_KeyValueAppend* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_KeyValueAppend_set_entry(envoy_config_core_v3_KeyValueAppend *msg, envoy_config_core_v3_KeyValue* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__KeyValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_KeyValue* envoy_config_core_v3_KeyValueAppend_mutable_entry(envoy_config_core_v3_KeyValueAppend* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_KeyValue* sub = (struct envoy_config_core_v3_KeyValue*)envoy_config_core_v3_KeyValueAppend_entry(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_KeyValue*)_upb_Message_New(&envoy__config__core__v3__KeyValue_msg_init, arena);
    if (sub) envoy_config_core_v3_KeyValueAppend_set_entry(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_KeyValueAppend_set_action(envoy_config_core_v3_KeyValueAppend *msg, int32_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_KeyValueAppend_set_record(envoy_config_core_v3_KeyValueAppend *msg, envoy_config_core_v3_KeyValuePair* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__KeyValuePair_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_KeyValuePair* envoy_config_core_v3_KeyValueAppend_mutable_record(envoy_config_core_v3_KeyValueAppend* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_KeyValuePair* sub = (struct envoy_config_core_v3_KeyValuePair*)envoy_config_core_v3_KeyValueAppend_record(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_KeyValuePair*)_upb_Message_New(&envoy__config__core__v3__KeyValuePair_msg_init, arena);
    if (sub) envoy_config_core_v3_KeyValueAppend_set_record(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_KeyValueMutation* envoy_config_core_v3_KeyValueMutation_new(upb_Arena* arena) {
  return (envoy_config_core_v3_KeyValueMutation*)_upb_Message_New(&envoy__config__core__v3__KeyValueMutation_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_KeyValueMutation* envoy_config_core_v3_KeyValueMutation_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_KeyValueMutation* ret = envoy_config_core_v3_KeyValueMutation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__KeyValueMutation_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_KeyValueMutation* envoy_config_core_v3_KeyValueMutation_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_KeyValueMutation* ret = envoy_config_core_v3_KeyValueMutation_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__KeyValueMutation_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_KeyValueMutation_serialize(const envoy_config_core_v3_KeyValueMutation* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__KeyValueMutation_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_KeyValueMutation_serialize_ex(const envoy_config_core_v3_KeyValueMutation* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__KeyValueMutation_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_KeyValueMutation_clear_append(envoy_config_core_v3_KeyValueMutation* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_KeyValueAppend* envoy_config_core_v3_KeyValueMutation_append(const envoy_config_core_v3_KeyValueMutation* msg) {
  const envoy_config_core_v3_KeyValueAppend* default_val = NULL;
  const envoy_config_core_v3_KeyValueAppend* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__KeyValueAppend_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_KeyValueMutation_has_append(const envoy_config_core_v3_KeyValueMutation* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_KeyValueMutation_clear_remove(envoy_config_core_v3_KeyValueMutation* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_KeyValueMutation_remove(const envoy_config_core_v3_KeyValueMutation* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_KeyValueMutation_set_append(envoy_config_core_v3_KeyValueMutation *msg, envoy_config_core_v3_KeyValueAppend* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__KeyValueAppend_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_KeyValueAppend* envoy_config_core_v3_KeyValueMutation_mutable_append(envoy_config_core_v3_KeyValueMutation* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_KeyValueAppend* sub = (struct envoy_config_core_v3_KeyValueAppend*)envoy_config_core_v3_KeyValueMutation_append(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_KeyValueAppend*)_upb_Message_New(&envoy__config__core__v3__KeyValueAppend_msg_init, arena);
    if (sub) envoy_config_core_v3_KeyValueMutation_set_append(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_KeyValueMutation_set_remove(envoy_config_core_v3_KeyValueMutation *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_QueryParameter* envoy_config_core_v3_QueryParameter_new(upb_Arena* arena) {
  return (envoy_config_core_v3_QueryParameter*)_upb_Message_New(&envoy__config__core__v3__QueryParameter_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_QueryParameter* envoy_config_core_v3_QueryParameter_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_QueryParameter* ret = envoy_config_core_v3_QueryParameter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__QueryParameter_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_QueryParameter* envoy_config_core_v3_QueryParameter_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_QueryParameter* ret = envoy_config_core_v3_QueryParameter_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__QueryParameter_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_QueryParameter_serialize(const envoy_config_core_v3_QueryParameter* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__QueryParameter_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_QueryParameter_serialize_ex(const envoy_config_core_v3_QueryParameter* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__QueryParameter_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_QueryParameter_clear_key(envoy_config_core_v3_QueryParameter* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_QueryParameter_key(const envoy_config_core_v3_QueryParameter* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_QueryParameter_clear_value(envoy_config_core_v3_QueryParameter* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_QueryParameter_value(const envoy_config_core_v3_QueryParameter* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_QueryParameter_set_key(envoy_config_core_v3_QueryParameter *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_QueryParameter_set_value(envoy_config_core_v3_QueryParameter *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_HeaderValue* envoy_config_core_v3_HeaderValue_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HeaderValue*)_upb_Message_New(&envoy__config__core__v3__HeaderValue_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HeaderValue* envoy_config_core_v3_HeaderValue_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HeaderValue* ret = envoy_config_core_v3_HeaderValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HeaderValue_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HeaderValue* envoy_config_core_v3_HeaderValue_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HeaderValue* ret = envoy_config_core_v3_HeaderValue_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HeaderValue_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HeaderValue_serialize(const envoy_config_core_v3_HeaderValue* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HeaderValue_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HeaderValue_serialize_ex(const envoy_config_core_v3_HeaderValue* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HeaderValue_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_HeaderValue_clear_key(envoy_config_core_v3_HeaderValue* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HeaderValue_key(const envoy_config_core_v3_HeaderValue* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HeaderValue_clear_value(envoy_config_core_v3_HeaderValue* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HeaderValue_value(const envoy_config_core_v3_HeaderValue* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HeaderValue_clear_raw_value(envoy_config_core_v3_HeaderValue* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_HeaderValue_raw_value(const envoy_config_core_v3_HeaderValue* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_HeaderValue_set_key(envoy_config_core_v3_HeaderValue *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HeaderValue_set_value(envoy_config_core_v3_HeaderValue *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HeaderValue_set_raw_value(envoy_config_core_v3_HeaderValue *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_HeaderValueOption* envoy_config_core_v3_HeaderValueOption_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HeaderValueOption*)_upb_Message_New(&envoy__config__core__v3__HeaderValueOption_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HeaderValueOption* envoy_config_core_v3_HeaderValueOption_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HeaderValueOption* ret = envoy_config_core_v3_HeaderValueOption_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HeaderValueOption_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HeaderValueOption* envoy_config_core_v3_HeaderValueOption_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HeaderValueOption* ret = envoy_config_core_v3_HeaderValueOption_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HeaderValueOption_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HeaderValueOption_serialize(const envoy_config_core_v3_HeaderValueOption* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HeaderValueOption_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HeaderValueOption_serialize_ex(const envoy_config_core_v3_HeaderValueOption* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HeaderValueOption_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_HeaderValueOption_clear_header(envoy_config_core_v3_HeaderValueOption* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HeaderValue* envoy_config_core_v3_HeaderValueOption_header(const envoy_config_core_v3_HeaderValueOption* msg) {
  const envoy_config_core_v3_HeaderValue* default_val = NULL;
  const envoy_config_core_v3_HeaderValue* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HeaderValueOption_has_header(const envoy_config_core_v3_HeaderValueOption* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HeaderValueOption_clear_append(envoy_config_core_v3_HeaderValueOption* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_core_v3_HeaderValueOption_append(const envoy_config_core_v3_HeaderValueOption* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_HeaderValueOption_has_append(const envoy_config_core_v3_HeaderValueOption* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_HeaderValueOption_clear_append_action(envoy_config_core_v3_HeaderValueOption* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_config_core_v3_HeaderValueOption_append_action(const envoy_config_core_v3_HeaderValueOption* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_HeaderValueOption_clear_keep_empty_value(envoy_config_core_v3_HeaderValueOption* msg) {
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_core_v3_HeaderValueOption_keep_empty_value(const envoy_config_core_v3_HeaderValueOption* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_HeaderValueOption_set_header(envoy_config_core_v3_HeaderValueOption *msg, envoy_config_core_v3_HeaderValue* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValue* envoy_config_core_v3_HeaderValueOption_mutable_header(envoy_config_core_v3_HeaderValueOption* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HeaderValue* sub = (struct envoy_config_core_v3_HeaderValue*)envoy_config_core_v3_HeaderValueOption_header(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HeaderValue*)_upb_Message_New(&envoy__config__core__v3__HeaderValue_msg_init, arena);
    if (sub) envoy_config_core_v3_HeaderValueOption_set_header(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HeaderValueOption_set_append(envoy_config_core_v3_HeaderValueOption *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_core_v3_HeaderValueOption_mutable_append(envoy_config_core_v3_HeaderValueOption* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_core_v3_HeaderValueOption_append(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_core_v3_HeaderValueOption_set_append(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_HeaderValueOption_set_append_action(envoy_config_core_v3_HeaderValueOption *msg, int32_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_HeaderValueOption_set_keep_empty_value(envoy_config_core_v3_HeaderValueOption *msg, bool value) {
  const upb_MiniTableField field = {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_HeaderMap* envoy_config_core_v3_HeaderMap_new(upb_Arena* arena) {
  return (envoy_config_core_v3_HeaderMap*)_upb_Message_New(&envoy__config__core__v3__HeaderMap_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_HeaderMap* envoy_config_core_v3_HeaderMap_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_HeaderMap* ret = envoy_config_core_v3_HeaderMap_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HeaderMap_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_HeaderMap* envoy_config_core_v3_HeaderMap_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_HeaderMap* ret = envoy_config_core_v3_HeaderMap_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__HeaderMap_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_HeaderMap_serialize(const envoy_config_core_v3_HeaderMap* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HeaderMap_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_HeaderMap_serialize_ex(const envoy_config_core_v3_HeaderMap* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__HeaderMap_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_HeaderMap_clear_headers(envoy_config_core_v3_HeaderMap* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_HeaderValue* const* envoy_config_core_v3_HeaderMap_headers(const envoy_config_core_v3_HeaderMap* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_core_v3_HeaderValue* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_HeaderMap_headers_upb_array(const envoy_config_core_v3_HeaderMap* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_HeaderMap_headers_mutable_upb_array(envoy_config_core_v3_HeaderMap* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_core_v3_HeaderValue** envoy_config_core_v3_HeaderMap_mutable_headers(envoy_config_core_v3_HeaderMap* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_core_v3_HeaderValue**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_core_v3_HeaderValue** envoy_config_core_v3_HeaderMap_resize_headers(envoy_config_core_v3_HeaderMap* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_HeaderValue**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_HeaderValue* envoy_config_core_v3_HeaderMap_add_headers(envoy_config_core_v3_HeaderMap* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HeaderValue_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_HeaderValue* sub = (struct envoy_config_core_v3_HeaderValue*)_upb_Message_New(&envoy__config__core__v3__HeaderValue_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_core_v3_WatchedDirectory* envoy_config_core_v3_WatchedDirectory_new(upb_Arena* arena) {
  return (envoy_config_core_v3_WatchedDirectory*)_upb_Message_New(&envoy__config__core__v3__WatchedDirectory_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_WatchedDirectory* envoy_config_core_v3_WatchedDirectory_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_WatchedDirectory* ret = envoy_config_core_v3_WatchedDirectory_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__WatchedDirectory_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_WatchedDirectory* envoy_config_core_v3_WatchedDirectory_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_WatchedDirectory* ret = envoy_config_core_v3_WatchedDirectory_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__WatchedDirectory_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_WatchedDirectory_serialize(const envoy_config_core_v3_WatchedDirectory* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__WatchedDirectory_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_WatchedDirectory_serialize_ex(const envoy_config_core_v3_WatchedDirectory* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__WatchedDirectory_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_WatchedDirectory_clear_path(envoy_config_core_v3_WatchedDirectory* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_WatchedDirectory_path(const envoy_config_core_v3_WatchedDirectory* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_WatchedDirectory_set_path(envoy_config_core_v3_WatchedDirectory *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_DataSource* envoy_config_core_v3_DataSource_new(upb_Arena* arena) {
  return (envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_DataSource* envoy_config_core_v3_DataSource_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_DataSource* ret = envoy_config_core_v3_DataSource_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__DataSource_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_DataSource* envoy_config_core_v3_DataSource_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_DataSource* ret = envoy_config_core_v3_DataSource_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__DataSource_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_DataSource_serialize(const envoy_config_core_v3_DataSource* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__DataSource_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_DataSource_serialize_ex(const envoy_config_core_v3_DataSource* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__DataSource_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_DataSource_specifier_filename = 1,
  envoy_config_core_v3_DataSource_specifier_inline_bytes = 2,
  envoy_config_core_v3_DataSource_specifier_inline_string = 3,
  envoy_config_core_v3_DataSource_specifier_environment_variable = 4,
  envoy_config_core_v3_DataSource_specifier_NOT_SET = 0
} envoy_config_core_v3_DataSource_specifier_oneofcases;
UPB_INLINE envoy_config_core_v3_DataSource_specifier_oneofcases envoy_config_core_v3_DataSource_specifier_case(const envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_DataSource_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_DataSource_clear_specifier(envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__DataSource_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_DataSource_clear_filename(envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_DataSource_filename(const envoy_config_core_v3_DataSource* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_DataSource_has_filename(const envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_DataSource_clear_inline_bytes(envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_DataSource_inline_bytes(const envoy_config_core_v3_DataSource* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_DataSource_has_inline_bytes(const envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_DataSource_clear_inline_string(envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_DataSource_inline_string(const envoy_config_core_v3_DataSource* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_DataSource_has_inline_string(const envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_DataSource_clear_environment_variable(envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_DataSource_environment_variable(const envoy_config_core_v3_DataSource* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_DataSource_has_environment_variable(const envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_DataSource_clear_watched_directory(envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_WatchedDirectory* envoy_config_core_v3_DataSource_watched_directory(const envoy_config_core_v3_DataSource* msg) {
  const envoy_config_core_v3_WatchedDirectory* default_val = NULL;
  const envoy_config_core_v3_WatchedDirectory* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__WatchedDirectory_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_DataSource_has_watched_directory(const envoy_config_core_v3_DataSource* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_DataSource_set_filename(envoy_config_core_v3_DataSource *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_DataSource_set_inline_bytes(envoy_config_core_v3_DataSource *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_DataSource_set_inline_string(envoy_config_core_v3_DataSource *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_DataSource_set_environment_variable(envoy_config_core_v3_DataSource *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_DataSource_set_watched_directory(envoy_config_core_v3_DataSource *msg, envoy_config_core_v3_WatchedDirectory* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__WatchedDirectory_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_WatchedDirectory* envoy_config_core_v3_DataSource_mutable_watched_directory(envoy_config_core_v3_DataSource* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_WatchedDirectory* sub = (struct envoy_config_core_v3_WatchedDirectory*)envoy_config_core_v3_DataSource_watched_directory(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_WatchedDirectory*)_upb_Message_New(&envoy__config__core__v3__WatchedDirectory_msg_init, arena);
    if (sub) envoy_config_core_v3_DataSource_set_watched_directory(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_RetryPolicy* envoy_config_core_v3_RetryPolicy_new(upb_Arena* arena) {
  return (envoy_config_core_v3_RetryPolicy*)_upb_Message_New(&envoy__config__core__v3__RetryPolicy_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_RetryPolicy* envoy_config_core_v3_RetryPolicy_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_RetryPolicy* ret = envoy_config_core_v3_RetryPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RetryPolicy_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_RetryPolicy* envoy_config_core_v3_RetryPolicy_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_RetryPolicy* ret = envoy_config_core_v3_RetryPolicy_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RetryPolicy_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_RetryPolicy_serialize(const envoy_config_core_v3_RetryPolicy* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RetryPolicy_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_RetryPolicy_serialize_ex(const envoy_config_core_v3_RetryPolicy* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RetryPolicy_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_clear_retry_back_off(envoy_config_core_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_BackoffStrategy* envoy_config_core_v3_RetryPolicy_retry_back_off(const envoy_config_core_v3_RetryPolicy* msg) {
  const struct envoy_config_core_v3_BackoffStrategy* default_val = NULL;
  const struct envoy_config_core_v3_BackoffStrategy* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__BackoffStrategy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_RetryPolicy_has_retry_back_off(const envoy_config_core_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_clear_num_retries(envoy_config_core_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_config_core_v3_RetryPolicy_num_retries(const envoy_config_core_v3_RetryPolicy* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_RetryPolicy_has_num_retries(const envoy_config_core_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_clear_retry_on(envoy_config_core_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_RetryPolicy_retry_on(const envoy_config_core_v3_RetryPolicy* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_clear_retry_priority(envoy_config_core_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_RetryPolicy_RetryPriority* envoy_config_core_v3_RetryPolicy_retry_priority(const envoy_config_core_v3_RetryPolicy* msg) {
  const envoy_config_core_v3_RetryPolicy_RetryPriority* default_val = NULL;
  const envoy_config_core_v3_RetryPolicy_RetryPriority* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_RetryPolicy_has_retry_priority(const envoy_config_core_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_clear_retry_host_predicate(envoy_config_core_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_RetryPolicy_RetryHostPredicate* const* envoy_config_core_v3_RetryPolicy_retry_host_predicate(const envoy_config_core_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_core_v3_RetryPolicy_RetryHostPredicate* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_core_v3_RetryPolicy_retry_host_predicate_upb_array(const envoy_config_core_v3_RetryPolicy* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_core_v3_RetryPolicy_retry_host_predicate_mutable_upb_array(envoy_config_core_v3_RetryPolicy* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_clear_host_selection_retry_max_attempts(envoy_config_core_v3_RetryPolicy* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(40, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t envoy_config_core_v3_RetryPolicy_host_selection_retry_max_attempts(const envoy_config_core_v3_RetryPolicy* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {6, UPB_SIZE(40, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_RetryPolicy_set_retry_back_off(envoy_config_core_v3_RetryPolicy *msg, struct envoy_config_core_v3_BackoffStrategy* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__BackoffStrategy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_BackoffStrategy* envoy_config_core_v3_RetryPolicy_mutable_retry_back_off(envoy_config_core_v3_RetryPolicy* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_BackoffStrategy* sub = (struct envoy_config_core_v3_BackoffStrategy*)envoy_config_core_v3_RetryPolicy_retry_back_off(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_BackoffStrategy*)_upb_Message_New(&envoy__config__core__v3__BackoffStrategy_msg_init, arena);
    if (sub) envoy_config_core_v3_RetryPolicy_set_retry_back_off(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_set_num_retries(envoy_config_core_v3_RetryPolicy *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_config_core_v3_RetryPolicy_mutable_num_retries(envoy_config_core_v3_RetryPolicy* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_config_core_v3_RetryPolicy_num_retries(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_config_core_v3_RetryPolicy_set_num_retries(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_set_retry_on(envoy_config_core_v3_RetryPolicy *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_set_retry_priority(envoy_config_core_v3_RetryPolicy *msg, envoy_config_core_v3_RetryPolicy_RetryPriority* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RetryPolicy_RetryPriority* envoy_config_core_v3_RetryPolicy_mutable_retry_priority(envoy_config_core_v3_RetryPolicy* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RetryPolicy_RetryPriority* sub = (struct envoy_config_core_v3_RetryPolicy_RetryPriority*)envoy_config_core_v3_RetryPolicy_retry_priority(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RetryPolicy_RetryPriority*)_upb_Message_New(&envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init, arena);
    if (sub) envoy_config_core_v3_RetryPolicy_set_retry_priority(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_core_v3_RetryPolicy_RetryHostPredicate** envoy_config_core_v3_RetryPolicy_mutable_retry_host_predicate(envoy_config_core_v3_RetryPolicy* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_core_v3_RetryPolicy_RetryHostPredicate**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_core_v3_RetryPolicy_RetryHostPredicate** envoy_config_core_v3_RetryPolicy_resize_retry_host_predicate(envoy_config_core_v3_RetryPolicy* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_RetryPolicy_RetryHostPredicate**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_core_v3_RetryPolicy_RetryHostPredicate* envoy_config_core_v3_RetryPolicy_add_retry_host_predicate(envoy_config_core_v3_RetryPolicy* msg, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_core_v3_RetryPolicy_RetryHostPredicate* sub = (struct envoy_config_core_v3_RetryPolicy_RetryHostPredicate*)_upb_Message_New(&envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_set_host_selection_retry_max_attempts(envoy_config_core_v3_RetryPolicy *msg, int64_t value) {
  const upb_MiniTableField field = {6, UPB_SIZE(40, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_RetryPolicy_RetryPriority* envoy_config_core_v3_RetryPolicy_RetryPriority_new(upb_Arena* arena) {
  return (envoy_config_core_v3_RetryPolicy_RetryPriority*)_upb_Message_New(&envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_RetryPolicy_RetryPriority* envoy_config_core_v3_RetryPolicy_RetryPriority_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_RetryPolicy_RetryPriority* ret = envoy_config_core_v3_RetryPolicy_RetryPriority_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_RetryPolicy_RetryPriority* envoy_config_core_v3_RetryPolicy_RetryPriority_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_RetryPolicy_RetryPriority* ret = envoy_config_core_v3_RetryPolicy_RetryPriority_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_RetryPolicy_RetryPriority_serialize(const envoy_config_core_v3_RetryPolicy_RetryPriority* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_RetryPolicy_RetryPriority_serialize_ex(const envoy_config_core_v3_RetryPolicy_RetryPriority* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_RetryPolicy_RetryPriority_config_type_typed_config = 2,
  envoy_config_core_v3_RetryPolicy_RetryPriority_config_type_NOT_SET = 0
} envoy_config_core_v3_RetryPolicy_RetryPriority_config_type_oneofcases;
UPB_INLINE envoy_config_core_v3_RetryPolicy_RetryPriority_config_type_oneofcases envoy_config_core_v3_RetryPolicy_RetryPriority_config_type_case(const envoy_config_core_v3_RetryPolicy_RetryPriority* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_RetryPolicy_RetryPriority_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_RetryPriority_clear_config_type(envoy_config_core_v3_RetryPolicy_RetryPriority* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_RetryPriority_clear_name(envoy_config_core_v3_RetryPolicy_RetryPriority* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_RetryPolicy_RetryPriority_name(const envoy_config_core_v3_RetryPolicy_RetryPriority* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_RetryPriority_clear_typed_config(envoy_config_core_v3_RetryPolicy_RetryPriority* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_core_v3_RetryPolicy_RetryPriority_typed_config(const envoy_config_core_v3_RetryPolicy_RetryPriority* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_RetryPolicy_RetryPriority_has_typed_config(const envoy_config_core_v3_RetryPolicy_RetryPriority* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_RetryPolicy_RetryPriority_set_name(envoy_config_core_v3_RetryPolicy_RetryPriority *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_RetryPriority_set_typed_config(envoy_config_core_v3_RetryPolicy_RetryPriority *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_core_v3_RetryPolicy_RetryPriority_mutable_typed_config(envoy_config_core_v3_RetryPolicy_RetryPriority* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_core_v3_RetryPolicy_RetryPriority_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_core_v3_RetryPolicy_RetryPriority_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_RetryPolicy_RetryHostPredicate* envoy_config_core_v3_RetryPolicy_RetryHostPredicate_new(upb_Arena* arena) {
  return (envoy_config_core_v3_RetryPolicy_RetryHostPredicate*)_upb_Message_New(&envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_RetryPolicy_RetryHostPredicate* envoy_config_core_v3_RetryPolicy_RetryHostPredicate_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_RetryPolicy_RetryHostPredicate* ret = envoy_config_core_v3_RetryPolicy_RetryHostPredicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_RetryPolicy_RetryHostPredicate* envoy_config_core_v3_RetryPolicy_RetryHostPredicate_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_RetryPolicy_RetryHostPredicate* ret = envoy_config_core_v3_RetryPolicy_RetryHostPredicate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_RetryPolicy_RetryHostPredicate_serialize(const envoy_config_core_v3_RetryPolicy_RetryHostPredicate* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_RetryPolicy_RetryHostPredicate_serialize_ex(const envoy_config_core_v3_RetryPolicy_RetryHostPredicate* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_RetryPolicy_RetryHostPredicate_config_type_typed_config = 2,
  envoy_config_core_v3_RetryPolicy_RetryHostPredicate_config_type_NOT_SET = 0
} envoy_config_core_v3_RetryPolicy_RetryHostPredicate_config_type_oneofcases;
UPB_INLINE envoy_config_core_v3_RetryPolicy_RetryHostPredicate_config_type_oneofcases envoy_config_core_v3_RetryPolicy_RetryHostPredicate_config_type_case(const envoy_config_core_v3_RetryPolicy_RetryHostPredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_RetryPolicy_RetryHostPredicate_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_RetryHostPredicate_clear_config_type(envoy_config_core_v3_RetryPolicy_RetryHostPredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_RetryHostPredicate_clear_name(envoy_config_core_v3_RetryPolicy_RetryHostPredicate* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_RetryPolicy_RetryHostPredicate_name(const envoy_config_core_v3_RetryPolicy_RetryHostPredicate* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_RetryHostPredicate_clear_typed_config(envoy_config_core_v3_RetryPolicy_RetryHostPredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_core_v3_RetryPolicy_RetryHostPredicate_typed_config(const envoy_config_core_v3_RetryPolicy_RetryHostPredicate* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_RetryPolicy_RetryHostPredicate_has_typed_config(const envoy_config_core_v3_RetryPolicy_RetryHostPredicate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_RetryPolicy_RetryHostPredicate_set_name(envoy_config_core_v3_RetryPolicy_RetryHostPredicate *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_RetryPolicy_RetryHostPredicate_set_typed_config(envoy_config_core_v3_RetryPolicy_RetryHostPredicate *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_core_v3_RetryPolicy_RetryHostPredicate_mutable_typed_config(envoy_config_core_v3_RetryPolicy_RetryHostPredicate* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_core_v3_RetryPolicy_RetryHostPredicate_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_core_v3_RetryPolicy_RetryHostPredicate_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_RemoteDataSource* envoy_config_core_v3_RemoteDataSource_new(upb_Arena* arena) {
  return (envoy_config_core_v3_RemoteDataSource*)_upb_Message_New(&envoy__config__core__v3__RemoteDataSource_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_RemoteDataSource* envoy_config_core_v3_RemoteDataSource_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_RemoteDataSource* ret = envoy_config_core_v3_RemoteDataSource_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RemoteDataSource_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_RemoteDataSource* envoy_config_core_v3_RemoteDataSource_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_RemoteDataSource* ret = envoy_config_core_v3_RemoteDataSource_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RemoteDataSource_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_RemoteDataSource_serialize(const envoy_config_core_v3_RemoteDataSource* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RemoteDataSource_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_RemoteDataSource_serialize_ex(const envoy_config_core_v3_RemoteDataSource* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RemoteDataSource_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_RemoteDataSource_clear_http_uri(envoy_config_core_v3_RemoteDataSource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_HttpUri* envoy_config_core_v3_RemoteDataSource_http_uri(const envoy_config_core_v3_RemoteDataSource* msg) {
  const struct envoy_config_core_v3_HttpUri* default_val = NULL;
  const struct envoy_config_core_v3_HttpUri* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HttpUri_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_RemoteDataSource_has_http_uri(const envoy_config_core_v3_RemoteDataSource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_RemoteDataSource_clear_sha256(envoy_config_core_v3_RemoteDataSource* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_RemoteDataSource_sha256(const envoy_config_core_v3_RemoteDataSource* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_RemoteDataSource_clear_retry_policy(envoy_config_core_v3_RemoteDataSource* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_RetryPolicy* envoy_config_core_v3_RemoteDataSource_retry_policy(const envoy_config_core_v3_RemoteDataSource* msg) {
  const envoy_config_core_v3_RetryPolicy* default_val = NULL;
  const envoy_config_core_v3_RetryPolicy* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_RemoteDataSource_has_retry_policy(const envoy_config_core_v3_RemoteDataSource* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_RemoteDataSource_set_http_uri(envoy_config_core_v3_RemoteDataSource *msg, struct envoy_config_core_v3_HttpUri* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__HttpUri_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_HttpUri* envoy_config_core_v3_RemoteDataSource_mutable_http_uri(envoy_config_core_v3_RemoteDataSource* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_HttpUri* sub = (struct envoy_config_core_v3_HttpUri*)envoy_config_core_v3_RemoteDataSource_http_uri(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_HttpUri*)_upb_Message_New(&envoy__config__core__v3__HttpUri_msg_init, arena);
    if (sub) envoy_config_core_v3_RemoteDataSource_set_http_uri(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_RemoteDataSource_set_sha256(envoy_config_core_v3_RemoteDataSource *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_RemoteDataSource_set_retry_policy(envoy_config_core_v3_RemoteDataSource *msg, envoy_config_core_v3_RetryPolicy* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RetryPolicy_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RetryPolicy* envoy_config_core_v3_RemoteDataSource_mutable_retry_policy(envoy_config_core_v3_RemoteDataSource* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RetryPolicy* sub = (struct envoy_config_core_v3_RetryPolicy*)envoy_config_core_v3_RemoteDataSource_retry_policy(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RetryPolicy*)_upb_Message_New(&envoy__config__core__v3__RetryPolicy_msg_init, arena);
    if (sub) envoy_config_core_v3_RemoteDataSource_set_retry_policy(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_AsyncDataSource* envoy_config_core_v3_AsyncDataSource_new(upb_Arena* arena) {
  return (envoy_config_core_v3_AsyncDataSource*)_upb_Message_New(&envoy__config__core__v3__AsyncDataSource_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_AsyncDataSource* envoy_config_core_v3_AsyncDataSource_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_AsyncDataSource* ret = envoy_config_core_v3_AsyncDataSource_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__AsyncDataSource_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_AsyncDataSource* envoy_config_core_v3_AsyncDataSource_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_AsyncDataSource* ret = envoy_config_core_v3_AsyncDataSource_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__AsyncDataSource_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_AsyncDataSource_serialize(const envoy_config_core_v3_AsyncDataSource* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__AsyncDataSource_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_AsyncDataSource_serialize_ex(const envoy_config_core_v3_AsyncDataSource* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__AsyncDataSource_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_AsyncDataSource_specifier_local = 1,
  envoy_config_core_v3_AsyncDataSource_specifier_remote = 2,
  envoy_config_core_v3_AsyncDataSource_specifier_NOT_SET = 0
} envoy_config_core_v3_AsyncDataSource_specifier_oneofcases;
UPB_INLINE envoy_config_core_v3_AsyncDataSource_specifier_oneofcases envoy_config_core_v3_AsyncDataSource_specifier_case(const envoy_config_core_v3_AsyncDataSource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_AsyncDataSource_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_AsyncDataSource_clear_specifier(envoy_config_core_v3_AsyncDataSource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__AsyncDataSource_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_AsyncDataSource_clear_local(envoy_config_core_v3_AsyncDataSource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_DataSource* envoy_config_core_v3_AsyncDataSource_local(const envoy_config_core_v3_AsyncDataSource* msg) {
  const envoy_config_core_v3_DataSource* default_val = NULL;
  const envoy_config_core_v3_DataSource* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_AsyncDataSource_has_local(const envoy_config_core_v3_AsyncDataSource* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_AsyncDataSource_clear_remote(envoy_config_core_v3_AsyncDataSource* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_core_v3_RemoteDataSource* envoy_config_core_v3_AsyncDataSource_remote(const envoy_config_core_v3_AsyncDataSource* msg) {
  const envoy_config_core_v3_RemoteDataSource* default_val = NULL;
  const envoy_config_core_v3_RemoteDataSource* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RemoteDataSource_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_AsyncDataSource_has_remote(const envoy_config_core_v3_AsyncDataSource* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_AsyncDataSource_set_local(envoy_config_core_v3_AsyncDataSource *msg, envoy_config_core_v3_DataSource* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__DataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_DataSource* envoy_config_core_v3_AsyncDataSource_mutable_local(envoy_config_core_v3_AsyncDataSource* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_DataSource* sub = (struct envoy_config_core_v3_DataSource*)envoy_config_core_v3_AsyncDataSource_local(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_DataSource*)_upb_Message_New(&envoy__config__core__v3__DataSource_msg_init, arena);
    if (sub) envoy_config_core_v3_AsyncDataSource_set_local(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_AsyncDataSource_set_remote(envoy_config_core_v3_AsyncDataSource *msg, envoy_config_core_v3_RemoteDataSource* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__RemoteDataSource_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_RemoteDataSource* envoy_config_core_v3_AsyncDataSource_mutable_remote(envoy_config_core_v3_AsyncDataSource* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_RemoteDataSource* sub = (struct envoy_config_core_v3_RemoteDataSource*)envoy_config_core_v3_AsyncDataSource_remote(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_RemoteDataSource*)_upb_Message_New(&envoy__config__core__v3__RemoteDataSource_msg_init, arena);
    if (sub) envoy_config_core_v3_AsyncDataSource_set_remote(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_TransportSocket* envoy_config_core_v3_TransportSocket_new(upb_Arena* arena) {
  return (envoy_config_core_v3_TransportSocket*)_upb_Message_New(&envoy__config__core__v3__TransportSocket_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_TransportSocket* envoy_config_core_v3_TransportSocket_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_TransportSocket* ret = envoy_config_core_v3_TransportSocket_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__TransportSocket_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_TransportSocket* envoy_config_core_v3_TransportSocket_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_TransportSocket* ret = envoy_config_core_v3_TransportSocket_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__TransportSocket_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_TransportSocket_serialize(const envoy_config_core_v3_TransportSocket* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__TransportSocket_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_TransportSocket_serialize_ex(const envoy_config_core_v3_TransportSocket* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__TransportSocket_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_core_v3_TransportSocket_config_type_typed_config = 3,
  envoy_config_core_v3_TransportSocket_config_type_NOT_SET = 0
} envoy_config_core_v3_TransportSocket_config_type_oneofcases;
UPB_INLINE envoy_config_core_v3_TransportSocket_config_type_oneofcases envoy_config_core_v3_TransportSocket_config_type_case(const envoy_config_core_v3_TransportSocket* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_core_v3_TransportSocket_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_TransportSocket_clear_config_type(envoy_config_core_v3_TransportSocket* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__core__v3__TransportSocket_msg_init, &field);
}
UPB_INLINE void envoy_config_core_v3_TransportSocket_clear_name(envoy_config_core_v3_TransportSocket* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_TransportSocket_name(const envoy_config_core_v3_TransportSocket* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_core_v3_TransportSocket_clear_typed_config(envoy_config_core_v3_TransportSocket* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_core_v3_TransportSocket_typed_config(const envoy_config_core_v3_TransportSocket* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_TransportSocket_has_typed_config(const envoy_config_core_v3_TransportSocket* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_core_v3_TransportSocket_set_name(envoy_config_core_v3_TransportSocket *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_core_v3_TransportSocket_set_typed_config(envoy_config_core_v3_TransportSocket *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_core_v3_TransportSocket_mutable_typed_config(envoy_config_core_v3_TransportSocket* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_core_v3_TransportSocket_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_core_v3_TransportSocket_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_core_v3_RuntimeFractionalPercent_new(upb_Arena* arena) {
  return (envoy_config_core_v3_RuntimeFractionalPercent*)_upb_Message_New(&envoy__config__core__v3__RuntimeFractionalPercent_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_core_v3_RuntimeFractionalPercent_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_RuntimeFractionalPercent* ret = envoy_config_core_v3_RuntimeFractionalPercent_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RuntimeFractionalPercent_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_RuntimeFractionalPercent* envoy_config_core_v3_RuntimeFractionalPercent_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_RuntimeFractionalPercent* ret = envoy_config_core_v3_RuntimeFractionalPercent_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__RuntimeFractionalPercent_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_RuntimeFractionalPercent_serialize(const envoy_config_core_v3_RuntimeFractionalPercent* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RuntimeFractionalPercent_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_RuntimeFractionalPercent_serialize_ex(const envoy_config_core_v3_RuntimeFractionalPercent* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__RuntimeFractionalPercent_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_RuntimeFractionalPercent_clear_default_value(envoy_config_core_v3_RuntimeFractionalPercent* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_FractionalPercent* envoy_config_core_v3_RuntimeFractionalPercent_default_value(const envoy_config_core_v3_RuntimeFractionalPercent* msg) {
  const struct envoy_type_v3_FractionalPercent* default_val = NULL;
  const struct envoy_type_v3_FractionalPercent* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_core_v3_RuntimeFractionalPercent_has_default_value(const envoy_config_core_v3_RuntimeFractionalPercent* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_core_v3_RuntimeFractionalPercent_clear_runtime_key(envoy_config_core_v3_RuntimeFractionalPercent* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_RuntimeFractionalPercent_runtime_key(const envoy_config_core_v3_RuntimeFractionalPercent* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_RuntimeFractionalPercent_set_default_value(envoy_config_core_v3_RuntimeFractionalPercent *msg, struct envoy_type_v3_FractionalPercent* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_FractionalPercent* envoy_config_core_v3_RuntimeFractionalPercent_mutable_default_value(envoy_config_core_v3_RuntimeFractionalPercent* msg, upb_Arena* arena) {
  struct envoy_type_v3_FractionalPercent* sub = (struct envoy_type_v3_FractionalPercent*)envoy_config_core_v3_RuntimeFractionalPercent_default_value(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_FractionalPercent*)_upb_Message_New(&envoy__type__v3__FractionalPercent_msg_init, arena);
    if (sub) envoy_config_core_v3_RuntimeFractionalPercent_set_default_value(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_core_v3_RuntimeFractionalPercent_set_runtime_key(envoy_config_core_v3_RuntimeFractionalPercent *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_core_v3_ControlPlane* envoy_config_core_v3_ControlPlane_new(upb_Arena* arena) {
  return (envoy_config_core_v3_ControlPlane*)_upb_Message_New(&envoy__config__core__v3__ControlPlane_msg_init, arena);
}
UPB_INLINE envoy_config_core_v3_ControlPlane* envoy_config_core_v3_ControlPlane_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_core_v3_ControlPlane* ret = envoy_config_core_v3_ControlPlane_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__ControlPlane_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_core_v3_ControlPlane* envoy_config_core_v3_ControlPlane_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_core_v3_ControlPlane* ret = envoy_config_core_v3_ControlPlane_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__core__v3__ControlPlane_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_core_v3_ControlPlane_serialize(const envoy_config_core_v3_ControlPlane* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__ControlPlane_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_core_v3_ControlPlane_serialize_ex(const envoy_config_core_v3_ControlPlane* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__core__v3__ControlPlane_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_core_v3_ControlPlane_clear_identifier(envoy_config_core_v3_ControlPlane* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_core_v3_ControlPlane_identifier(const envoy_config_core_v3_ControlPlane* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_core_v3_ControlPlane_set_identifier(envoy_config_core_v3_ControlPlane *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
