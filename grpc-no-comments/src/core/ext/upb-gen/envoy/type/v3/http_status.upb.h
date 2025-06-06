
#ifndef ENVOY_TYPE_V3_HTTP_STATUS_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_V3_HTTP_STATUS_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/v3/http_status.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_type_v3_HttpStatus { upb_Message UPB_PRIVATE(base); } envoy_type_v3_HttpStatus;

typedef enum {
  envoy_type_v3_Empty = 0,
  envoy_type_v3_Continue = 100,
  envoy_type_v3_OK = 200,
  envoy_type_v3_Created = 201,
  envoy_type_v3_Accepted = 202,
  envoy_type_v3_NonAuthoritativeInformation = 203,
  envoy_type_v3_NoContent = 204,
  envoy_type_v3_ResetContent = 205,
  envoy_type_v3_PartialContent = 206,
  envoy_type_v3_MultiStatus = 207,
  envoy_type_v3_AlreadyReported = 208,
  envoy_type_v3_IMUsed = 226,
  envoy_type_v3_MultipleChoices = 300,
  envoy_type_v3_MovedPermanently = 301,
  envoy_type_v3_Found = 302,
  envoy_type_v3_SeeOther = 303,
  envoy_type_v3_NotModified = 304,
  envoy_type_v3_UseProxy = 305,
  envoy_type_v3_TemporaryRedirect = 307,
  envoy_type_v3_PermanentRedirect = 308,
  envoy_type_v3_BadRequest = 400,
  envoy_type_v3_Unauthorized = 401,
  envoy_type_v3_PaymentRequired = 402,
  envoy_type_v3_Forbidden = 403,
  envoy_type_v3_NotFound = 404,
  envoy_type_v3_MethodNotAllowed = 405,
  envoy_type_v3_NotAcceptable = 406,
  envoy_type_v3_ProxyAuthenticationRequired = 407,
  envoy_type_v3_RequestTimeout = 408,
  envoy_type_v3_Conflict = 409,
  envoy_type_v3_Gone = 410,
  envoy_type_v3_LengthRequired = 411,
  envoy_type_v3_PreconditionFailed = 412,
  envoy_type_v3_PayloadTooLarge = 413,
  envoy_type_v3_URITooLong = 414,
  envoy_type_v3_UnsupportedMediaType = 415,
  envoy_type_v3_RangeNotSatisfiable = 416,
  envoy_type_v3_ExpectationFailed = 417,
  envoy_type_v3_MisdirectedRequest = 421,
  envoy_type_v3_UnprocessableEntity = 422,
  envoy_type_v3_Locked = 423,
  envoy_type_v3_FailedDependency = 424,
  envoy_type_v3_UpgradeRequired = 426,
  envoy_type_v3_PreconditionRequired = 428,
  envoy_type_v3_TooManyRequests = 429,
  envoy_type_v3_RequestHeaderFieldsTooLarge = 431,
  envoy_type_v3_InternalServerError = 500,
  envoy_type_v3_NotImplemented = 501,
  envoy_type_v3_BadGateway = 502,
  envoy_type_v3_ServiceUnavailable = 503,
  envoy_type_v3_GatewayTimeout = 504,
  envoy_type_v3_HTTPVersionNotSupported = 505,
  envoy_type_v3_VariantAlsoNegotiates = 506,
  envoy_type_v3_InsufficientStorage = 507,
  envoy_type_v3_LoopDetected = 508,
  envoy_type_v3_NotExtended = 510,
  envoy_type_v3_NetworkAuthenticationRequired = 511
} envoy_type_v3_StatusCode;

UPB_INLINE envoy_type_v3_HttpStatus* envoy_type_v3_HttpStatus_new(upb_Arena* arena) {
  return (envoy_type_v3_HttpStatus*)_upb_Message_New(&envoy__type__v3__HttpStatus_msg_init, arena);
}
UPB_INLINE envoy_type_v3_HttpStatus* envoy_type_v3_HttpStatus_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_type_v3_HttpStatus* ret = envoy_type_v3_HttpStatus_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__HttpStatus_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_type_v3_HttpStatus* envoy_type_v3_HttpStatus_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_type_v3_HttpStatus* ret = envoy_type_v3_HttpStatus_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__type__v3__HttpStatus_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_type_v3_HttpStatus_serialize(const envoy_type_v3_HttpStatus* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__HttpStatus_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_type_v3_HttpStatus_serialize_ex(const envoy_type_v3_HttpStatus* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__type__v3__HttpStatus_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_type_v3_HttpStatus_clear_code(envoy_type_v3_HttpStatus* msg) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE int32_t envoy_type_v3_HttpStatus_code(const envoy_type_v3_HttpStatus* msg) {
  int32_t default_val = 0;
  int32_t ret;
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}

UPB_INLINE void envoy_type_v3_HttpStatus_set_code(envoy_type_v3_HttpStatus *msg, int32_t value) {
  const upb_MiniTableField field = {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)};
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
