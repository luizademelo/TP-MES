
#ifndef ENVOY_TYPE_V3_HTTP_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_V3_HTTP_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/v3/http.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  envoy_type_v3_HTTP1 = 0,
  envoy_type_v3_HTTP2 = 1,
  envoy_type_v3_HTTP3 = 2
} envoy_type_v3_CodecClientType;

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
