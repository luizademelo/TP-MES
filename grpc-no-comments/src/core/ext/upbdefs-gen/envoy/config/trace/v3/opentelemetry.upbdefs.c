
#include "upb/reflection/def.h"
#include "envoy/config/trace/v3/opentelemetry.upbdefs.h"
#include "envoy/config/trace/v3/opentelemetry.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_extension_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_core_v3_grpc_service_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_core_v3_http_service_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_migrate_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;

static const char descriptor[803] = {
    '\n', ')', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 't', 'r', 'a', 'c', 'e', '/', 'v', '3', '/',
    'o', 'p', 'e', 'n', 't', 'e', 'l', 'e', 'm', 'e', 't', 'r',
    'y', '.', 'p', 'r', 'o', 't', 'o', '\022', '\025', 'e', 'n', 'v',
    'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'r',
    'a', 'c', 'e', '.', 'v', '3', '\032', '$', 'e', 'n', 'v', 'o',
    'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r',
    'e', '/', 'v', '3', '/', 'e', 'x', 't', 'e', 'n', 's', 'i',
    'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032', '\'', 'e', 'n',
    'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c',
    'o', 'r', 'e', '/', 'v', '3', '/', 'g', 'r', 'p', 'c', '_',
    's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'p', 'r', 'o', 't',
    'o', '\032', '\'', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n',
    'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/',
    'h', 't', 't', 'p', '_', 's', 'e', 'r', 'v', 'i', 'c', 'e',
    '.', 'p', 'r', 'o', 't', 'o', '\032', '\036', 'u', 'd', 'p', 'a',
    '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '/', 'm', 'i', 'g', 'r', 'a', 't', 'e', '.', 'p', 'r', 'o',
    't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a',
    't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\"', '\223', '\003',
    '\n', '\023', 'O', 'p', 'e', 'n', 'T', 'e', 'l', 'e', 'm', 'e',
    't', 'r', 'y', 'C', 'o', 'n', 'f', 'i', 'g', '\022', '[', '\n',
    '\014', 'g', 'r', 'p', 'c', '_', 's', 'e', 'r', 'v', 'i', 'c',
    'e', '\030', '\001', ' ', '\001', '(', '\013', '2', '!', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c',
    'o', 'r', 'e', '.', 'v', '3', '.', 'G', 'r', 'p', 'c', 'S',
    'e', 'r', 'v', 'i', 'c', 'e', 'B', '\025', '\362', '\230', '\376', '\217',
    '\005', '\017', '\022', '\r', 'o', 't', 'l', 'p', '_', 'e', 'x', 'p',
    'o', 'r', 't', 'e', 'r', 'R', '\013', 'g', 'r', 'p', 'c', 'S',
    'e', 'r', 'v', 'i', 'c', 'e', '\022', '[', '\n', '\014', 'h', 't',
    't', 'p', '_', 's', 'e', 'r', 'v', 'i', 'c', 'e', '\030', '\003',
    ' ', '\001', '(', '\013', '2', '!', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e',
    '.', 'v', '3', '.', 'H', 't', 't', 'p', 'S', 'e', 'r', 'v',
    'i', 'c', 'e', 'B', '\025', '\362', '\230', '\376', '\217', '\005', '\017', '\022',
    '\r', 'o', 't', 'l', 'p', '_', 'e', 'x', 'p', 'o', 'r', 't',
    'e', 'r', 'R', '\013', 'h', 't', 't', 'p', 'S', 'e', 'r', 'v',
    'i', 'c', 'e', '\022', '!', '\n', '\014', 's', 'e', 'r', 'v', 'i',
    'c', 'e', '_', 'n', 'a', 'm', 'e', '\030', '\002', ' ', '\001', '(',
    '\t', 'R', '\013', 's', 'e', 'r', 'v', 'i', 'c', 'e', 'N', 'a',
    'm', 'e', '\022', 'Y', '\n', '\022', 'r', 'e', 's', 'o', 'u', 'r',
    'c', 'e', '_', 'd', 'e', 't', 'e', 'c', 't', 'o', 'r', 's',
    '\030', '\004', ' ', '\003', '(', '\013', '2', '*', '.', 'e', 'n', 'v',
    'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o',
    'r', 'e', '.', 'v', '3', '.', 'T', 'y', 'p', 'e', 'd', 'E',
    'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 'C', 'o', 'n', 'f',
    'i', 'g', 'R', '\021', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e',
    'D', 'e', 't', 'e', 'c', 't', 'o', 'r', 's', '\022', 'D', '\n',
    '\007', 's', 'a', 'm', 'p', 'l', 'e', 'r', '\030', '\005', ' ', '\001',
    '(', '\013', '2', '*', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v',
    '3', '.', 'T', 'y', 'p', 'e', 'd', 'E', 'x', 't', 'e', 'n',
    's', 'i', 'o', 'n', 'C', 'o', 'n', 'f', 'i', 'g', 'R', '\007',
    's', 'a', 'm', 'p', 'l', 'e', 'r', 'B', '\211', '\001', '\n', '#',
    'i', 'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x',
    'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 't', 'r', 'a', 'c', 'e', '.', 'v', '3', 'B',
    '\022', 'O', 'p', 'e', 'n', 't', 'e', 'l', 'e', 'm', 'e', 't',
    'r', 'y', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', 'D', 'g',
    'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n',
    'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-',
    'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n',
    'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 't', 'r', 'a', 'c', 'e', '/', 'v', '3', ';',
    't', 'r', 'a', 'c', 'e', 'v', '3', '\272', '\200', '\310', '\321', '\006',
    '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[6] = {
    &envoy_config_core_v3_extension_proto_upbdefinit,
    &envoy_config_core_v3_grpc_service_proto_upbdefinit,
    &envoy_config_core_v3_http_service_proto_upbdefinit,
    &udpa_annotations_migrate_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_trace_v3_opentelemetry_proto_upbdefinit = {
    deps,
    &envoy_config_trace_v3_opentelemetry_proto_upb_file_layout,
    "envoy/config/trace/v3/opentelemetry.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
