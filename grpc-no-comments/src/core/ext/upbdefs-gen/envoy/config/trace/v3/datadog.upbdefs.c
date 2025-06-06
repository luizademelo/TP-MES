
#include "upb/reflection/def.h"
#include "envoy/config/trace/v3/datadog.upbdefs.h"
#include "envoy/config/trace/v3/datadog.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_duration_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_migrate_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[786] = {
    '\n', '#', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 't', 'r', 'a', 'c', 'e', '/', 'v', '3', '/',
    'd', 'a', 't', 'a', 'd', 'o', 'g', '.', 'p', 'r', 'o', 't',
    'o', '\022', '\025', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 't', 'r', 'a', 'c', 'e', '.', 'v', '3',
    '\032', '\036', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '/', 'd', 'u', 'r', 'a', 't', 'i',
    'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032', '\036', 'u', 'd',
    'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o',
    'n', 's', '/', 'm', 'i', 'g', 'r', 'a', 't', 'e', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a',
    'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's',
    't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i', 'o',
    'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027',
    'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l',
    'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"',
    '[', '\n', '\023', 'D', 'a', 't', 'a', 'd', 'o', 'g', 'R', 'e',
    'm', 'o', 't', 'e', 'C', 'o', 'n', 'f', 'i', 'g', '\022', 'D',
    '\n', '\020', 'p', 'o', 'l', 'l', 'i', 'n', 'g', '_', 'i', 'n',
    't', 'e', 'r', 'v', 'a', 'l', '\030', '\001', ' ', '\001', '(', '\013',
    '2', '\031', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r',
    'o', 't', 'o', 'b', 'u', 'f', '.', 'D', 'u', 'r', 'a', 't',
    'i', 'o', 'n', 'R', '\017', 'p', 'o', 'l', 'l', 'i', 'n', 'g',
    'I', 'n', 't', 'e', 'r', 'v', 'a', 'l', '\"', '\235', '\002', '\n',
    '\r', 'D', 'a', 't', 'a', 'd', 'o', 'g', 'C', 'o', 'n', 'f',
    'i', 'g', '\022', '4', '\n', '\021', 'c', 'o', 'l', 'l', 'e', 'c',
    't', 'o', 'r', '_', 'c', 'l', 'u', 's', 't', 'e', 'r', '\030',
    '\001', ' ', '\001', '(', '\t', 'B', '\007', '\372', 'B', '\004', 'r', '\002',
    '\020', '\001', 'R', '\020', 'c', 'o', 'l', 'l', 'e', 'c', 't', 'o',
    'r', 'C', 'l', 'u', 's', 't', 'e', 'r', '\022', '*', '\n', '\014',
    's', 'e', 'r', 'v', 'i', 'c', 'e', '_', 'n', 'a', 'm', 'e',
    '\030', '\002', ' ', '\001', '(', '\t', 'B', '\007', '\372', 'B', '\004', 'r',
    '\002', '\020', '\001', 'R', '\013', 's', 'e', 'r', 'v', 'i', 'c', 'e',
    'N', 'a', 'm', 'e', '\022', '-', '\n', '\022', 'c', 'o', 'l', 'l',
    'e', 'c', 't', 'o', 'r', '_', 'h', 'o', 's', 't', 'n', 'a',
    'm', 'e', '\030', '\003', ' ', '\001', '(', '\t', 'R', '\021', 'c', 'o',
    'l', 'l', 'e', 'c', 't', 'o', 'r', 'H', 'o', 's', 't', 'n',
    'a', 'm', 'e', '\022', 'O', '\n', '\r', 'r', 'e', 'm', 'o', 't',
    'e', '_', 'c', 'o', 'n', 'f', 'i', 'g', '\030', '\004', ' ', '\001',
    '(', '\013', '2', '*', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 't', 'r', 'a', 'c', 'e', '.',
    'v', '3', '.', 'D', 'a', 't', 'a', 'd', 'o', 'g', 'R', 'e',
    'm', 'o', 't', 'e', 'C', 'o', 'n', 'f', 'i', 'g', 'R', '\014',
    'r', 'e', 'm', 'o', 't', 'e', 'C', 'o', 'n', 'f', 'i', 'g',
    ':', '*', '\232', '\305', '\210', '\036', '%', '\n', '#', 'e', 'n', 'v',
    'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'r',
    'a', 'c', 'e', '.', 'v', '2', '.', 'D', 'a', 't', 'a', 'd',
    'o', 'g', 'C', 'o', 'n', 'f', 'i', 'g', 'B', '\263', '\001', '\n',
    '#', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o',
    'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 't', 'r', 'a', 'c', 'e', '.', 'v', '3',
    'B', '\014', 'D', 'a', 't', 'a', 'd', 'o', 'g', 'P', 'r', 'o',
    't', 'o', 'P', '\001', 'Z', 'D', 'g', 'i', 't', 'h', 'u', 'b',
    '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r',
    'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r',
    'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v',
    'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 't', 'r',
    'a', 'c', 'e', '/', 'v', '3', ';', 't', 'r', 'a', 'c', 'e',
    'v', '3', '\362', '\230', '\376', '\217', '\005', '*', '\022', '(', 'e', 'n',
    'v', 'o', 'y', '.', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o',
    'n', 's', '.', 't', 'r', 'a', 'c', 'e', 'r', 's', '.', 'd',
    'a', 't', 'a', 'd', 'o', 'g', '.', 'v', '4', 'a', 'l', 'p',
    'h', 'a', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006',
    'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[6] = {
    &google_protobuf_duration_proto_upbdefinit,
    &udpa_annotations_migrate_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_trace_v3_datadog_proto_upbdefinit = {
    deps,
    &envoy_config_trace_v3_datadog_proto_upb_file_layout,
    "envoy/config/trace/v3/datadog.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
