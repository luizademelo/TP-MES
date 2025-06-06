
#include "upb/reflection/def.h"
#include "envoy/config/trace/v3/skywalking.upbdefs.h"
#include "envoy/config/trace/v3/skywalking.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_grpc_service_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_wrappers_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_migrate_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_sensitive_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[860] = {
    '\n', '&', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 't', 'r', 'a', 'c', 'e', '/', 'v', '3', '/',
    's', 'k', 'y', 'w', 'a', 'l', 'k', 'i', 'n', 'g', '.', 'p',
    'r', 'o', 't', 'o', '\022', '\025', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'r', 'a', 'c', 'e',
    '.', 'v', '3', '\032', '\'', 'e', 'n', 'v', 'o', 'y', '/', 'c',
    'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '/', 'g', 'r', 'p', 'c', '_', 's', 'e', 'r', 'v', 'i',
    'c', 'e', '.', 'p', 'r', 'o', 't', 'o', '\032', '\036', 'g', 'o',
    'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u',
    'f', '/', 'w', 'r', 'a', 'p', 'p', 'e', 'r', 's', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\036', 'u', 'd', 'p', 'a', '/', 'a',
    'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 'm',
    'i', 'g', 'r', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o',
    '\032', ' ', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 's', 'e', 'n', 's', 'i',
    't', 'i', 'v', 'e', '.', 'p', 'r', 'o', 't', 'o', '\032', '\035',
    'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't',
    'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u', 's', '.',
    'p', 'r', 'o', 't', 'o', '\032', '\027', 'v', 'a', 'l', 'i', 'd',
    'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e',
    '.', 'p', 'r', 'o', 't', 'o', '\"', '\254', '\001', '\n', '\020', 'S',
    'k', 'y', 'W', 'a', 'l', 'k', 'i', 'n', 'g', 'C', 'o', 'n',
    'f', 'i', 'g', '\022', 'N', '\n', '\014', 'g', 'r', 'p', 'c', '_',
    's', 'e', 'r', 'v', 'i', 'c', 'e', '\030', '\001', ' ', '\001', '(',
    '\013', '2', '!', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o',
    'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3',
    '.', 'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e',
    'B', '\010', '\372', 'B', '\005', '\212', '\001', '\002', '\020', '\001', 'R', '\013',
    'g', 'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '\022',
    'H', '\n', '\r', 'c', 'l', 'i', 'e', 'n', 't', '_', 'c', 'o',
    'n', 'f', 'i', 'g', '\030', '\002', ' ', '\001', '(', '\013', '2', '#',
    '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i',
    'g', '.', 't', 'r', 'a', 'c', 'e', '.', 'v', '3', '.', 'C',
    'l', 'i', 'e', 'n', 't', 'C', 'o', 'n', 'f', 'i', 'g', 'R',
    '\014', 'c', 'l', 'i', 'e', 'n', 't', 'C', 'o', 'n', 'f', 'i',
    'g', '\"', '\344', '\001', '\n', '\014', 'C', 'l', 'i', 'e', 'n', 't',
    'C', 'o', 'n', 'f', 'i', 'g', '\022', '!', '\n', '\014', 's', 'e',
    'r', 'v', 'i', 'c', 'e', '_', 'n', 'a', 'm', 'e', '\030', '\001',
    ' ', '\001', '(', '\t', 'R', '\013', 's', 'e', 'r', 'v', 'i', 'c',
    'e', 'N', 'a', 'm', 'e', '\022', '#', '\n', '\r', 'i', 'n', 's',
    't', 'a', 'n', 'c', 'e', '_', 'n', 'a', 'm', 'e', '\030', '\002',
    ' ', '\001', '(', '\t', 'R', '\014', 'i', 'n', 's', 't', 'a', 'n',
    'c', 'e', 'N', 'a', 'm', 'e', '\022', '-', '\n', '\r', 'b', 'a',
    'c', 'k', 'e', 'n', 'd', '_', 't', 'o', 'k', 'e', 'n', '\030',
    '\003', ' ', '\001', '(', '\t', 'B', '\006', '\270', '\267', '\213', '\244', '\002',
    '\001', 'H', '\000', 'R', '\014', 'b', 'a', 'c', 'k', 'e', 'n', 'd',
    'T', 'o', 'k', 'e', 'n', '\022', 'B', '\n', '\016', 'm', 'a', 'x',
    '_', 'c', 'a', 'c', 'h', 'e', '_', 's', 'i', 'z', 'e', '\030',
    '\004', ' ', '\001', '(', '\013', '2', '\034', '.', 'g', 'o', 'o', 'g',
    'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.',
    'U', 'I', 'n', 't', '3', '2', 'V', 'a', 'l', 'u', 'e', 'R',
    '\014', 'm', 'a', 'x', 'C', 'a', 'c', 'h', 'e', 'S', 'i', 'z',
    'e', 'B', '\031', '\n', '\027', 'b', 'a', 'c', 'k', 'e', 'n', 'd',
    '_', 't', 'o', 'k', 'e', 'n', '_', 's', 'p', 'e', 'c', 'i',
    'f', 'i', 'e', 'r', 'B', '\271', '\001', '\n', '#', 'i', 'o', '.',
    'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    't', 'r', 'a', 'c', 'e', '.', 'v', '3', 'B', '\017', 'S', 'k',
    'y', 'w', 'a', 'l', 'k', 'i', 'n', 'g', 'P', 'r', 'o', 't',
    'o', 'P', '\001', 'Z', 'D', 'g', 'i', 't', 'h', 'u', 'b', '.',
    'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o',
    'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o',
    'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o',
    'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 't', 'r', 'a',
    'c', 'e', '/', 'v', '3', ';', 't', 'r', 'a', 'c', 'e', 'v',
    '3', '\362', '\230', '\376', '\217', '\005', '-', '\022', '+', 'e', 'n', 'v',
    'o', 'y', '.', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n',
    's', '.', 't', 'r', 'a', 'c', 'e', 'r', 's', '.', 's', 'k',
    'y', 'w', 'a', 'l', 'k', 'i', 'n', 'g', '.', 'v', '4', 'a',
    'l', 'p', 'h', 'a', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002',
    'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[7] = {
    &envoy_config_core_v3_grpc_service_proto_upbdefinit,
    &google_protobuf_wrappers_proto_upbdefinit,
    &udpa_annotations_migrate_proto_upbdefinit,
    &udpa_annotations_sensitive_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_trace_v3_skywalking_proto_upbdefinit = {
    deps,
    &envoy_config_trace_v3_skywalking_proto_upb_file_layout,
    "envoy/config/trace/v3/skywalking.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
