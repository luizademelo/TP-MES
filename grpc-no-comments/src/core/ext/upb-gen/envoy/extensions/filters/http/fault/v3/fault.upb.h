
#ifndef ENVOY_EXTENSIONS_FILTERS_HTTP_FAULT_V3_FAULT_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_FILTERS_HTTP_FAULT_V3_FAULT_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/filters/http/fault/v3/fault.upb_minitable.h"

#include "envoy/config/route/v3/route_components.upb_minitable.h"
#include "envoy/extensions/filters/common/fault/v3/fault.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_filters_http_fault_v3_FaultAbort { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_fault_v3_FaultAbort;
typedef struct envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort;
typedef struct envoy_extensions_filters_http_fault_v3_HTTPFault { upb_Message UPB_PRIVATE(base); } envoy_extensions_filters_http_fault_v3_HTTPFault;
struct envoy_config_route_v3_HeaderMatcher;
struct envoy_extensions_filters_common_fault_v3_FaultDelay;
struct envoy_extensions_filters_common_fault_v3_FaultRateLimit;
struct envoy_type_v3_FractionalPercent;
struct google_protobuf_Struct;
struct google_protobuf_UInt32Value;

UPB_INLINE envoy_extensions_filters_http_fault_v3_FaultAbort* envoy_extensions_filters_http_fault_v3_FaultAbort_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_fault_v3_FaultAbort*)_upb_Message_New(&envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_fault_v3_FaultAbort* envoy_extensions_filters_http_fault_v3_FaultAbort_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_fault_v3_FaultAbort* ret = envoy_extensions_filters_http_fault_v3_FaultAbort_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_fault_v3_FaultAbort* envoy_extensions_filters_http_fault_v3_FaultAbort_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_fault_v3_FaultAbort* ret = envoy_extensions_filters_http_fault_v3_FaultAbort_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_fault_v3_FaultAbort_serialize(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_fault_v3_FaultAbort_serialize_ex(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_extensions_filters_http_fault_v3_FaultAbort_error_type_http_status = 2,
  envoy_extensions_filters_http_fault_v3_FaultAbort_error_type_grpc_status = 5,
  envoy_extensions_filters_http_fault_v3_FaultAbort_error_type_header_abort = 4,
  envoy_extensions_filters_http_fault_v3_FaultAbort_error_type_NOT_SET = 0
} envoy_extensions_filters_http_fault_v3_FaultAbort_error_type_oneofcases;
UPB_INLINE envoy_extensions_filters_http_fault_v3_FaultAbort_error_type_oneofcases envoy_extensions_filters_http_fault_v3_FaultAbort_error_type_case(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return (envoy_extensions_filters_http_fault_v3_FaultAbort_error_type_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_FaultAbort_clear_error_type(envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init, &field);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_FaultAbort_clear_http_status(envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_extensions_filters_http_fault_v3_FaultAbort_http_status(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_FaultAbort_has_http_status(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_FaultAbort_clear_percentage(envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_type_v3_FractionalPercent* envoy_extensions_filters_http_fault_v3_FaultAbort_percentage(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const struct envoy_type_v3_FractionalPercent* default_val = NULL;
  const struct envoy_type_v3_FractionalPercent* ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_FaultAbort_has_percentage(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_FaultAbort_clear_header_abort(envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* envoy_extensions_filters_http_fault_v3_FaultAbort_header_abort(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* default_val = NULL;
  const envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* ret;
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_FaultAbort_has_header_abort(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_FaultAbort_clear_grpc_status(envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint32_t envoy_extensions_filters_http_fault_v3_FaultAbort_grpc_status(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  uint32_t default_val = (uint32_t)0u;
  uint32_t ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_FaultAbort_has_grpc_status(const envoy_extensions_filters_http_fault_v3_FaultAbort* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_http_fault_v3_FaultAbort_set_http_status(envoy_extensions_filters_http_fault_v3_FaultAbort *msg, uint32_t value) {
  const upb_MiniTableField field = {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_FaultAbort_set_percentage(envoy_extensions_filters_http_fault_v3_FaultAbort *msg, struct envoy_type_v3_FractionalPercent* value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__type__v3__FractionalPercent_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_type_v3_FractionalPercent* envoy_extensions_filters_http_fault_v3_FaultAbort_mutable_percentage(envoy_extensions_filters_http_fault_v3_FaultAbort* msg, upb_Arena* arena) {
  struct envoy_type_v3_FractionalPercent* sub = (struct envoy_type_v3_FractionalPercent*)envoy_extensions_filters_http_fault_v3_FaultAbort_percentage(msg);
  if (sub == NULL) {
    sub = (struct envoy_type_v3_FractionalPercent*)_upb_Message_New(&envoy__type__v3__FractionalPercent_msg_init, arena);
    if (sub) envoy_extensions_filters_http_fault_v3_FaultAbort_set_percentage(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_FaultAbort_set_header_abort(envoy_extensions_filters_http_fault_v3_FaultAbort *msg, envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* value) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* envoy_extensions_filters_http_fault_v3_FaultAbort_mutable_header_abort(envoy_extensions_filters_http_fault_v3_FaultAbort* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* sub = (struct envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort*)envoy_extensions_filters_http_fault_v3_FaultAbort_header_abort(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort*)_upb_Message_New(&envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init, arena);
    if (sub) envoy_extensions_filters_http_fault_v3_FaultAbort_set_header_abort(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_FaultAbort_set_grpc_status(envoy_extensions_filters_http_fault_v3_FaultAbort *msg, uint32_t value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort*)_upb_Message_New(&envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* ret = envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* ret = envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort_serialize(const envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort_serialize_ex(const envoy_extensions_filters_http_fault_v3_FaultAbort_HeaderAbort* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__fault__v3__FaultAbort__HeaderAbort_msg_init, options, arena, &ptr, len);
  return ptr;
}

UPB_INLINE envoy_extensions_filters_http_fault_v3_HTTPFault* envoy_extensions_filters_http_fault_v3_HTTPFault_new(upb_Arena* arena) {
  return (envoy_extensions_filters_http_fault_v3_HTTPFault*)_upb_Message_New(&envoy__extensions__filters__http__fault__v3__HTTPFault_msg_init, arena);
}
UPB_INLINE envoy_extensions_filters_http_fault_v3_HTTPFault* envoy_extensions_filters_http_fault_v3_HTTPFault_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_filters_http_fault_v3_HTTPFault* ret = envoy_extensions_filters_http_fault_v3_HTTPFault_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__fault__v3__HTTPFault_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_filters_http_fault_v3_HTTPFault* envoy_extensions_filters_http_fault_v3_HTTPFault_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_filters_http_fault_v3_HTTPFault* ret = envoy_extensions_filters_http_fault_v3_HTTPFault_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__filters__http__fault__v3__HTTPFault_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_filters_http_fault_v3_HTTPFault_serialize(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__fault__v3__HTTPFault_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_filters_http_fault_v3_HTTPFault_serialize_ex(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__filters__http__fault__v3__HTTPFault_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_delay(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 144), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_filters_common_fault_v3_FaultDelay* envoy_extensions_filters_http_fault_v3_HTTPFault_delay(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const struct envoy_extensions_filters_common_fault_v3_FaultDelay* default_val = NULL;
  const struct envoy_extensions_filters_common_fault_v3_FaultDelay* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 144), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__common__fault__v3__FaultDelay_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_HTTPFault_has_delay(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 144), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_abort(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 152), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_extensions_filters_http_fault_v3_FaultAbort* envoy_extensions_filters_http_fault_v3_HTTPFault_abort(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const envoy_extensions_filters_http_fault_v3_FaultAbort* default_val = NULL;
  const envoy_extensions_filters_http_fault_v3_FaultAbort* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 152), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_HTTPFault_has_abort(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 152), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_upstream_cluster(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_fault_v3_HTTPFault_upstream_cluster(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_headers(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 160), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_route_v3_HeaderMatcher* const* envoy_extensions_filters_http_fault_v3_HTTPFault_headers(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 160), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const struct envoy_config_route_v3_HeaderMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_http_fault_v3_HTTPFault_headers_upb_array(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg, size_t* size) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 160), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_http_fault_v3_HTTPFault_headers_mutable_upb_array(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {4, UPB_SIZE(20, 160), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_downstream_nodes(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 168), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* envoy_extensions_filters_http_fault_v3_HTTPFault_downstream_nodes(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 168), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_extensions_filters_http_fault_v3_HTTPFault_downstream_nodes_upb_array(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg, size_t* size) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 168), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_extensions_filters_http_fault_v3_HTTPFault_downstream_nodes_mutable_upb_array(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {5, UPB_SIZE(24, 168), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_max_active_faults(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 176), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_UInt32Value* envoy_extensions_filters_http_fault_v3_HTTPFault_max_active_faults(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const struct google_protobuf_UInt32Value* default_val = NULL;
  const struct google_protobuf_UInt32Value* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(28, 176), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_HTTPFault_has_max_active_faults(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 176), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_response_rate_limit(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 184), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_extensions_filters_common_fault_v3_FaultRateLimit* envoy_extensions_filters_http_fault_v3_HTTPFault_response_rate_limit(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const struct envoy_extensions_filters_common_fault_v3_FaultRateLimit* default_val = NULL;
  const struct envoy_extensions_filters_common_fault_v3_FaultRateLimit* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(32, 184), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__common__fault__v3__FaultRateLimit_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_HTTPFault_has_response_rate_limit(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 184), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_delay_percent_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_fault_v3_HTTPFault_delay_percent_runtime(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {8, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_abort_percent_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_fault_v3_HTTPFault_abort_percent_runtime(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {9, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_delay_duration_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {10, 64, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_fault_v3_HTTPFault_delay_duration_runtime(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {10, 64, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_abort_http_status_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {11, UPB_SIZE(72, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_fault_v3_HTTPFault_abort_http_status_runtime(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {11, UPB_SIZE(72, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_max_active_faults_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {12, UPB_SIZE(80, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_fault_v3_HTTPFault_max_active_faults_runtime(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {12, UPB_SIZE(80, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_response_rate_limit_percent_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {13, UPB_SIZE(88, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_fault_v3_HTTPFault_response_rate_limit_percent_runtime(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {13, UPB_SIZE(88, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_abort_grpc_status_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {14, UPB_SIZE(96, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_extensions_filters_http_fault_v3_HTTPFault_abort_grpc_status_runtime(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {14, UPB_SIZE(96, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_disable_downstream_cluster_stats(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {15, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_HTTPFault_disable_downstream_cluster_stats(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  bool default_val = false;
  bool ret;
  const upb_MiniTableField field = {15, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_clear_filter_metadata(envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(36, 192), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Struct* envoy_extensions_filters_http_fault_v3_HTTPFault_filter_metadata(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const struct google_protobuf_Struct* default_val = NULL;
  const struct google_protobuf_Struct* ret;
  const upb_MiniTableField field = {16, UPB_SIZE(36, 192), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_HTTPFault_has_filter_metadata(const envoy_extensions_filters_http_fault_v3_HTTPFault* msg) {
  const upb_MiniTableField field = {16, UPB_SIZE(36, 192), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_delay(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, struct envoy_extensions_filters_common_fault_v3_FaultDelay* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 144), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__common__fault__v3__FaultDelay_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_common_fault_v3_FaultDelay* envoy_extensions_filters_http_fault_v3_HTTPFault_mutable_delay(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_common_fault_v3_FaultDelay* sub = (struct envoy_extensions_filters_common_fault_v3_FaultDelay*)envoy_extensions_filters_http_fault_v3_HTTPFault_delay(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_common_fault_v3_FaultDelay*)_upb_Message_New(&envoy__extensions__filters__common__fault__v3__FaultDelay_msg_init, arena);
    if (sub) envoy_extensions_filters_http_fault_v3_HTTPFault_set_delay(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_abort(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, envoy_extensions_filters_http_fault_v3_FaultAbort* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 152), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_http_fault_v3_FaultAbort* envoy_extensions_filters_http_fault_v3_HTTPFault_mutable_abort(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_http_fault_v3_FaultAbort* sub = (struct envoy_extensions_filters_http_fault_v3_FaultAbort*)envoy_extensions_filters_http_fault_v3_HTTPFault_abort(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_http_fault_v3_FaultAbort*)_upb_Message_New(&envoy__extensions__filters__http__fault__v3__FaultAbort_msg_init, arena);
    if (sub) envoy_extensions_filters_http_fault_v3_HTTPFault_set_abort(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_upstream_cluster(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher** envoy_extensions_filters_http_fault_v3_HTTPFault_mutable_headers(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, size_t* size) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 160), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (struct envoy_config_route_v3_HeaderMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher** envoy_extensions_filters_http_fault_v3_HTTPFault_resize_headers(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 160), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (struct envoy_config_route_v3_HeaderMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_config_route_v3_HeaderMatcher* envoy_extensions_filters_http_fault_v3_HTTPFault_add_headers(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, upb_Arena* arena) {
  upb_MiniTableField field = {4, UPB_SIZE(20, 160), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__route__v3__HeaderMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_config_route_v3_HeaderMatcher* sub = (struct envoy_config_route_v3_HeaderMatcher*)_upb_Message_New(&envoy__config__route__v3__HeaderMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE upb_StringView* envoy_extensions_filters_http_fault_v3_HTTPFault_mutable_downstream_nodes(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, size_t* size) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 168), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* envoy_extensions_filters_http_fault_v3_HTTPFault_resize_downstream_nodes(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 168), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool envoy_extensions_filters_http_fault_v3_HTTPFault_add_downstream_nodes(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {5, UPB_SIZE(24, 168), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_max_active_faults(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, struct google_protobuf_UInt32Value* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(28, 176), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__UInt32Value_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_UInt32Value* envoy_extensions_filters_http_fault_v3_HTTPFault_mutable_max_active_faults(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, upb_Arena* arena) {
  struct google_protobuf_UInt32Value* sub = (struct google_protobuf_UInt32Value*)envoy_extensions_filters_http_fault_v3_HTTPFault_max_active_faults(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_UInt32Value*)_upb_Message_New(&google__protobuf__UInt32Value_msg_init, arena);
    if (sub) envoy_extensions_filters_http_fault_v3_HTTPFault_set_max_active_faults(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_response_rate_limit(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, struct envoy_extensions_filters_common_fault_v3_FaultRateLimit* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(32, 184), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__extensions__filters__common__fault__v3__FaultRateLimit_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_extensions_filters_common_fault_v3_FaultRateLimit* envoy_extensions_filters_http_fault_v3_HTTPFault_mutable_response_rate_limit(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, upb_Arena* arena) {
  struct envoy_extensions_filters_common_fault_v3_FaultRateLimit* sub = (struct envoy_extensions_filters_common_fault_v3_FaultRateLimit*)envoy_extensions_filters_http_fault_v3_HTTPFault_response_rate_limit(msg);
  if (sub == NULL) {
    sub = (struct envoy_extensions_filters_common_fault_v3_FaultRateLimit*)_upb_Message_New(&envoy__extensions__filters__common__fault__v3__FaultRateLimit_msg_init, arena);
    if (sub) envoy_extensions_filters_http_fault_v3_HTTPFault_set_response_rate_limit(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_delay_percent_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, upb_StringView value) {
  const upb_MiniTableField field = {8, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_abort_percent_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, upb_StringView value) {
  const upb_MiniTableField field = {9, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_delay_duration_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, upb_StringView value) {
  const upb_MiniTableField field = {10, 64, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_abort_http_status_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, upb_StringView value) {
  const upb_MiniTableField field = {11, UPB_SIZE(72, 80), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_max_active_faults_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, upb_StringView value) {
  const upb_MiniTableField field = {12, UPB_SIZE(80, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_response_rate_limit_percent_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, upb_StringView value) {
  const upb_MiniTableField field = {13, UPB_SIZE(88, 112), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_abort_grpc_status_runtime(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, upb_StringView value) {
  const upb_MiniTableField field = {14, UPB_SIZE(96, 128), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_disable_downstream_cluster_stats(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, bool value) {
  const upb_MiniTableField field = {15, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_extensions_filters_http_fault_v3_HTTPFault_set_filter_metadata(envoy_extensions_filters_http_fault_v3_HTTPFault *msg, struct google_protobuf_Struct* value) {
  const upb_MiniTableField field = {16, UPB_SIZE(36, 192), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Struct_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Struct* envoy_extensions_filters_http_fault_v3_HTTPFault_mutable_filter_metadata(envoy_extensions_filters_http_fault_v3_HTTPFault* msg, upb_Arena* arena) {
  struct google_protobuf_Struct* sub = (struct google_protobuf_Struct*)envoy_extensions_filters_http_fault_v3_HTTPFault_filter_metadata(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Struct*)_upb_Message_New(&google__protobuf__Struct_msg_init, arena);
    if (sub) envoy_extensions_filters_http_fault_v3_HTTPFault_set_filter_metadata(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
