
#ifndef XDS_CORE_V3_CONTEXT_PARAMS_PROTO_UPB_H__UPB_H_
#define XDS_CORE_V3_CONTEXT_PARAMS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/core/v3/context_params.upb_minitable.h"

#include "xds/annotations/v3/status.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_core_v3_ContextParams { upb_Message UPB_PRIVATE(base); } xds_core_v3_ContextParams;

UPB_INLINE xds_core_v3_ContextParams* xds_core_v3_ContextParams_new(upb_Arena* arena) {
  return (xds_core_v3_ContextParams*)_upb_Message_New(&xds__core__v3__ContextParams_msg_init, arena);
}
UPB_INLINE xds_core_v3_ContextParams* xds_core_v3_ContextParams_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_core_v3_ContextParams* ret = xds_core_v3_ContextParams_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__ContextParams_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_core_v3_ContextParams* xds_core_v3_ContextParams_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_core_v3_ContextParams* ret = xds_core_v3_ContextParams_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__ContextParams_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_core_v3_ContextParams_serialize(const xds_core_v3_ContextParams* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__ContextParams_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_core_v3_ContextParams_serialize_ex(const xds_core_v3_ContextParams* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__ContextParams_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_core_v3_ContextParams_clear_params(xds_core_v3_ContextParams* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE size_t xds_core_v3_ContextParams_params_size(const xds_core_v3_ContextParams* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  return map ? _upb_Map_Size(map) : 0;
}
UPB_INLINE bool xds_core_v3_ContextParams_params_get(const xds_core_v3_ContextParams* msg, upb_StringView key, upb_StringView* val) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams__ParamsEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Get(map, &key, 0, val, 0);
}
UPB_INLINE bool xds_core_v3_ContextParams_params_next(const xds_core_v3_ContextParams* msg, upb_StringView* key, upb_StringView* val,
                           size_t* iter) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams__ParamsEntry_msg_init);
  const upb_Map* map = upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  upb_MessageValue k;
  upb_MessageValue v;
  if (!upb_Map_Next(map, &k, &v, iter)) return false;
  memcpy(key, &k, sizeof(*key));
  memcpy(val, &v, sizeof(*val));
  return true;
}
UPB_INLINE const upb_Map* _xds_core_v3_ContextParams_params_upb_map(xds_core_v3_ContextParams* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams__ParamsEntry_msg_init);
  return upb_Message_GetMap(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_Map* _xds_core_v3_ContextParams_params_mutable_upb_map(xds_core_v3_ContextParams* msg, upb_Arena* a) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams__ParamsEntry_msg_init);
  return _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg), &field, 0, 0, a);
}

UPB_INLINE void xds_core_v3_ContextParams_params_clear(xds_core_v3_ContextParams* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return;
  _upb_Map_Clear(map);
}
UPB_INLINE bool xds_core_v3_ContextParams_params_set(xds_core_v3_ContextParams* msg, upb_StringView key, upb_StringView val, upb_Arena* a) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams__ParamsEntry_msg_init);
  upb_Map* map = _upb_Message_GetOrCreateMutableMap(UPB_UPCAST(msg),
                                                    &field, 0, 0, a);
  return _upb_Map_Insert(map, &key, 0, &val, 0, a) !=
         kUpb_MapInsertStatus_OutOfMemory;
}
UPB_INLINE bool xds_core_v3_ContextParams_params_delete(xds_core_v3_ContextParams* msg, upb_StringView key) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Map* map = (upb_Map*)upb_Message_GetMap(UPB_UPCAST(msg), &field);
  if (!map) return false;
  return _upb_Map_Delete(map, &key, 0, NULL);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
