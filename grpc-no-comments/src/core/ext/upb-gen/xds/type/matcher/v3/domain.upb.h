
#ifndef XDS_TYPE_MATCHER_V3_DOMAIN_PROTO_UPB_H__UPB_H_
#define XDS_TYPE_MATCHER_V3_DOMAIN_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "xds/type/matcher/v3/domain.upb_minitable.h"

#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/type/matcher/v3/matcher.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xds_type_matcher_v3_ServerNameMatcher { upb_Message UPB_PRIVATE(base); } xds_type_matcher_v3_ServerNameMatcher;
typedef struct xds_type_matcher_v3_ServerNameMatcher_DomainMatcher { upb_Message UPB_PRIVATE(base); } xds_type_matcher_v3_ServerNameMatcher_DomainMatcher;
struct xds_type_matcher_v3_Matcher_OnMatch;

UPB_INLINE xds_type_matcher_v3_ServerNameMatcher* xds_type_matcher_v3_ServerNameMatcher_new(upb_Arena* arena) {
  return (xds_type_matcher_v3_ServerNameMatcher*)_upb_Message_New(&xds__type__matcher__v3__ServerNameMatcher_msg_init, arena);
}
UPB_INLINE xds_type_matcher_v3_ServerNameMatcher* xds_type_matcher_v3_ServerNameMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_matcher_v3_ServerNameMatcher* ret = xds_type_matcher_v3_ServerNameMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__ServerNameMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_matcher_v3_ServerNameMatcher* xds_type_matcher_v3_ServerNameMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_matcher_v3_ServerNameMatcher* ret = xds_type_matcher_v3_ServerNameMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__ServerNameMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_matcher_v3_ServerNameMatcher_serialize(const xds_type_matcher_v3_ServerNameMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__ServerNameMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_matcher_v3_ServerNameMatcher_serialize_ex(const xds_type_matcher_v3_ServerNameMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__ServerNameMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_matcher_v3_ServerNameMatcher_clear_domain_matchers(xds_type_matcher_v3_ServerNameMatcher* msg) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* const* xds_type_matcher_v3_ServerNameMatcher_domain_matchers(const xds_type_matcher_v3_ServerNameMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (const xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _xds_type_matcher_v3_ServerNameMatcher_domain_matchers_upb_array(const xds_type_matcher_v3_ServerNameMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init);
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _xds_type_matcher_v3_ServerNameMatcher_domain_matchers_mutable_upb_array(xds_type_matcher_v3_ServerNameMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}

UPB_INLINE xds_type_matcher_v3_ServerNameMatcher_DomainMatcher** xds_type_matcher_v3_ServerNameMatcher_mutable_domain_matchers(xds_type_matcher_v3_ServerNameMatcher* msg, size_t* size) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init);
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (xds_type_matcher_v3_ServerNameMatcher_DomainMatcher**)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE xds_type_matcher_v3_ServerNameMatcher_DomainMatcher** xds_type_matcher_v3_ServerNameMatcher_resize_domain_matchers(xds_type_matcher_v3_ServerNameMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (xds_type_matcher_v3_ServerNameMatcher_DomainMatcher**)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE struct xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* xds_type_matcher_v3_ServerNameMatcher_add_domain_matchers(xds_type_matcher_v3_ServerNameMatcher* msg, upb_Arena* arena) {
  upb_MiniTableField field = {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(
      UPB_UPCAST(msg), &field, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
                  arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return NULL;
  }
  struct xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* sub = (struct xds_type_matcher_v3_ServerNameMatcher_DomainMatcher*)_upb_Message_New(&xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init, arena);
  if (!arr || !sub) return NULL;
  UPB_PRIVATE(_upb_Array_Set)
  (arr, arr->UPB_PRIVATE(size) - 1, &sub, sizeof(sub));
  return sub;
}

UPB_INLINE xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_new(upb_Arena* arena) {
  return (xds_type_matcher_v3_ServerNameMatcher_DomainMatcher*)_upb_Message_New(&xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init, arena);
}
UPB_INLINE xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_parse(const char* buf, size_t size, upb_Arena* arena) {
  xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* ret = xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* ret = xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_serialize(const xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_serialize_ex(const xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &xds__type__matcher__v3__ServerNameMatcher__DomainMatcher_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_clear_domains(xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView const* xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_domains(const xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView const*)upb_Array_DataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE const upb_Array* _xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_domains_upb_array(const xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg, size_t* size) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  const upb_Array* arr = upb_Message_GetArray(UPB_UPCAST(msg), &field);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE upb_Array* _xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_domains_mutable_upb_array(xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg, size_t* size, upb_Arena* arena) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(UPB_UPCAST(msg),
                                                       &field, arena);
  if (size) {
    *size = arr ? arr->UPB_PRIVATE(size) : 0;
  }
  return arr;
}
UPB_INLINE void xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_clear_on_match(xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct xds_type_matcher_v3_Matcher_OnMatch* xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_on_match(const xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg) {
  const struct xds_type_matcher_v3_Matcher_OnMatch* default_val = NULL;
  const struct xds_type_matcher_v3_Matcher_OnMatch* ret;
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher__OnMatch_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_has_on_match(const xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE upb_StringView* xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_mutable_domains(xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg, size_t* size) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Array* arr = upb_Message_GetMutableArray(UPB_UPCAST(msg), &field);
  if (arr) {
    if (size) *size = arr->UPB_PRIVATE(size);
    return (upb_StringView*)upb_Array_MutableDataPtr(arr);
  } else {
    if (size) *size = 0;
    return NULL;
  }
}
UPB_INLINE upb_StringView* xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_resize_domains(xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg, size_t size, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return (upb_StringView*)upb_Message_ResizeArrayUninitialized(UPB_UPCAST(msg),
                                                   &field, size, arena);
}
UPB_INLINE bool xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_add_domains(xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg, upb_StringView val, upb_Arena* arena) {
  upb_MiniTableField field = {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
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
UPB_INLINE void xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_set_on_match(xds_type_matcher_v3_ServerNameMatcher_DomainMatcher *msg, struct xds_type_matcher_v3_Matcher_OnMatch* value) {
  const upb_MiniTableField field = {2, UPB_SIZE(16, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&xds__type__matcher__v3__Matcher__OnMatch_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct xds_type_matcher_v3_Matcher_OnMatch* xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_mutable_on_match(xds_type_matcher_v3_ServerNameMatcher_DomainMatcher* msg, upb_Arena* arena) {
  struct xds_type_matcher_v3_Matcher_OnMatch* sub = (struct xds_type_matcher_v3_Matcher_OnMatch*)xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_on_match(msg);
  if (sub == NULL) {
    sub = (struct xds_type_matcher_v3_Matcher_OnMatch*)_upb_Message_New(&xds__type__matcher__v3__Matcher__OnMatch_msg_init, arena);
    if (sub) xds_type_matcher_v3_ServerNameMatcher_DomainMatcher_set_on_match(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
