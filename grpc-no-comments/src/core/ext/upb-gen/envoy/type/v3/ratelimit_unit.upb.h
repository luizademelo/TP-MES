
#ifndef ENVOY_TYPE_V3_RATELIMIT_UNIT_PROTO_UPB_H__UPB_H_
#define ENVOY_TYPE_V3_RATELIMIT_UNIT_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/type/v3/ratelimit_unit.upb_minitable.h"

#include "udpa/annotations/status.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  envoy_type_v3_UNKNOWN = 0,
  envoy_type_v3_SECOND = 1,
  envoy_type_v3_MINUTE = 2,
  envoy_type_v3_HOUR = 3,
  envoy_type_v3_DAY = 4,
  envoy_type_v3_MONTH = 5,
  envoy_type_v3_YEAR = 6
} envoy_type_v3_RateLimitUnit;

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
