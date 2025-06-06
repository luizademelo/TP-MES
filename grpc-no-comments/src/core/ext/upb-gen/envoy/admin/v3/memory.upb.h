
#ifndef ENVOY_ADMIN_V3_MEMORY_PROTO_UPB_H__UPB_H_
#define ENVOY_ADMIN_V3_MEMORY_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/admin/v3/memory.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_admin_v3_Memory { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_Memory;

UPB_INLINE envoy_admin_v3_Memory* envoy_admin_v3_Memory_new(upb_Arena* arena) {
  return (envoy_admin_v3_Memory*)_upb_Message_New(&envoy__admin__v3__Memory_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_Memory* envoy_admin_v3_Memory_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_Memory* ret = envoy_admin_v3_Memory_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__Memory_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_Memory* envoy_admin_v3_Memory_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_Memory* ret = envoy_admin_v3_Memory_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__Memory_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_Memory_serialize(const envoy_admin_v3_Memory* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__Memory_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_Memory_serialize_ex(const envoy_admin_v3_Memory* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__Memory_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_Memory_clear_allocated(envoy_admin_v3_Memory* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_Memory_allocated(const envoy_admin_v3_Memory* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_Memory_clear_heap_size(envoy_admin_v3_Memory* msg) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_Memory_heap_size(const envoy_admin_v3_Memory* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_Memory_clear_pageheap_unmapped(envoy_admin_v3_Memory* msg) {
  const upb_MiniTableField field = {3, 24, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_Memory_pageheap_unmapped(const envoy_admin_v3_Memory* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {3, 24, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_Memory_clear_pageheap_free(envoy_admin_v3_Memory* msg) {
  const upb_MiniTableField field = {4, 32, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_Memory_pageheap_free(const envoy_admin_v3_Memory* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {4, 32, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_Memory_clear_total_thread_cache(envoy_admin_v3_Memory* msg) {
  const upb_MiniTableField field = {5, 40, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_Memory_total_thread_cache(const envoy_admin_v3_Memory* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {5, 40, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_Memory_clear_total_physical_bytes(envoy_admin_v3_Memory* msg) {
  const upb_MiniTableField field = {6, 48, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_Memory_total_physical_bytes(const envoy_admin_v3_Memory* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {6, 48, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_admin_v3_Memory_set_allocated(envoy_admin_v3_Memory *msg, uint64_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_Memory_set_heap_size(envoy_admin_v3_Memory *msg, uint64_t value) {
  const upb_MiniTableField field = {2, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_Memory_set_pageheap_unmapped(envoy_admin_v3_Memory *msg, uint64_t value) {
  const upb_MiniTableField field = {3, 24, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_Memory_set_pageheap_free(envoy_admin_v3_Memory *msg, uint64_t value) {
  const upb_MiniTableField field = {4, 32, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_Memory_set_total_thread_cache(envoy_admin_v3_Memory *msg, uint64_t value) {
  const upb_MiniTableField field = {5, 40, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_Memory_set_total_physical_bytes(envoy_admin_v3_Memory *msg, uint64_t value) {
  const upb_MiniTableField field = {6, 48, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
