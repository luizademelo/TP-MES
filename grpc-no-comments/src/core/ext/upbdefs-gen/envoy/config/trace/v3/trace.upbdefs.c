
#include "upb/reflection/def.h"
#include "envoy/config/trace/v3/trace.upbdefs.h"
#include "envoy/config/trace/v3/trace.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_trace_v3_datadog_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_trace_v3_dynamic_ot_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_trace_v3_http_tracer_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_trace_v3_lightstep_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_trace_v3_opentelemetry_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_trace_v3_service_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_trace_v3_zipkin_proto_upbdefinit;

static const char descriptor[476] = {
    '\n', '!', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 't', 'r', 'a', 'c', 'e', '/', 'v', '3', '/',
    't', 'r', 'a', 'c', 'e', '.', 'p', 'r', 'o', 't', 'o', '\022',
    '\025', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i',
    'g', '.', 't', 'r', 'a', 'c', 'e', '.', 'v', '3', '\032', '#',
    'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g',
    '/', 't', 'r', 'a', 'c', 'e', '/', 'v', '3', '/', 'd', 'a',
    't', 'a', 'd', 'o', 'g', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '&', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i',
    'g', '/', 't', 'r', 'a', 'c', 'e', '/', 'v', '3', '/', 'd',
    'y', 'n', 'a', 'm', 'i', 'c', '_', 'o', 't', '.', 'p', 'r',
    'o', 't', 'o', '\032', '\'', 'e', 'n', 'v', 'o', 'y', '/', 'c',
    'o', 'n', 'f', 'i', 'g', '/', 't', 'r', 'a', 'c', 'e', '/',
    'v', '3', '/', 'h', 't', 't', 'p', '_', 't', 'r', 'a', 'c',
    'e', 'r', '.', 'p', 'r', 'o', 't', 'o', '\032', '%', 'e', 'n',
    'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 't',
    'r', 'a', 'c', 'e', '/', 'v', '3', '/', 'l', 'i', 'g', 'h',
    't', 's', 't', 'e', 'p', '.', 'p', 'r', 'o', 't', 'o', '\032',
    ')', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i',
    'g', '/', 't', 'r', 'a', 'c', 'e', '/', 'v', '3', '/', 'o',
    'p', 'e', 'n', 't', 'e', 'l', 'e', 'm', 'e', 't', 'r', 'y',
    '.', 'p', 'r', 'o', 't', 'o', '\032', '#', 'e', 'n', 'v', 'o',
    'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 't', 'r', 'a',
    'c', 'e', '/', 'v', '3', '/', 's', 'e', 'r', 'v', 'i', 'c',
    'e', '.', 'p', 'r', 'o', 't', 'o', '\032', '\"', 'e', 'n', 'v',
    'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 't', 'r',
    'a', 'c', 'e', '/', 'v', '3', '/', 'z', 'i', 'p', 'k', 'i',
    'n', '.', 'p', 'r', 'o', 't', 'o', 'B', 'y', '\n', '#', 'i',
    'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y',
    '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i',
    'g', '.', 't', 'r', 'a', 'c', 'e', '.', 'v', '3', 'B', '\n',
    'T', 'r', 'a', 'c', 'e', 'P', 'r', 'o', 't', 'o', 'P', '\001',
    'Z', 'D', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm',
    '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/',
    'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p',
    'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 'c',
    'o', 'n', 'f', 'i', 'g', '/', 't', 'r', 'a', 'c', 'e', '/',
    'v', '3', ';', 't', 'r', 'a', 'c', 'e', 'v', '3', 'P', '\000',
    'P', '\001', 'P', '\002', 'P', '\003', 'P', '\004', 'P', '\005', 'P', '\006',
    'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[8] = {
    &envoy_config_trace_v3_datadog_proto_upbdefinit,
    &envoy_config_trace_v3_dynamic_ot_proto_upbdefinit,
    &envoy_config_trace_v3_http_tracer_proto_upbdefinit,
    &envoy_config_trace_v3_lightstep_proto_upbdefinit,
    &envoy_config_trace_v3_opentelemetry_proto_upbdefinit,
    &envoy_config_trace_v3_service_proto_upbdefinit,
    &envoy_config_trace_v3_zipkin_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_trace_v3_trace_proto_upbdefinit = {
    deps,
    &envoy_config_trace_v3_trace_proto_upb_file_layout,
    "envoy/config/trace/v3/trace.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
