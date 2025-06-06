
#ifndef XDS_SERVICE_ORCA_V3_ORCA_PROTO_UPB_H__UPB_H_
#define XDS_SERVICE_ORCA_V3_ORCA_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/service/orca/v3/orca.upb_minitable.h"

#include "xds/data/orca/v3/orca_load_report.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_service_orca_v3_OrcaLoadReportRequest { upb_Message UPB_PRIVATE(base); } xds_service_orca_v3_OrcaLoadReportRequest;
struct google_protobuf_Duration;

UPB_INLINE xds_service_orca_v3_OrcaLoadReportRequest* xds_service_orca_v3_OrcaLoadReportRequest_new(upb_Arena* arena) {
  return (xds_service_orca_v3_OrcaLoadReportRequest*)_upb_Message_New(&xds__service__orca__v3__OrcaLoadReportRequest_msg_init, arena);
}
UPB_INLINE xds_service_orca_v3_OrcaLoadReportRequest* xds_service_orca_v3_OrcaLoadReportRequest_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_service_orca_v3_OrcaLoadReportRequest* ret = xds_service_orca_v3_OrcaLoadReportRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__service__orca__v3__OrcaLoadReportRequest_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_service_orca_v3_OrcaLoadReportRequest* xds_service_orca_v3_OrcaLoadReportRequest_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_service_orca_v3_OrcaLoadReportRequest* ret = xds_service_orca_v3_OrcaLoadReportRequest_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__service__orca__v3__OrcaLoadReportRequest_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_service_orca_v3_OrcaLoadReportRequest_serialize(const xds_service_orca_v3_OrcaLoadReportRequest* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__service__orca__v3__OrcaLoadReportRequest_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_service_orca_v3_OrcaLoadReportRequest_serialize_ex(const xds_service_orca_v3_OrcaLoadReportRequest* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__service__orca__v3__OrcaLoadReportRequest_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_service_orca_v3_OrcaLoadReportRequest_clear_report_interval(xds_service_orca_v3_OrcaLoadReportRequest* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Duration* xds_service_orca_v3_OrcaLoadReportRequest_report_interval(const xds_service_orca_v3_OrcaLoadReportRequest* msg) {
  const struct google_protobuf_Duration* default_val = NULL;
  const struct google_protobuf_Duration* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_service_orca_v3_OrcaLoadReportRequest_has_report_interval(const xds_service_orca_v3_OrcaLoadReportRequest* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_service_orca_v3_OrcaLoadReportRequest_clear_request_cost_names(xds_service_orca_v3_OrcaLoadReportRequest* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* xds_service_orca_v3_OrcaLoadReportRequest_request_cost_names(const xds_service_orca_v3_OrcaLoadReportRequest* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _xds_service_orca_v3_OrcaLoadReportRequest_request_cost_names_upb_array(const xds_service_orca_v3_OrcaLoadReportRequest* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _xds_service_orca_v3_OrcaLoadReportRequest_request_cost_names_mutable_upb_array(xds_service_orca_v3_OrcaLoadReportRequest* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void xds_service_orca_v3_OrcaLoadReportRequest_set_report_interval(xds_service_orca_v3_OrcaLoadReportRequest *msg, struct google_protobuf_Duration* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Duration_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Duration* xds_service_orca_v3_OrcaLoadReportRequest_mutable_report_interval(xds_service_orca_v3_OrcaLoadReportRequest* msg, upb_Arena* arena) {
  struct google_protobuf_Duration* sub = (struct google_protobuf_Duration*)xds_service_orca_v3_OrcaLoadReportRequest_report_interval(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Duration*)_upb_Message_New(&google__protobuf__Duration_msg_init, arena);
    if (sub) xds_service_orca_v3_OrcaLoadReportRequest_set_report_interval(msg, sub);
  }
  return sub;
}
UPB_INLINE upb_StringView* xds_service_orca_v3_OrcaLoadReportRequest_mutable_request_cost_names(xds_service_orca_v3_OrcaLoadReportRequest* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* xds_service_orca_v3_OrcaLoadReportRequest_resize_request_cost_names(xds_service_orca_v3_OrcaLoadReportRequest* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool xds_service_orca_v3_OrcaLoadReportRequest_add_request_cost_names(xds_service_orca_v3_OrcaLoadReportRequest* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
