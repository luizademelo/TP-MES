
#ifndef XDS_CORE_V3_RESOURCE_LOCATOR_PROTO_UPB_H__UPB_H_
#define XDS_CORE_V3_RESOURCE_LOCATOR_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/core/v3/resource_locator.upb_minitable.h"

#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/core/v3/context_params.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_core_v3_ResourceLocator { upb_Message UPB_PRIVATE(base); } xds_core_v3_ResourceLocator;
typedef struct xds_core_v3_ResourceLocator_Directive { upb_Message UPB_PRIVATE(base); } xds_core_v3_ResourceLocator_Directive;
struct xds_core_v3_ContextParams;

typedef enum {
  xds_core_v3_ResourceLocator_XDSTP = 0,
  xds_core_v3_ResourceLocator_HTTP = 1,
  xds_core_v3_ResourceLocator_FILE = 2
} xds_core_v3_ResourceLocator_Scheme;

UPB_INLINE xds_core_v3_ResourceLocator* xds_core_v3_ResourceLocator_new(upb_Arena* arena) {
  return (xds_core_v3_ResourceLocator*)_upb_Message_New(&xds__core__v3__ResourceLocator_msg_init, arena);
}
UPB_INLINE xds_core_v3_ResourceLocator* xds_core_v3_ResourceLocator_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_core_v3_ResourceLocator* ret = xds_core_v3_ResourceLocator_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__ResourceLocator_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_core_v3_ResourceLocator* xds_core_v3_ResourceLocator_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_core_v3_ResourceLocator* ret = xds_core_v3_ResourceLocator_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__ResourceLocator_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_core_v3_ResourceLocator_serialize(const xds_core_v3_ResourceLocator* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__ResourceLocator_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_core_v3_ResourceLocator_serialize_ex(const xds_core_v3_ResourceLocator* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__ResourceLocator_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  xds_core_v3_ResourceLocator_context_param_specifier_exact_context = 5,
  xds_core_v3_ResourceLocator_context_param_specifier_NOT_SET = 0
} xds_core_v3_ResourceLocator_context_param_specifier_oneofcases;
UPB_INLINE xds_core_v3_ResourceLocator_context_param_specifier_oneofcases xds_core_v3_ResourceLocator_context_param_specifier_case(const xds_core_v3_ResourceLocator* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 72), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (xds_core_v3_ResourceLocator_context_param_specifier_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_core_v3_ResourceLocator_clear_context_param_specifier(xds_core_v3_ResourceLocator* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 72), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &xds__core__v3__ResourceLocator_msg_init, &field);
}
UPB_INLINE void xds_core_v3_ResourceLocator_clear_scheme(xds_core_v3_ResourceLocator* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t xds_core_v3_ResourceLocator_scheme(const xds_core_v3_ResourceLocator* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_core_v3_ResourceLocator_clear_id(xds_core_v3_ResourceLocator* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_core_v3_ResourceLocator_id(const xds_core_v3_ResourceLocator* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_core_v3_ResourceLocator_clear_authority(xds_core_v3_ResourceLocator* msg) {
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_core_v3_ResourceLocator_authority(const xds_core_v3_ResourceLocator* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_core_v3_ResourceLocator_clear_resource_type(xds_core_v3_ResourceLocator* msg) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_core_v3_ResourceLocator_resource_type(const xds_core_v3_ResourceLocator* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {4, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE void xds_core_v3_ResourceLocator_clear_exact_context(xds_core_v3_ResourceLocator* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 72), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_core_v3_ContextParams* xds_core_v3_ResourceLocator_exact_context(const xds_core_v3_ResourceLocator* msg) {
  const struct xds_core_v3_ContextParams* default_val = NULL;
  const struct xds_core_v3_ContextParams* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(20, 72), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_core_v3_ResourceLocator_has_exact_context(const xds_core_v3_ResourceLocator* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 72), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_core_v3_ResourceLocator_clear_directives(xds_core_v3_ResourceLocator* msg) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const xds_core_v3_ResourceLocator_Directive* const* xds_core_v3_ResourceLocator_directives(const xds_core_v3_ResourceLocator* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ResourceLocator__Directive_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const xds_core_v3_ResourceLocator_Directive* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _xds_core_v3_ResourceLocator_directives_upb_array(const xds_core_v3_ResourceLocator* msg, size_t* size) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ResourceLocator__Directive_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _xds_core_v3_ResourceLocator_directives_mutable_upb_array(xds_core_v3_ResourceLocator* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {6, UPB_SIZE(12, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ResourceLocator__Directive_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE void xds_core_v3_ResourceLocator_set_scheme(xds_core_v3_ResourceLocator *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_core_v3_ResourceLocator_set_id(xds_core_v3_ResourceLocator *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_core_v3_ResourceLocator_set_authority(xds_core_v3_ResourceLocator *msg, upb_StringView value) {
  const upb_MiniTableField field = {3, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_core_v3_ResourceLocator_set_resource_type(xds_core_v3_ResourceLocator *msg, upb_StringView value) {
  const upb_MiniTableField field = {4, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE void xds_core_v3_ResourceLocator_set_exact_context(xds_core_v3_ResourceLocator *msg, struct xds_core_v3_ContextParams* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(20, 72), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ContextParams_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_core_v3_ContextParams* xds_core_v3_ResourceLocator_mutable_exact_context(xds_core_v3_ResourceLocator* msg, upb_Arena* arena) {
  struct xds_core_v3_ContextParams* sub = (struct xds_core_v3_ContextParams*)xds_core_v3_ResourceLocator_exact_context(msg);
  if (sub == NULL) {
    sub = (struct xds_core_v3_ContextParams*)_upb_Message_New(&xds__core__v3__ContextParams_msg_init, arena);
    if (sub) xds_core_v3_ResourceLocator_set_exact_context(msg, sub);
  }
  return sub;
}
UPB_INLINE xds_core_v3_ResourceLocator_Directive** xds_core_v3_ResourceLocator_mutable_directives(xds_core_v3_ResourceLocator* msg, size_t* size) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ResourceLocator__Directive_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (xds_core_v3_ResourceLocator_Directive**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE xds_core_v3_ResourceLocator_Directive** xds_core_v3_ResourceLocator_resize_directives(xds_core_v3_ResourceLocator* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (xds_core_v3_ResourceLocator_Directive**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct xds_core_v3_ResourceLocator_Directive* xds_core_v3_ResourceLocator_add_directives(xds_core_v3_ResourceLocator* msg, upb_Arena* arena) {
  upb_MiniTableField field = {6, UPB_SIZE(12, 64), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ResourceLocator__Directive_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct xds_core_v3_ResourceLocator_Directive* sub = (struct xds_core_v3_ResourceLocator_Directive*)_upb_Message_New(&xds__core__v3__ResourceLocator__Directive_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE xds_core_v3_ResourceLocator_Directive* xds_core_v3_ResourceLocator_Directive_new(upb_Arena* arena) {
  return (xds_core_v3_ResourceLocator_Directive*)_upb_Message_New(&xds__core__v3__ResourceLocator__Directive_msg_init, arena);
}
UPB_INLINE xds_core_v3_ResourceLocator_Directive* xds_core_v3_ResourceLocator_Directive_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_core_v3_ResourceLocator_Directive* ret = xds_core_v3_ResourceLocator_Directive_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__ResourceLocator__Directive_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_core_v3_ResourceLocator_Directive* xds_core_v3_ResourceLocator_Directive_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_core_v3_ResourceLocator_Directive* ret = xds_core_v3_ResourceLocator_Directive_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__core__v3__ResourceLocator__Directive_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_core_v3_ResourceLocator_Directive_serialize(const xds_core_v3_ResourceLocator_Directive* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__ResourceLocator__Directive_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_core_v3_ResourceLocator_Directive_serialize_ex(const xds_core_v3_ResourceLocator_Directive* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__core__v3__ResourceLocator__Directive_msg_init, options, arena, &ptr, len);
  return ptr;
}
typedef enum {
  xds_core_v3_ResourceLocator_Directive_directive_alt = 1,
  xds_core_v3_ResourceLocator_Directive_directive_entry = 2,
  xds_core_v3_ResourceLocator_Directive_directive_NOT_SET = 0
} xds_core_v3_ResourceLocator_Directive_directive_oneofcases;
UPB_INLINE xds_core_v3_ResourceLocator_Directive_directive_oneofcases xds_core_v3_ResourceLocator_Directive_directive_case(const xds_core_v3_ResourceLocator_Directive* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (xds_core_v3_ResourceLocator_Directive_directive_oneofcases)upb_Message_WhichOneofFieldNumber(
      UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_core_v3_ResourceLocator_Directive_clear_directive(xds_core_v3_ResourceLocator_Directive* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearOneof(UPB_UPCAST(msg), &xds__core__v3__ResourceLocator__Directive_msg_init, &field);
}
UPB_INLINE void xds_core_v3_ResourceLocator_Directive_clear_alt(xds_core_v3_ResourceLocator_Directive* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const xds_core_v3_ResourceLocator* xds_core_v3_ResourceLocator_Directive_alt(const xds_core_v3_ResourceLocator_Directive* msg) {
  const xds_core_v3_ResourceLocator* default_val = NULL;
  const xds_core_v3_ResourceLocator* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ResourceLocator_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_core_v3_ResourceLocator_Directive_has_alt(const xds_core_v3_ResourceLocator_Directive* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void xds_core_v3_ResourceLocator_Directive_clear_entry(xds_core_v3_ResourceLocator_Directive* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView xds_core_v3_ResourceLocator_Directive_entry(const xds_core_v3_ResourceLocator_Directive* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_core_v3_ResourceLocator_Directive_has_entry(const xds_core_v3_ResourceLocator_Directive* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void xds_core_v3_ResourceLocator_Directive_set_alt(xds_core_v3_ResourceLocator_Directive *msg, xds_core_v3_ResourceLocator* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__core__v3__ResourceLocator_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_core_v3_ResourceLocator* xds_core_v3_ResourceLocator_Directive_mutable_alt(xds_core_v3_ResourceLocator_Directive* msg, upb_Arena* arena) {
  struct xds_core_v3_ResourceLocator* sub = (struct xds_core_v3_ResourceLocator*)xds_core_v3_ResourceLocator_Directive_alt(msg);
  if (sub == NULL) {
    sub = (struct xds_core_v3_ResourceLocator*)_upb_Message_New(&xds__core__v3__ResourceLocator_msg_init, arena);
    if (sub) xds_core_v3_ResourceLocator_Directive_set_alt(msg, sub);
  }
  return sub;
}
UPB_INLINE void xds_core_v3_ResourceLocator_Directive_set_entry(xds_core_v3_ResourceLocator_Directive *msg, upb_StringView value) {
  const upb_MiniTableField field = {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
