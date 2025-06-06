
#ifndef ENVOY_ADMIN_V3_CERTS_PROTO_UPB_H__UPB_H_
#define ENVOY_ADMIN_V3_CERTS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/admin/v3/certs.upb_minitable.h"

#include "google/protobuf/timestamp.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_admin_v3_Certificates { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_Certificates;
typedef struct envoy_admin_v3_Certificate { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_Certificate;
typedef struct envoy_admin_v3_CertificateDetails { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_CertificateDetails;
typedef struct envoy_admin_v3_CertificateDetails_OcspDetails { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_CertificateDetails_OcspDetails;
typedef struct envoy_admin_v3_SubjectAlternateName { upb_Message UPB_PRIVATE(base); } envoy_admin_v3_SubjectAlternateName;
struct google_protobuf_Timestamp;

UPB_INLINE envoy_admin_v3_Certificates* envoy_admin_v3_Certificates_new(upb_Arena* arena) {
  return (envoy_admin_v3_Certificates*)_upb_Message_New(&envoy__admin__v3__Certificates_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_Certificates* envoy_admin_v3_Certificates_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_Certificates* ret = envoy_admin_v3_Certificates_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__Certificates_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_Certificates* envoy_admin_v3_Certificates_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_Certificates* ret = envoy_admin_v3_Certificates_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__Certificates_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_Certificates_serialize(const envoy_admin_v3_Certificates* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__Certificates_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_Certificates_serialize_ex(const envoy_admin_v3_Certificates* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__Certificates_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_Certificates_clear_certificates(envoy_admin_v3_Certificates* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_Certificate* const* envoy_admin_v3_Certificates_certificates(const envoy_admin_v3_Certificates* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__Certificate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_Certificate* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_Certificates_certificates_upb_array(const envoy_admin_v3_Certificates* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__Certificate_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_Certificates_certificates_mutable_upb_array(envoy_admin_v3_Certificates* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__Certificate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_admin_v3_Certificate** envoy_admin_v3_Certificates_mutable_certificates(envoy_admin_v3_Certificates* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__Certificate_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_Certificate**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_Certificate** envoy_admin_v3_Certificates_resize_certificates(envoy_admin_v3_Certificates* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_Certificate**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_Certificate* envoy_admin_v3_Certificates_add_certificates(envoy_admin_v3_Certificates* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__Certificate_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_Certificate* sub = (struct envoy_admin_v3_Certificate*)_upb_Message_New(&envoy__admin__v3__Certificate_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_Certificate* envoy_admin_v3_Certificate_new(upb_Arena* arena) {
  return (envoy_admin_v3_Certificate*)_upb_Message_New(&envoy__admin__v3__Certificate_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_Certificate* envoy_admin_v3_Certificate_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_Certificate* ret = envoy_admin_v3_Certificate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__Certificate_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_Certificate* envoy_admin_v3_Certificate_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_Certificate* ret = envoy_admin_v3_Certificate_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__Certificate_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_Certificate_serialize(const envoy_admin_v3_Certificate* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__Certificate_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_Certificate_serialize_ex(const envoy_admin_v3_Certificate* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__Certificate_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_Certificate_clear_ca_cert(envoy_admin_v3_Certificate* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_CertificateDetails* const* envoy_admin_v3_Certificate_ca_cert(const envoy_admin_v3_Certificate* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_CertificateDetails* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_Certificate_ca_cert_upb_array(const envoy_admin_v3_Certificate* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_Certificate_ca_cert_mutable_upb_array(envoy_admin_v3_Certificate* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_Certificate_clear_cert_chain(envoy_admin_v3_Certificate* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_CertificateDetails* const* envoy_admin_v3_Certificate_cert_chain(const envoy_admin_v3_Certificate* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_CertificateDetails* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_Certificate_cert_chain_upb_array(const envoy_admin_v3_Certificate* msg, size_t* size) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_Certificate_cert_chain_mutable_upb_array(envoy_admin_v3_Certificate* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE envoy_admin_v3_CertificateDetails** envoy_admin_v3_Certificate_mutable_ca_cert(envoy_admin_v3_Certificate* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_CertificateDetails**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_CertificateDetails** envoy_admin_v3_Certificate_resize_ca_cert(envoy_admin_v3_Certificate* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_CertificateDetails**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_CertificateDetails* envoy_admin_v3_Certificate_add_ca_cert(envoy_admin_v3_Certificate* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_CertificateDetails* sub = (struct envoy_admin_v3_CertificateDetails*)_upb_Message_New(&envoy__admin__v3__CertificateDetails_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE envoy_admin_v3_CertificateDetails** envoy_admin_v3_Certificate_mutable_cert_chain(envoy_admin_v3_Certificate* msg, size_t* size) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_CertificateDetails**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_CertificateDetails** envoy_admin_v3_Certificate_resize_cert_chain(envoy_admin_v3_Certificate* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_CertificateDetails**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_CertificateDetails* envoy_admin_v3_Certificate_add_cert_chain(envoy_admin_v3_Certificate* msg, upb_Arena* arena) {
  upb_MiniTableField field = {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_CertificateDetails* sub = (struct envoy_admin_v3_CertificateDetails*)_upb_Message_New(&envoy__admin__v3__CertificateDetails_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE envoy_admin_v3_CertificateDetails* envoy_admin_v3_CertificateDetails_new(upb_Arena* arena) {
  return (envoy_admin_v3_CertificateDetails*)_upb_Message_New(&envoy__admin__v3__CertificateDetails_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_CertificateDetails* envoy_admin_v3_CertificateDetails_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_CertificateDetails* ret = envoy_admin_v3_CertificateDetails_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__CertificateDetails_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_CertificateDetails* envoy_admin_v3_CertificateDetails_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_CertificateDetails* ret = envoy_admin_v3_CertificateDetails_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__CertificateDetails_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_CertificateDetails_serialize(const envoy_admin_v3_CertificateDetails* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__CertificateDetails_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_CertificateDetails_serialize_ex(const envoy_admin_v3_CertificateDetails* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__CertificateDetails_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_clear_path(envoy_admin_v3_CertificateDetails* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CertificateDetails_path(const envoy_admin_v3_CertificateDetails* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_clear_serial_number(envoy_admin_v3_CertificateDetails* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_CertificateDetails_serial_number(const envoy_admin_v3_CertificateDetails* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_clear_subject_alt_names(envoy_admin_v3_CertificateDetails* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_SubjectAlternateName* const* envoy_admin_v3_CertificateDetails_subject_alt_names(const envoy_admin_v3_CertificateDetails* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SubjectAlternateName_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const envoy_admin_v3_SubjectAlternateName* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _envoy_admin_v3_CertificateDetails_subject_alt_names_upb_array(const envoy_admin_v3_CertificateDetails* msg, size_t* size) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SubjectAlternateName_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _envoy_admin_v3_CertificateDetails_subject_alt_names_mutable_upb_array(envoy_admin_v3_CertificateDetails* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SubjectAlternateName_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_clear_days_until_expiration(envoy_admin_v3_CertificateDetails* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE uint64_t envoy_admin_v3_CertificateDetails_days_until_expiration(const envoy_admin_v3_CertificateDetails* msg) {
  uint64_t default_val = (uint64_t)0ull;
  uint64_t ret;
  const upb_MiniTableField field = {4, UPB_SIZE(48, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_clear_valid_from(envoy_admin_v3_CertificateDetails* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_CertificateDetails_valid_from(const envoy_admin_v3_CertificateDetails* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(16, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_CertificateDetails_has_valid_from(const envoy_admin_v3_CertificateDetails* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_clear_expiration_time(envoy_admin_v3_CertificateDetails* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 72), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_CertificateDetails_expiration_time(const envoy_admin_v3_CertificateDetails* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {6, UPB_SIZE(20, 72), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_CertificateDetails_has_expiration_time(const envoy_admin_v3_CertificateDetails* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 72), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_clear_ocsp_details(envoy_admin_v3_CertificateDetails* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 80), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const envoy_admin_v3_CertificateDetails_OcspDetails* envoy_admin_v3_CertificateDetails_ocsp_details(const envoy_admin_v3_CertificateDetails* msg) {
  const envoy_admin_v3_CertificateDetails_OcspDetails* default_val = NULL;
  const envoy_admin_v3_CertificateDetails_OcspDetails* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(24, 80), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails__OcspDetails_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_CertificateDetails_has_ocsp_details(const envoy_admin_v3_CertificateDetails* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 80), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_CertificateDetails_set_path(envoy_admin_v3_CertificateDetails *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_set_serial_number(envoy_admin_v3_CertificateDetails *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE envoy_admin_v3_SubjectAlternateName** envoy_admin_v3_CertificateDetails_mutable_subject_alt_names(envoy_admin_v3_CertificateDetails* msg, size_t* size) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SubjectAlternateName_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (envoy_admin_v3_SubjectAlternateName**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE envoy_admin_v3_SubjectAlternateName** envoy_admin_v3_CertificateDetails_resize_subject_alt_names(envoy_admin_v3_CertificateDetails* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_SubjectAlternateName**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct envoy_admin_v3_SubjectAlternateName* envoy_admin_v3_CertificateDetails_add_subject_alt_names(envoy_admin_v3_CertificateDetails* msg, upb_Arena* arena) {
  upb_MiniTableField field = {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__SubjectAlternateName_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct envoy_admin_v3_SubjectAlternateName* sub = (struct envoy_admin_v3_SubjectAlternateName*)_upb_Message_New(&envoy__admin__v3__SubjectAlternateName_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_set_days_until_expiration(envoy_admin_v3_CertificateDetails *msg, uint64_t value) {
  const upb_MiniTableField field = {4, UPB_SIZE(48, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_set_valid_from(envoy_admin_v3_CertificateDetails *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(16, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_CertificateDetails_mutable_valid_from(envoy_admin_v3_CertificateDetails* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_CertificateDetails_valid_from(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_CertificateDetails_set_valid_from(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_set_expiration_time(envoy_admin_v3_CertificateDetails *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {6, UPB_SIZE(20, 72), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_CertificateDetails_mutable_expiration_time(envoy_admin_v3_CertificateDetails* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_CertificateDetails_expiration_time(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_CertificateDetails_set_expiration_time(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_set_ocsp_details(envoy_admin_v3_CertificateDetails *msg, envoy_admin_v3_CertificateDetails_OcspDetails* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(24, 80), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__admin__v3__CertificateDetails__OcspDetails_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_admin_v3_CertificateDetails_OcspDetails* envoy_admin_v3_CertificateDetails_mutable_ocsp_details(envoy_admin_v3_CertificateDetails* msg, upb_Arena* arena) {
  struct envoy_admin_v3_CertificateDetails_OcspDetails* sub = (struct envoy_admin_v3_CertificateDetails_OcspDetails*)envoy_admin_v3_CertificateDetails_ocsp_details(msg);
  if (sub == NULL) {
    sub = (struct envoy_admin_v3_CertificateDetails_OcspDetails*)_upb_Message_New(&envoy__admin__v3__CertificateDetails__OcspDetails_msg_init, arena);
    if (sub) envoy_admin_v3_CertificateDetails_set_ocsp_details(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_CertificateDetails_OcspDetails* envoy_admin_v3_CertificateDetails_OcspDetails_new(upb_Arena* arena) {
  return (envoy_admin_v3_CertificateDetails_OcspDetails*)_upb_Message_New(&envoy__admin__v3__CertificateDetails__OcspDetails_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_CertificateDetails_OcspDetails* envoy_admin_v3_CertificateDetails_OcspDetails_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_CertificateDetails_OcspDetails* ret = envoy_admin_v3_CertificateDetails_OcspDetails_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__CertificateDetails__OcspDetails_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_CertificateDetails_OcspDetails* envoy_admin_v3_CertificateDetails_OcspDetails_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_CertificateDetails_OcspDetails* ret = envoy_admin_v3_CertificateDetails_OcspDetails_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__CertificateDetails__OcspDetails_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_CertificateDetails_OcspDetails_serialize(const envoy_admin_v3_CertificateDetails_OcspDetails* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__CertificateDetails__OcspDetails_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_CertificateDetails_OcspDetails_serialize_ex(const envoy_admin_v3_CertificateDetails_OcspDetails* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__CertificateDetails__OcspDetails_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_OcspDetails_clear_valid_from(envoy_admin_v3_CertificateDetails_OcspDetails* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_CertificateDetails_OcspDetails_valid_from(const envoy_admin_v3_CertificateDetails_OcspDetails* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_CertificateDetails_OcspDetails_has_valid_from(const envoy_admin_v3_CertificateDetails_OcspDetails* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_OcspDetails_clear_expiration(envoy_admin_v3_CertificateDetails_OcspDetails* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct google_protobuf_Timestamp* envoy_admin_v3_CertificateDetails_OcspDetails_expiration(const envoy_admin_v3_CertificateDetails_OcspDetails* msg) {
  const struct google_protobuf_Timestamp* default_val = NULL;
  const struct google_protobuf_Timestamp* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_CertificateDetails_OcspDetails_has_expiration(const envoy_admin_v3_CertificateDetails_OcspDetails* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_CertificateDetails_OcspDetails_set_valid_from(envoy_admin_v3_CertificateDetails_OcspDetails *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_CertificateDetails_OcspDetails_mutable_valid_from(envoy_admin_v3_CertificateDetails_OcspDetails* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_CertificateDetails_OcspDetails_valid_from(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_CertificateDetails_OcspDetails_set_valid_from(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_admin_v3_CertificateDetails_OcspDetails_set_expiration(envoy_admin_v3_CertificateDetails_OcspDetails *msg, struct google_protobuf_Timestamp* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&google__protobuf__Timestamp_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct google_protobuf_Timestamp* envoy_admin_v3_CertificateDetails_OcspDetails_mutable_expiration(envoy_admin_v3_CertificateDetails_OcspDetails* msg, upb_Arena* arena) {
  struct google_protobuf_Timestamp* sub = (struct google_protobuf_Timestamp*)envoy_admin_v3_CertificateDetails_OcspDetails_expiration(msg);
  if (sub == NULL) {
    sub = (struct google_protobuf_Timestamp*)_upb_Message_New(&google__protobuf__Timestamp_msg_init, arena);
    if (sub) envoy_admin_v3_CertificateDetails_OcspDetails_set_expiration(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_admin_v3_SubjectAlternateName* envoy_admin_v3_SubjectAlternateName_new(upb_Arena* arena) {
  return (envoy_admin_v3_SubjectAlternateName*)_upb_Message_New(&envoy__admin__v3__SubjectAlternateName_msg_init, arena);
}
UPB_INLINE envoy_admin_v3_SubjectAlternateName* envoy_admin_v3_SubjectAlternateName_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_admin_v3_SubjectAlternateName* ret = envoy_admin_v3_SubjectAlternateName_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__SubjectAlternateName_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_admin_v3_SubjectAlternateName* envoy_admin_v3_SubjectAlternateName_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_admin_v3_SubjectAlternateName* ret = envoy_admin_v3_SubjectAlternateName_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__admin__v3__SubjectAlternateName_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_admin_v3_SubjectAlternateName_serialize(const envoy_admin_v3_SubjectAlternateName* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__SubjectAlternateName_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_admin_v3_SubjectAlternateName_serialize_ex(const envoy_admin_v3_SubjectAlternateName* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__admin__v3__SubjectAlternateName_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  envoy_admin_v3_SubjectAlternateName_name_dns = 1,
  envoy_admin_v3_SubjectAlternateName_name_uri = 2,
  envoy_admin_v3_SubjectAlternateName_name_ip_address = 3,
  envoy_admin_v3_SubjectAlternateName_name_NOT_SET = 0
} envoy_admin_v3_SubjectAlternateName_name_oneofcases;
UPB_INLINE envoy_admin_v3_SubjectAlternateName_name_oneofcases envoy_admin_v3_SubjectAlternateName_name_case(const envoy_admin_v3_SubjectAlternateName* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return (envoy_admin_v3_SubjectAlternateName_name_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_SubjectAlternateName_clear_name(envoy_admin_v3_SubjectAlternateName* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &envoy__admin__v3__SubjectAlternateName_msg_init, &field);
}
UPB_INLINE void envoy_admin_v3_SubjectAlternateName_clear_dns(envoy_admin_v3_SubjectAlternateName* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_SubjectAlternateName_dns(const envoy_admin_v3_SubjectAlternateName* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_SubjectAlternateName_has_dns(const envoy_admin_v3_SubjectAlternateName* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_SubjectAlternateName_clear_uri(envoy_admin_v3_SubjectAlternateName* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_SubjectAlternateName_uri(const envoy_admin_v3_SubjectAlternateName* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_SubjectAlternateName_has_uri(const envoy_admin_v3_SubjectAlternateName* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_admin_v3_SubjectAlternateName_clear_ip_address(envoy_admin_v3_SubjectAlternateName* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_admin_v3_SubjectAlternateName_ip_address(const envoy_admin_v3_SubjectAlternateName* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_admin_v3_SubjectAlternateName_has_ip_address(const envoy_admin_v3_SubjectAlternateName* msg) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_admin_v3_SubjectAlternateName_set_dns(envoy_admin_v3_SubjectAlternateName *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_SubjectAlternateName_set_uri(envoy_admin_v3_SubjectAlternateName *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void envoy_admin_v3_SubjectAlternateName_set_ip_address(envoy_admin_v3_SubjectAlternateName *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
