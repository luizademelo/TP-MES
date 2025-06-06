
#ifndef ENVOY_CONFIG_METRICS_V3_STATS_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_METRICS_V3_STATS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/metrics/v3/stats.upb_minitable.h"

#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_metrics_v3_StatsSink { upb_Message UPB_PRIVATE(base); } envoy_config_metrics_v3_StatsSink;
typedef struct envoy_config_metrics_v3_StatsConfig { upb_Message UPB_PRIVATE(base); } envoy_config_metrics_v3_StatsConfig;
typedef struct envoy_config_metrics_v3_StatsMatcher { upb_Message UPB_PRIVATE(base); } envoy_config_metrics_v3_StatsMatcher;
typedef struct envoy_config_metrics_v3_TagSpecifier { upb_Message UPB_PRIVATE(base); } envoy_config_metrics_v3_TagSpecifier;
typedef struct envoy_config_metrics_v3_HistogramBucketSettings { upb_Message UPB_PRIVATE(base); } envoy_config_metrics_v3_HistogramBucketSettings;
typedef struct envoy_config_metrics_v3_StatsdSink { upb_Message UPB_PRIVATE(base); } envoy_config_metrics_v3_StatsdSink;
typedef struct envoy_config_metrics_v3_DogStatsdSink { upb_Message UPB_PRIVATE(base); } envoy_config_metrics_v3_DogStatsdSink;
typedef struct envoy_config_metrics_v3_HystrixSink { upb_Message UPB_PRIVATE(base); } envoy_config_metrics_v3_HystrixSink;
struct envoy_config_core_v3_Address;
struct envoy_type_matcher_v3_ListStringMatcher;
struct envoy_type_matcher_v3_StringMatcher;
struct google_protobuf_Any;
struct google_protobuf_BoolValue;
struct google_protobuf_UInt64Value;

