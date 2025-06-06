
#ifndef ENVOY_TYPE_MATCHER_V3_HTTP_INPUTS_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_MATCHER_V3_HTTP_INPUTS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/matcher/v3/http_inputs.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_matcher_v3_HttpRequestHeaderMatchInput { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_HttpRequestHeaderMatchInput;
typedef struct envoy_type_matcher_v3_HttpRequestTrailerMatchInput { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_HttpRequestTrailerMatchInput;
typedef struct envoy_type_matcher_v3_HttpResponseHeaderMatchInput { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_HttpResponseHeaderMatchInput;
typedef struct envoy_type_matcher_v3_HttpResponseTrailerMatchInput { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_HttpResponseTrailerMatchInput;
typedef struct envoy_type_matcher_v3_HttpRequestQueryParamMatchInput { upb_Message UPB_PRIVATE(base); } envoy_type_matcher_v3_HttpRequestQueryParamMatchInput;

UPB_INLINE envoy_type_matcher_v3_HttpRequestHeaderMatchInput* envoy_type_matcher_v3_HttpRequestHeaderMatchInput_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_HttpRequestHeaderMatchInput*)_upb_Message_New(&envoy__type__matcher__v3__HttpRequestHeaderMatchInput_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_HttpRequestHeaderMatchInput* envoy_type_matcher_v3_HttpRequestHeaderMatchInput_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_HttpRequestHeaderMatchInput* ret = envoy_type_matcher_v3_HttpRequestHeaderMatchInput_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__HttpRequestHeaderMatchInput_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_HttpRequestHeaderMatchInput* envoy_type_matcher_v3_HttpRequestHeaderMatchInput_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_HttpRequestHeaderMatchInput* ret = envoy_type_matcher_v3_HttpRequestHeaderMatchInput_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__HttpRequestHeaderMatchInput_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_HttpRequestHeaderMatchInput_serialize(const envoy_type_matcher_v3_HttpRequestHeaderMatchInput* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__HttpRequestHeaderMatchInput_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_HttpRequestHeaderMatchInput_serialize_ex(const envoy_type_matcher_v3_HttpRequestHeaderMatchInput* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__HttpRequestHeaderMatchInput_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_matcher_v3_HttpRequestHeaderMatchInput_clear_header_name(envoy_type_matcher_v3_HttpRequestHeaderMatchInput* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_matcher_v3_HttpRequestHeaderMatchInput_header_name(const envoy_type_matcher_v3_HttpRequestHeaderMatchInput* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_type_matcher_v3_HttpRequestHeaderMatchInput_set_header_name(envoy_type_matcher_v3_HttpRequestHeaderMatchInput *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_type_matcher_v3_HttpRequestTrailerMatchInput* envoy_type_matcher_v3_HttpRequestTrailerMatchInput_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_HttpRequestTrailerMatchInput*)_upb_Message_New(&envoy__type__matcher__v3__HttpRequestTrailerMatchInput_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_HttpRequestTrailerMatchInput* envoy_type_matcher_v3_HttpRequestTrailerMatchInput_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_HttpRequestTrailerMatchInput* ret = envoy_type_matcher_v3_HttpRequestTrailerMatchInput_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__HttpRequestTrailerMatchInput_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_HttpRequestTrailerMatchInput* envoy_type_matcher_v3_HttpRequestTrailerMatchInput_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_HttpRequestTrailerMatchInput* ret = envoy_type_matcher_v3_HttpRequestTrailerMatchInput_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__HttpRequestTrailerMatchInput_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_HttpRequestTrailerMatchInput_serialize(const envoy_type_matcher_v3_HttpRequestTrailerMatchInput* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__HttpRequestTrailerMatchInput_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_HttpRequestTrailerMatchInput_serialize_ex(const envoy_type_matcher_v3_HttpRequestTrailerMatchInput* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__HttpRequestTrailerMatchInput_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_matcher_v3_HttpRequestTrailerMatchInput_clear_header_name(envoy_type_matcher_v3_HttpRequestTrailerMatchInput* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_matcher_v3_HttpRequestTrailerMatchInput_header_name(const envoy_type_matcher_v3_HttpRequestTrailerMatchInput* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_type_matcher_v3_HttpRequestTrailerMatchInput_set_header_name(envoy_type_matcher_v3_HttpRequestTrailerMatchInput *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_type_matcher_v3_HttpResponseHeaderMatchInput* envoy_type_matcher_v3_HttpResponseHeaderMatchInput_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_HttpResponseHeaderMatchInput*)_upb_Message_New(&envoy__type__matcher__v3__HttpResponseHeaderMatchInput_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_HttpResponseHeaderMatchInput* envoy_type_matcher_v3_HttpResponseHeaderMatchInput_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_HttpResponseHeaderMatchInput* ret = envoy_type_matcher_v3_HttpResponseHeaderMatchInput_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__HttpResponseHeaderMatchInput_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_HttpResponseHeaderMatchInput* envoy_type_matcher_v3_HttpResponseHeaderMatchInput_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_HttpResponseHeaderMatchInput* ret = envoy_type_matcher_v3_HttpResponseHeaderMatchInput_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__HttpResponseHeaderMatchInput_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_HttpResponseHeaderMatchInput_serialize(const envoy_type_matcher_v3_HttpResponseHeaderMatchInput* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__HttpResponseHeaderMatchInput_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_HttpResponseHeaderMatchInput_serialize_ex(const envoy_type_matcher_v3_HttpResponseHeaderMatchInput* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__HttpResponseHeaderMatchInput_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_matcher_v3_HttpResponseHeaderMatchInput_clear_header_name(envoy_type_matcher_v3_HttpResponseHeaderMatchInput* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_matcher_v3_HttpResponseHeaderMatchInput_header_name(const envoy_type_matcher_v3_HttpResponseHeaderMatchInput* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_type_matcher_v3_HttpResponseHeaderMatchInput_set_header_name(envoy_type_matcher_v3_HttpResponseHeaderMatchInput *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_type_matcher_v3_HttpResponseTrailerMatchInput* envoy_type_matcher_v3_HttpResponseTrailerMatchInput_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_HttpResponseTrailerMatchInput*)_upb_Message_New(&envoy__type__matcher__v3__HttpResponseTrailerMatchInput_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_HttpResponseTrailerMatchInput* envoy_type_matcher_v3_HttpResponseTrailerMatchInput_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_HttpResponseTrailerMatchInput* ret = envoy_type_matcher_v3_HttpResponseTrailerMatchInput_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__HttpResponseTrailerMatchInput_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_HttpResponseTrailerMatchInput* envoy_type_matcher_v3_HttpResponseTrailerMatchInput_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_HttpResponseTrailerMatchInput* ret = envoy_type_matcher_v3_HttpResponseTrailerMatchInput_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__HttpResponseTrailerMatchInput_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_HttpResponseTrailerMatchInput_serialize(const envoy_type_matcher_v3_HttpResponseTrailerMatchInput* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__HttpResponseTrailerMatchInput_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_HttpResponseTrailerMatchInput_serialize_ex(const envoy_type_matcher_v3_HttpResponseTrailerMatchInput* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__HttpResponseTrailerMatchInput_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_matcher_v3_HttpResponseTrailerMatchInput_clear_header_name(envoy_type_matcher_v3_HttpResponseTrailerMatchInput* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_matcher_v3_HttpResponseTrailerMatchInput_header_name(const envoy_type_matcher_v3_HttpResponseTrailerMatchInput* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_type_matcher_v3_HttpResponseTrailerMatchInput_set_header_name(envoy_type_matcher_v3_HttpResponseTrailerMatchInput *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

UPB_INLINE envoy_type_matcher_v3_HttpRequestQueryParamMatchInput* envoy_type_matcher_v3_HttpRequestQueryParamMatchInput_new(upb_Arena* arena) {
  return (envoy_type_matcher_v3_HttpRequestQueryParamMatchInput*)_upb_Message_New(&envoy__type__matcher__v3__HttpRequestQueryParamMatchInput_msg_init, arena);
}
UPB_INLINE envoy_type_matcher_v3_HttpRequestQueryParamMatchInput* envoy_type_matcher_v3_HttpRequestQueryParamMatchInput_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_matcher_v3_HttpRequestQueryParamMatchInput* ret = envoy_type_matcher_v3_HttpRequestQueryParamMatchInput_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__HttpRequestQueryParamMatchInput_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_matcher_v3_HttpRequestQueryParamMatchInput* envoy_type_matcher_v3_HttpRequestQueryParamMatchInput_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_matcher_v3_HttpRequestQueryParamMatchInput* ret = envoy_type_matcher_v3_HttpRequestQueryParamMatchInput_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__matcher__v3__HttpRequestQueryParamMatchInput_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_matcher_v3_HttpRequestQueryParamMatchInput_serialize(const envoy_type_matcher_v3_HttpRequestQueryParamMatchInput* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__HttpRequestQueryParamMatchInput_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_matcher_v3_HttpRequestQueryParamMatchInput_serialize_ex(const envoy_type_matcher_v3_HttpRequestQueryParamMatchInput* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__matcher__v3__HttpRequestQueryParamMatchInput_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_matcher_v3_HttpRequestQueryParamMatchInput_clear_query_param(envoy_type_matcher_v3_HttpRequestQueryParamMatchInput* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE upb_StringView envoy_type_matcher_v3_HttpRequestQueryParamMatchInput_query_param(const envoy_type_matcher_v3_HttpRequestQueryParamMatchInput* msg) {
  upb_StringView default_val = upb_StringView_FromString("");
  upb_StringView ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_type_matcher_v3_HttpRequestQueryParamMatchInput_set_query_param(envoy_type_matcher_v3_HttpRequestQueryParamMatchInput *msg, upb_StringView value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
