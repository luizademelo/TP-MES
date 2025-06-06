
#ifndef XDS_DATA_ORCA_V3_ORCA_LOAD_REPORT_PROTO_UPB_H__UPB_H_
#define XDS_DATA_ORCA_V3_ORCA_LOAD_REPORT_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/data/orca/v3/orca_load_report.upb_minitable.h"

#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_data_orca_v3_OrcaLoadReport { upb_Message UPB_PRIVATE(base); } xds_data_orca_v3_OrcaLoadReport;

UPB_INLINE xds_data_orca_v3_OrcaLoadReport* xds_data_orca_v3_OrcaLoadReport_new(upb_Arena* arena) {
  return (xds_data_orca_v3_OrcaLoadReport*)_upb_Message_New(&xds__data__orca__v3__OrcaLoadReport_msg_init, arena);
}
UPB_INLINE xds_data_orca_v3_OrcaLoadReport* xds_data_orca_v3_OrcaLoadReport_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_data_orca_v3_OrcaLoadReport* ret = xds_data_orca_v3_OrcaLoadReport_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__data__orca__v3__OrcaLoadReport_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_data_orca_v3_OrcaLoadReport* xds_data_orca_v3_OrcaLoadReport_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_data_orca_v3_OrcaLoadReport* ret = xds_data_orca_v3_OrcaLoadReport_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__data__orca__v3__OrcaLoadReport_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_data_orca_v3_OrcaLoadReport_serialize(const xds_data_orca_v3_OrcaLoadReport* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__data__orca__v3__OrcaLoadReport_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_data_orca_v3_OrcaLoadReport_serialize_ex(const xds_data_orca_v3_OrcaLoadReport* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__data__orca__v3__OrcaLoadReport_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_clear_cpu_utilization(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 8), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double xds_data_orca_v3_OrcaLoadReport_cpu_utilization(const xds_data_orca_v3_OrcaLoadReport* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {1, UPB_SIZE(24, 8), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_clear_mem_utilization(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 16), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double xds_data_orca_v3_OrcaLoadReport_mem_utilization(const xds_data_orca_v3_OrcaLoadReport* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {2, UPB_SIZE(32, 16), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_clear_rps(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t xds_data_orca_v3_OrcaLoadReport_rps(const xds_data_orca_v3_OrcaLoadReport* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, UPB_SIZE(40, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_clear_request_cost(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t xds_data_orca_v3_OrcaLoadReport_request_cost_size(const xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_request_cost_get(const xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView key, double* val) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__RequestCostEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_request_cost_next(const xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView* key, double* val,
                           size_t* iter) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__RequestCostEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _xds_data_orca_v3_OrcaLoadReport_request_cost_upb_map(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__RequestCostEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _xds_data_orca_v3_OrcaLoadReport_request_cost_mutable_upb_map(xds_data_orca_v3_OrcaLoadReport* msg, upb_Arena* a) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__RequestCostEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(double), a);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_clear_utilization(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t xds_data_orca_v3_OrcaLoadReport_utilization_size(const xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_utilization_get(const xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView key, double* val) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__UtilizationEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_utilization_next(const xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView* key, double* val,
                           size_t* iter) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__UtilizationEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _xds_data_orca_v3_OrcaLoadReport_utilization_upb_map(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__UtilizationEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _xds_data_orca_v3_OrcaLoadReport_utilization_mutable_upb_map(xds_data_orca_v3_OrcaLoadReport* msg, upb_Arena* a) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__UtilizationEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(double), a);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_clear_rps_fractional(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {6, 48, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double xds_data_orca_v3_OrcaLoadReport_rps_fractional(const xds_data_orca_v3_OrcaLoadReport* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {6, 48, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_clear_eps(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {7, 56, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double xds_data_orca_v3_OrcaLoadReport_eps(const xds_data_orca_v3_OrcaLoadReport* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {7, 56, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_clear_named_metrics(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t xds_data_orca_v3_OrcaLoadReport_named_metrics_size(const xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_named_metrics_get(const xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView key, double* val) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__NamedMetricsEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, sizeof(*val));
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_named_metrics_next(const xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView* key, double* val,
                           size_t* iter) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__NamedMetricsEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _xds_data_orca_v3_OrcaLoadReport_named_metrics_upb_map(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__NamedMetricsEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _xds_data_orca_v3_OrcaLoadReport_named_metrics_mutable_upb_map(xds_data_orca_v3_OrcaLoadReport* msg, upb_Arena* a) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__NamedMetricsEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, sizeof(double), a);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_clear_application_utilization(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {9, UPB_SIZE(64, 72), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE double xds_data_orca_v3_OrcaLoadReport_application_utilization(const xds_data_orca_v3_OrcaLoadReport* msg) {
  double default_val = 0;
  double ret;
  const upb_MiniTableField field = {9, UPB_SIZE(64, 72), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_set_cpu_utilization(xds_data_orca_v3_OrcaLoadReport *msg, double value) {
  const upb_MiniTableField field = {1, UPB_SIZE(24, 8), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_set_mem_utilization(xds_data_orca_v3_OrcaLoadReport *msg, double value) {
  const upb_MiniTableField field = {2, UPB_SIZE(32, 16), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_set_rps(xds_data_orca_v3_OrcaLoadReport *msg, uint64_t value) {
  const upb_MiniTableField field = {3, UPB_SIZE(40, 24), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_request_cost_clear(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_request_cost_set(xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView key, double val, upb_Arena* a) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__RequestCostEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_request_cost_delete(xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView key) {
  const upb_MiniTableField field = {4, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_utilization_clear(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_utilization_set(xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView key, double val, upb_Arena* a) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__UtilizationEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_utilization_delete(xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView key) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_set_rps_fractional(xds_data_orca_v3_OrcaLoadReport *msg, double value) {
  const upb_MiniTableField field = {6, 48, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_set_eps(xds_data_orca_v3_OrcaLoadReport *msg, double value) {
  const upb_MiniTableField field = {7, 56, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_named_metrics_clear(xds_data_orca_v3_OrcaLoadReport* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_named_metrics_set(xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView key, double val, upb_Arena* a) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__data__orca__v3__OrcaLoadReport__NamedMetricsEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, sizeof(val), a);
  return _upb_Map_Insert(map, &key, 0, &val, sizeof(val), a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool xds_data_orca_v3_OrcaLoadReport_named_metrics_delete(xds_data_orca_v3_OrcaLoadReport* msg, upb_StringView key) {
  const upb_MiniTableField field = {8, UPB_SIZE(16, 64), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}
UPB_INLINE void xds_data_orca_v3_OrcaLoadReport_set_application_utilization(xds_data_orca_v3_OrcaLoadReport *msg, double value) {
  const upb_MiniTableField field = {9, UPB_SIZE(64, 72), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
