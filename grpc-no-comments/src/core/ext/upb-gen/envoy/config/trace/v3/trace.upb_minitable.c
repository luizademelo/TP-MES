
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/trace/v3/trace.upb_minitable.h"
#include "envoy/config/trace/v3/datadog.upb_minitable.h"
#include "envoy/config/trace/v3/dynamic_ot.upb_minitable.h"
#include "envoy/config/trace/v3/http_tracer.upb_minitable.h"
#include "envoy/config/trace/v3/lightstep.upb_minitable.h"
#include "envoy/config/trace/v3/opentelemetry.upb_minitable.h"
#include "envoy/config/trace/v3/service.upb_minitable.h"
#include "envoy/config/trace/v3/zipkin.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
const upb_MiniTableFile envoy_config_trace_v3_trace_proto_upb_file_layout = {
  NULL,
  NULL,
  NULL,
  0,
  0,
  0,
};

#include "upb/port/undef.inc"
