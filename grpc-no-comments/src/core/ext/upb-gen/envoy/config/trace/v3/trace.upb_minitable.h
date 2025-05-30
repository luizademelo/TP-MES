
#ifndef ENVOY_CONFIG_TRACE_V3_TRACE_PROTO_UPB_H__UPB_MINITABLE_H_
#define ENVOY_CONFIG_TRACE_V3_TRACE_PROTO_UPB_H__UPB_MINITABLE_H_

#include "upb/generated_code_support.h"

#include "envoy/config/trace/v3/datadog.upb_minitable.h"
#include "envoy/config/trace/v3/dynamic_ot.upb_minitable.h"
#include "envoy/config/trace/v3/http_tracer.upb_minitable.h"
#include "envoy/config/trace/v3/lightstep.upb_minitable.h"
#include "envoy/config/trace/v3/opentelemetry.upb_minitable.h"
#include "envoy/config/trace/v3/service.upb_minitable.h"
#include "envoy/config/trace/v3/zipkin.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern const upb_MiniTableFile envoy_config_trace_v3_trace_proto_upb_file_layout;

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