UPB_INLINE envoy_config_metrics_v3_StatsSink* envoy_config_metrics_v3_StatsSink_new(upb_Arena* arena) {
  return (envoy_config_metrics_v3_StatsSink*)_upb_Message_New(&envoy__config__metrics__v3__StatsSink_msg_init, arena);
}
UPB_INLINE envoy_config_metrics_v3_StatsSink* envoy_config_metrics_v3_StatsSink_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_metrics_v3_StatsSink* ret = envoy_config_metrics_v3_StatsSink_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__StatsSink_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_metrics_v3_StatsSink* envoy_config_metrics_v3_StatsSink_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_metrics_v3_StatsSink* ret = envoy_config_metrics_v3_StatsSink_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__StatsSink_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_metrics_v3_StatsSink_serialize(const envoy_config_metrics_v3_StatsSink* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsSink_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_metrics_v3_StatsSink_serialize_ex(const envoy_config_metrics_v3_StatsSink* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsSink_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_metrics_v3_StatsSink_config_type_typed_config = 3,
  envoy_config_metrics_v3_StatsSink_config_type_NOT_SET = 0
} envoy_config_metrics_v3_StatsSink_config_type_oneofcases;
UPB_INLINE envoy_config_metrics_v3_StatsSink_config_type_oneofcases envoy_config_metrics_v3_StatsSink_config_type_case(const envoy_config_metrics_v3_StatsSink* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_metrics_v3_StatsSink_config_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsSink_clear_config_type(envoy_config_metrics_v3_StatsSink* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsSink_msg_init, &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsSink_clear_name(envoy_config_metrics_v3_StatsSink* msg) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_metrics_v3_StatsSink_name(const envoy_config_metrics_v3_StatsSink* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_metrics_v3_StatsSink_clear_typed_config(envoy_config_metrics_v3_StatsSink* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Any* envoy_config_metrics_v3_StatsSink_typed_config(const envoy_config_metrics_v3_StatsSink* msg) {
  const struct google_protobuf_Any* default_val = NULL;
  const struct google_protobuf_Any* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_StatsSink_has_typed_config(const envoy_config_metrics_v3_StatsSink* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_metrics_v3_StatsSink_set_name(envoy_config_metrics_v3_StatsSink *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_metrics_v3_StatsSink_set_typed_config(envoy_config_metrics_v3_StatsSink *msg, struct google_protobuf_Any* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Any_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Any* envoy_config_metrics_v3_StatsSink_mutable_typed_config(envoy_config_metrics_v3_StatsSink* msg, upb_Arena* arena) {
  struct google_protobuf_Any* sub = (struct google_protobuf_Any*)envoy_config_metrics_v3_StatsSink_typed_config(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Any*)_upb_Message_New(&google__protobuf__Any_msg_init, arena);
    if (sub) envoy_config_metrics_v3_StatsSink_set_typed_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_metrics_v3_StatsConfig* envoy_config_metrics_v3_StatsConfig_new(upb_Arena* arena) {
  return (envoy_config_metrics_v3_StatsConfig*)_upb_Message_New(&envoy__config__metrics__v3__StatsConfig_msg_init, arena);
}
UPB_INLINE envoy_config_metrics_v3_StatsConfig* envoy_config_metrics_v3_StatsConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_metrics_v3_StatsConfig* ret = envoy_config_metrics_v3_StatsConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__StatsConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_metrics_v3_StatsConfig* envoy_config_metrics_v3_StatsConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_metrics_v3_StatsConfig* ret = envoy_config_metrics_v3_StatsConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__StatsConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_metrics_v3_StatsConfig_serialize(const envoy_config_metrics_v3_StatsConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_metrics_v3_StatsConfig_serialize_ex(const envoy_config_metrics_v3_StatsConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_metrics_v3_StatsConfig_clear_stats_tags(envoy_config_metrics_v3_StatsConfig* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_metrics_v3_TagSpecifier* const* envoy_config_metrics_v3_StatsConfig_stats_tags(const envoy_config_metrics_v3_StatsConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__TagSpecifier_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_metrics_v3_TagSpecifier* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_metrics_v3_StatsConfig_stats_tags_upb_array(const envoy_config_metrics_v3_StatsConfig* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__TagSpecifier_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_metrics_v3_StatsConfig_stats_tags_mutable_upb_array(envoy_config_metrics_v3_StatsConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__TagSpecifier_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_config_metrics_v3_StatsConfig_clear_use_all_default_tags(envoy_config_metrics_v3_StatsConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_BoolValue* envoy_config_metrics_v3_StatsConfig_use_all_default_tags(const envoy_config_metrics_v3_StatsConfig* msg) {
  const struct google_protobuf_BoolValue* default_val = NULL;
  const struct google_protobuf_BoolValue* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_StatsConfig_has_use_all_default_tags(const envoy_config_metrics_v3_StatsConfig* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsConfig_clear_stats_matcher(envoy_config_metrics_v3_StatsConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_metrics_v3_StatsMatcher* envoy_config_metrics_v3_StatsConfig_stats_matcher(const envoy_config_metrics_v3_StatsConfig* msg) {
  const envoy_config_metrics_v3_StatsMatcher* default_val = NULL;
  const envoy_config_metrics_v3_StatsMatcher* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__StatsMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_StatsConfig_has_stats_matcher(const envoy_config_metrics_v3_StatsConfig* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsConfig_clear_histogram_bucket_settings(envoy_config_metrics_v3_StatsConfig* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_config_metrics_v3_HistogramBucketSettings* const* envoy_config_metrics_v3_StatsConfig_histogram_bucket_settings(const envoy_config_metrics_v3_StatsConfig* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__HistogramBucketSettings_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_config_metrics_v3_HistogramBucketSettings* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_metrics_v3_StatsConfig_histogram_bucket_settings_upb_array(const envoy_config_metrics_v3_StatsConfig* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__HistogramBucketSettings_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_metrics_v3_StatsConfig_histogram_bucket_settings_mutable_upb_array(envoy_config_metrics_v3_StatsConfig* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__HistogramBucketSettings_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_config_metrics_v3_TagSpecifier** envoy_config_metrics_v3_StatsConfig_mutable_stats_tags(envoy_config_metrics_v3_StatsConfig* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__TagSpecifier_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_metrics_v3_TagSpecifier**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_metrics_v3_TagSpecifier** envoy_config_metrics_v3_StatsConfig_resize_stats_tags(envoy_config_metrics_v3_StatsConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_metrics_v3_TagSpecifier**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_metrics_v3_TagSpecifier* envoy_config_metrics_v3_StatsConfig_add_stats_tags(envoy_config_metrics_v3_StatsConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__TagSpecifier_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_metrics_v3_TagSpecifier* sub = (struct envoy_config_metrics_v3_TagSpecifier*)_upb_Message_New(&envoy__config__metrics__v3__TagSpecifier_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_config_metrics_v3_StatsConfig_set_use_all_default_tags(envoy_config_metrics_v3_StatsConfig *msg, struct google_protobuf_BoolValue* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__BoolValue_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_BoolValue* envoy_config_metrics_v3_StatsConfig_mutable_use_all_default_tags(envoy_config_metrics_v3_StatsConfig* msg, upb_Arena* arena) {
  struct google_protobuf_BoolValue* sub = (struct google_protobuf_BoolValue*)envoy_config_metrics_v3_StatsConfig_use_all_default_tags(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_BoolValue*)_upb_Message_New(&google__protobuf__BoolValue_msg_init, arena);
    if (sub) envoy_config_metrics_v3_StatsConfig_set_use_all_default_tags(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_metrics_v3_StatsConfig_set_stats_matcher(envoy_config_metrics_v3_StatsConfig *msg, envoy_config_metrics_v3_StatsMatcher* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__StatsMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_metrics_v3_StatsMatcher* envoy_config_metrics_v3_StatsConfig_mutable_stats_matcher(envoy_config_metrics_v3_StatsConfig* msg, upb_Arena* arena) {
  struct envoy_config_metrics_v3_StatsMatcher* sub = (struct envoy_config_metrics_v3_StatsMatcher*)envoy_config_metrics_v3_StatsConfig_stats_matcher(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_metrics_v3_StatsMatcher*)_upb_Message_New(&envoy__config__metrics__v3__StatsMatcher_msg_init, arena);
    if (sub) envoy_config_metrics_v3_StatsConfig_set_stats_matcher(msg, sub);
  }
  return sub;
}
UPB_INLINE envoy_config_metrics_v3_HistogramBucketSettings** envoy_config_metrics_v3_StatsConfig_mutable_histogram_bucket_settings(envoy_config_metrics_v3_StatsConfig* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__HistogramBucketSettings_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_config_metrics_v3_HistogramBucketSettings**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_config_metrics_v3_HistogramBucketSettings** envoy_config_metrics_v3_StatsConfig_resize_histogram_bucket_settings(envoy_config_metrics_v3_StatsConfig* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_metrics_v3_HistogramBucketSettings**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_metrics_v3_HistogramBucketSettings* envoy_config_metrics_v3_StatsConfig_add_histogram_bucket_settings(envoy_config_metrics_v3_StatsConfig* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__metrics__v3__HistogramBucketSettings_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_metrics_v3_HistogramBucketSettings* sub = (struct envoy_config_metrics_v3_HistogramBucketSettings*)_upb_Message_New(&envoy__config__metrics__v3__HistogramBucketSettings_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_config_metrics_v3_StatsMatcher* envoy_config_metrics_v3_StatsMatcher_new(upb_Arena* arena) {
  return (envoy_config_metrics_v3_StatsMatcher*)_upb_Message_New(&envoy__config__metrics__v3__StatsMatcher_msg_init, arena);
}
UPB_INLINE envoy_config_metrics_v3_StatsMatcher* envoy_config_metrics_v3_StatsMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_metrics_v3_StatsMatcher* ret = envoy_config_metrics_v3_StatsMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__StatsMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_metrics_v3_StatsMatcher* envoy_config_metrics_v3_StatsMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_metrics_v3_StatsMatcher* ret = envoy_config_metrics_v3_StatsMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__StatsMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_metrics_v3_StatsMatcher_serialize(const envoy_config_metrics_v3_StatsMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_metrics_v3_StatsMatcher_serialize_ex(const envoy_config_metrics_v3_StatsMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_metrics_v3_StatsMatcher_stats_matcher_reject_all = 1,
  envoy_config_metrics_v3_StatsMatcher_stats_matcher_exclusion_list = 2,
  envoy_config_metrics_v3_StatsMatcher_stats_matcher_inclusion_list = 3,
  envoy_config_metrics_v3_StatsMatcher_stats_matcher_NOT_SET = 0
} envoy_config_metrics_v3_StatsMatcher_stats_matcher_oneofcases;
UPB_INLINE envoy_config_metrics_v3_StatsMatcher_stats_matcher_oneofcases envoy_config_metrics_v3_StatsMatcher_stats_matcher_case(const envoy_config_metrics_v3_StatsMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return (envoy_config_metrics_v3_StatsMatcher_stats_matcher_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsMatcher_clear_stats_matcher(envoy_config_metrics_v3_StatsMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsMatcher_msg_init, &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsMatcher_clear_reject_all(envoy_config_metrics_v3_StatsMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_config_metrics_v3_StatsMatcher_reject_all(const envoy_config_metrics_v3_StatsMatcher* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_StatsMatcher_has_reject_all(const envoy_config_metrics_v3_StatsMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsMatcher_clear_exclusion_list(envoy_config_metrics_v3_StatsMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_ListStringMatcher* envoy_config_metrics_v3_StatsMatcher_exclusion_list(const envoy_config_metrics_v3_StatsMatcher* msg) {
  const struct envoy_type_matcher_v3_ListStringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_ListStringMatcher* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ListStringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_StatsMatcher_has_exclusion_list(const envoy_config_metrics_v3_StatsMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsMatcher_clear_inclusion_list(envoy_config_metrics_v3_StatsMatcher* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_ListStringMatcher* envoy_config_metrics_v3_StatsMatcher_inclusion_list(const envoy_config_metrics_v3_StatsMatcher* msg) {
  const struct envoy_type_matcher_v3_ListStringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_ListStringMatcher* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ListStringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_StatsMatcher_has_inclusion_list(const envoy_config_metrics_v3_StatsMatcher* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_metrics_v3_StatsMatcher_set_reject_all(envoy_config_metrics_v3_StatsMatcher *msg, bool value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_metrics_v3_StatsMatcher_set_exclusion_list(envoy_config_metrics_v3_StatsMatcher *msg, struct envoy_type_matcher_v3_ListStringMatcher* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ListStringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_ListStringMatcher* envoy_config_metrics_v3_StatsMatcher_mutable_exclusion_list(envoy_config_metrics_v3_StatsMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_ListStringMatcher* sub = (struct envoy_type_matcher_v3_ListStringMatcher*)envoy_config_metrics_v3_StatsMatcher_exclusion_list(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_ListStringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__ListStringMatcher_msg_init, arena);
    if (sub) envoy_config_metrics_v3_StatsMatcher_set_exclusion_list(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_metrics_v3_StatsMatcher_set_inclusion_list(envoy_config_metrics_v3_StatsMatcher *msg, struct envoy_type_matcher_v3_ListStringMatcher* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__ListStringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_ListStringMatcher* envoy_config_metrics_v3_StatsMatcher_mutable_inclusion_list(envoy_config_metrics_v3_StatsMatcher* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_ListStringMatcher* sub = (struct envoy_type_matcher_v3_ListStringMatcher*)envoy_config_metrics_v3_StatsMatcher_inclusion_list(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_ListStringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__ListStringMatcher_msg_init, arena);
    if (sub) envoy_config_metrics_v3_StatsMatcher_set_inclusion_list(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_metrics_v3_TagSpecifier* envoy_config_metrics_v3_TagSpecifier_new(upb_Arena* arena) {
  return (envoy_config_metrics_v3_TagSpecifier*)_upb_Message_New(&envoy__config__metrics__v3__TagSpecifier_msg_init, arena);
}
UPB_INLINE envoy_config_metrics_v3_TagSpecifier* envoy_config_metrics_v3_TagSpecifier_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_metrics_v3_TagSpecifier* ret = envoy_config_metrics_v3_TagSpecifier_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__TagSpecifier_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_metrics_v3_TagSpecifier* envoy_config_metrics_v3_TagSpecifier_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_metrics_v3_TagSpecifier* ret = envoy_config_metrics_v3_TagSpecifier_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__TagSpecifier_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_metrics_v3_TagSpecifier_serialize(const envoy_config_metrics_v3_TagSpecifier* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__TagSpecifier_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_metrics_v3_TagSpecifier_serialize_ex(const envoy_config_metrics_v3_TagSpecifier* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__TagSpecifier_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_metrics_v3_TagSpecifier_tag_value_regex = 2,
  envoy_config_metrics_v3_TagSpecifier_tag_value_fixed_value = 3,
  envoy_config_metrics_v3_TagSpecifier_tag_value_NOT_SET = 0
} envoy_config_metrics_v3_TagSpecifier_tag_value_oneofcases;
UPB_INLINE envoy_config_metrics_v3_TagSpecifier_tag_value_oneofcases envoy_config_metrics_v3_TagSpecifier_tag_value_case(const envoy_config_metrics_v3_TagSpecifier* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_config_metrics_v3_TagSpecifier_tag_value_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_TagSpecifier_clear_tag_value(envoy_config_metrics_v3_TagSpecifier* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__metrics__v3__TagSpecifier_msg_init, &field);
}
UPB_INLINE void envoy_config_metrics_v3_TagSpecifier_clear_tag_name(envoy_config_metrics_v3_TagSpecifier* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_metrics_v3_TagSpecifier_tag_name(const envoy_config_metrics_v3_TagSpecifier* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_metrics_v3_TagSpecifier_clear_regex(envoy_config_metrics_v3_TagSpecifier* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_metrics_v3_TagSpecifier_regex(const envoy_config_metrics_v3_TagSpecifier* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_TagSpecifier_has_regex(const envoy_config_metrics_v3_TagSpecifier* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_TagSpecifier_clear_fixed_value(envoy_config_metrics_v3_TagSpecifier* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_metrics_v3_TagSpecifier_fixed_value(const envoy_config_metrics_v3_TagSpecifier* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_TagSpecifier_has_fixed_value(const envoy_config_metrics_v3_TagSpecifier* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_metrics_v3_TagSpecifier_set_tag_name(envoy_config_metrics_v3_TagSpecifier *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_metrics_v3_TagSpecifier_set_regex(envoy_config_metrics_v3_TagSpecifier *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_metrics_v3_TagSpecifier_set_fixed_value(envoy_config_metrics_v3_TagSpecifier *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_metrics_v3_HistogramBucketSettings* envoy_config_metrics_v3_HistogramBucketSettings_new(upb_Arena* arena) {
  return (envoy_config_metrics_v3_HistogramBucketSettings*)_upb_Message_New(&envoy__config__metrics__v3__HistogramBucketSettings_msg_init, arena);
}
UPB_INLINE envoy_config_metrics_v3_HistogramBucketSettings* envoy_config_metrics_v3_HistogramBucketSettings_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_metrics_v3_HistogramBucketSettings* ret = envoy_config_metrics_v3_HistogramBucketSettings_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__HistogramBucketSettings_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_metrics_v3_HistogramBucketSettings* envoy_config_metrics_v3_HistogramBucketSettings_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_metrics_v3_HistogramBucketSettings* ret = envoy_config_metrics_v3_HistogramBucketSettings_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__HistogramBucketSettings_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_metrics_v3_HistogramBucketSettings_serialize(const envoy_config_metrics_v3_HistogramBucketSettings* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__HistogramBucketSettings_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_metrics_v3_HistogramBucketSettings_serialize_ex(const envoy_config_metrics_v3_HistogramBucketSettings* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__HistogramBucketSettings_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_metrics_v3_HistogramBucketSettings_clear_match(envoy_config_metrics_v3_HistogramBucketSettings* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_matcher_v3_StringMatcher* envoy_config_metrics_v3_HistogramBucketSettings_match(const envoy_config_metrics_v3_HistogramBucketSettings* msg) {
  const struct envoy_type_matcher_v3_StringMatcher* default_val = NULL;
  const struct envoy_type_matcher_v3_StringMatcher* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_HistogramBucketSettings_has_match(const envoy_config_metrics_v3_HistogramBucketSettings* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_HistogramBucketSettings_clear_buckets(envoy_config_metrics_v3_HistogramBucketSettings* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double const* envoy_config_metrics_v3_HistogramBucketSettings_buckets(const envoy_config_metrics_v3_HistogramBucketSettings* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (double const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_config_metrics_v3_HistogramBucketSettings_buckets_upb_array(const envoy_config_metrics_v3_HistogramBucketSettings* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_config_metrics_v3_HistogramBucketSettings_buckets_mutable_upb_array(envoy_config_metrics_v3_HistogramBucketSettings* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void envoy_config_metrics_v3_HistogramBucketSettings_set_match(envoy_config_metrics_v3_HistogramBucketSettings *msg, struct envoy_type_matcher_v3_StringMatcher* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__matcher__v3__StringMatcher_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_matcher_v3_StringMatcher* envoy_config_metrics_v3_HistogramBucketSettings_mutable_match(envoy_config_metrics_v3_HistogramBucketSettings* msg, upb_Arena* arena) {
  struct envoy_type_matcher_v3_StringMatcher* sub = (struct envoy_type_matcher_v3_StringMatcher*)envoy_config_metrics_v3_HistogramBucketSettings_match(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_matcher_v3_StringMatcher*)_upb_Message_New(&envoy__type__matcher__v3__StringMatcher_msg_init, arena);
    if (sub) envoy_config_metrics_v3_HistogramBucketSettings_set_match(msg, sub);
  }
  return sub;
}
UPB_INLINE double* envoy_config_metrics_v3_HistogramBucketSettings_mutable_buckets(envoy_config_metrics_v3_HistogramBucketSettings* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (double*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE double* envoy_config_metrics_v3_HistogramBucketSettings_resize_buckets(envoy_config_metrics_v3_HistogramBucketSettings* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (double*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_config_metrics_v3_HistogramBucketSettings_add_buckets(envoy_config_metrics_v3_HistogramBucketSettings* msg, double val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

UPB_INLINE envoy_config_metrics_v3_StatsdSink* envoy_config_metrics_v3_StatsdSink_new(upb_Arena* arena) {
  return (envoy_config_metrics_v3_StatsdSink*)_upb_Message_New(&envoy__config__metrics__v3__StatsdSink_msg_init, arena);
}
UPB_INLINE envoy_config_metrics_v3_StatsdSink* envoy_config_metrics_v3_StatsdSink_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_metrics_v3_StatsdSink* ret = envoy_config_metrics_v3_StatsdSink_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__StatsdSink_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_metrics_v3_StatsdSink* envoy_config_metrics_v3_StatsdSink_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_metrics_v3_StatsdSink* ret = envoy_config_metrics_v3_StatsdSink_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__StatsdSink_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_metrics_v3_StatsdSink_serialize(const envoy_config_metrics_v3_StatsdSink* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsdSink_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_metrics_v3_StatsdSink_serialize_ex(const envoy_config_metrics_v3_StatsdSink* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsdSink_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_metrics_v3_StatsdSink_statsd_specifier_address = 1,
  envoy_config_metrics_v3_StatsdSink_statsd_specifier_tcp_cluster_name = 2,
  envoy_config_metrics_v3_StatsdSink_statsd_specifier_NOT_SET = 0
} envoy_config_metrics_v3_StatsdSink_statsd_specifier_oneofcases;
UPB_INLINE envoy_config_metrics_v3_StatsdSink_statsd_specifier_oneofcases envoy_config_metrics_v3_StatsdSink_statsd_specifier_case(const envoy_config_metrics_v3_StatsdSink* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_metrics_v3_StatsdSink_statsd_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsdSink_clear_statsd_specifier(envoy_config_metrics_v3_StatsdSink* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__metrics__v3__StatsdSink_msg_init, &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsdSink_clear_address(envoy_config_metrics_v3_StatsdSink* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_config_metrics_v3_StatsdSink_address(const envoy_config_metrics_v3_StatsdSink* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_StatsdSink_has_address(const envoy_config_metrics_v3_StatsdSink* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsdSink_clear_tcp_cluster_name(envoy_config_metrics_v3_StatsdSink* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_metrics_v3_StatsdSink_tcp_cluster_name(const envoy_config_metrics_v3_StatsdSink* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_StatsdSink_has_tcp_cluster_name(const envoy_config_metrics_v3_StatsdSink* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_StatsdSink_clear_prefix(envoy_config_metrics_v3_StatsdSink* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_metrics_v3_StatsdSink_prefix(const envoy_config_metrics_v3_StatsdSink* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_metrics_v3_StatsdSink_set_address(envoy_config_metrics_v3_StatsdSink *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_config_metrics_v3_StatsdSink_mutable_address(envoy_config_metrics_v3_StatsdSink* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_config_metrics_v3_StatsdSink_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_config_metrics_v3_StatsdSink_set_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_metrics_v3_StatsdSink_set_tcp_cluster_name(envoy_config_metrics_v3_StatsdSink *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_metrics_v3_StatsdSink_set_prefix(envoy_config_metrics_v3_StatsdSink *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_config_metrics_v3_DogStatsdSink* envoy_config_metrics_v3_DogStatsdSink_new(upb_Arena* arena) {
  return (envoy_config_metrics_v3_DogStatsdSink*)_upb_Message_New(&envoy__config__metrics__v3__DogStatsdSink_msg_init, arena);
}
UPB_INLINE envoy_config_metrics_v3_DogStatsdSink* envoy_config_metrics_v3_DogStatsdSink_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_metrics_v3_DogStatsdSink* ret = envoy_config_metrics_v3_DogStatsdSink_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__DogStatsdSink_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_metrics_v3_DogStatsdSink* envoy_config_metrics_v3_DogStatsdSink_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_metrics_v3_DogStatsdSink* ret = envoy_config_metrics_v3_DogStatsdSink_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__DogStatsdSink_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_metrics_v3_DogStatsdSink_serialize(const envoy_config_metrics_v3_DogStatsdSink* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__DogStatsdSink_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_metrics_v3_DogStatsdSink_serialize_ex(const envoy_config_metrics_v3_DogStatsdSink* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__DogStatsdSink_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_config_metrics_v3_DogStatsdSink_dog_statsd_specifier_address = 1,
  envoy_config_metrics_v3_DogStatsdSink_dog_statsd_specifier_NOT_SET = 0
} envoy_config_metrics_v3_DogStatsdSink_dog_statsd_specifier_oneofcases;
UPB_INLINE envoy_config_metrics_v3_DogStatsdSink_dog_statsd_specifier_oneofcases envoy_config_metrics_v3_DogStatsdSink_dog_statsd_specifier_case(const envoy_config_metrics_v3_DogStatsdSink* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_config_metrics_v3_DogStatsdSink_dog_statsd_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_DogStatsdSink_clear_dog_statsd_specifier(envoy_config_metrics_v3_DogStatsdSink* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__config__metrics__v3__DogStatsdSink_msg_init, &field);
}
UPB_INLINE void envoy_config_metrics_v3_DogStatsdSink_clear_address(envoy_config_metrics_v3_DogStatsdSink* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_Address* envoy_config_metrics_v3_DogStatsdSink_address(const envoy_config_metrics_v3_DogStatsdSink* msg) {
  const struct envoy_config_core_v3_Address* default_val = NULL;
  const struct envoy_config_core_v3_Address* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_DogStatsdSink_has_address(const envoy_config_metrics_v3_DogStatsdSink* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_metrics_v3_DogStatsdSink_clear_prefix(envoy_config_metrics_v3_DogStatsdSink* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_config_metrics_v3_DogStatsdSink_prefix(const envoy_config_metrics_v3_DogStatsdSink* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_config_metrics_v3_DogStatsdSink_clear_max_bytes_per_datagram(envoy_config_metrics_v3_DogStatsdSink* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt64Value* envoy_config_metrics_v3_DogStatsdSink_max_bytes_per_datagram(const envoy_config_metrics_v3_DogStatsdSink* msg) {
  const struct google_protobuf_UInt64Value* default_val = NULL;
  const struct google_protobuf_UInt64Value* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_metrics_v3_DogStatsdSink_has_max_bytes_per_datagram(const envoy_config_metrics_v3_DogStatsdSink* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_metrics_v3_DogStatsdSink_set_address(envoy_config_metrics_v3_DogStatsdSink *msg, struct envoy_config_core_v3_Address* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__Address_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_Address* envoy_config_metrics_v3_DogStatsdSink_mutable_address(envoy_config_metrics_v3_DogStatsdSink* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_Address* sub = (struct envoy_config_core_v3_Address*)envoy_config_metrics_v3_DogStatsdSink_address(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_Address*)_upb_Message_New(&envoy__config__core__v3__Address_msg_init, arena);
    if (sub) envoy_config_metrics_v3_DogStatsdSink_set_address(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_metrics_v3_DogStatsdSink_set_prefix(envoy_config_metrics_v3_DogStatsdSink *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_config_metrics_v3_DogStatsdSink_set_max_bytes_per_datagram(envoy_config_metrics_v3_DogStatsdSink *msg, struct google_protobuf_UInt64Value* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(12, 32), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt64Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt64Value* envoy_config_metrics_v3_DogStatsdSink_mutable_max_bytes_per_datagram(envoy_config_metrics_v3_DogStatsdSink* msg, upb_Arena* arena) {
  struct google_protobuf_UInt64Value* sub = (struct google_protobuf_UInt64Value*)envoy_config_metrics_v3_DogStatsdSink_max_bytes_per_datagram(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt64Value*)_upb_Message_New(&google__protobuf__UInt64Value_msg_init, arena);
    if (sub) envoy_config_metrics_v3_DogStatsdSink_set_max_bytes_per_datagram(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_metrics_v3_HystrixSink* envoy_config_metrics_v3_HystrixSink_new(upb_Arena* arena) {
  return (envoy_config_metrics_v3_HystrixSink*)_upb_Message_New(&envoy__config__metrics__v3__HystrixSink_msg_init, arena);
}
UPB_INLINE envoy_config_metrics_v3_HystrixSink* envoy_config_metrics_v3_HystrixSink_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_metrics_v3_HystrixSink* ret = envoy_config_metrics_v3_HystrixSink_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__HystrixSink_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_metrics_v3_HystrixSink* envoy_config_metrics_v3_HystrixSink_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_metrics_v3_HystrixSink* ret = envoy_config_metrics_v3_HystrixSink_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__metrics__v3__HystrixSink_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_metrics_v3_HystrixSink_serialize(const envoy_config_metrics_v3_HystrixSink* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__HystrixSink_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_metrics_v3_HystrixSink_serialize_ex(const envoy_config_metrics_v3_HystrixSink* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__metrics__v3__HystrixSink_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_metrics_v3_HystrixSink_clear_num_buckets(envoy_config_metrics_v3_HystrixSink* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int64_t envoy_config_metrics_v3_HystrixSink_num_buckets(const envoy_config_metrics_v3_HystrixSink* msg) {
  int64_t default_val = (int64_t)0ll;
  int64_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_config_metrics_v3_HystrixSink_set_num_buckets(envoy_config_metrics_v3_HystrixSink *msg, int64_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
