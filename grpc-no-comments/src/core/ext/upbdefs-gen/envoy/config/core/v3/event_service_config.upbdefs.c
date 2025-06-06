
#include "upb/reflection/def.h"
#include "envoy/config/core/v3/event_service_config.upbdefs.h"
#include "envoy/config/core/v3/event_service_config.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_grpc_service_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[525] = {
    '\n', '/', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'e',
    'v', 'e', 'n', 't', '_', 's', 'e', 'r', 'v', 'i', 'c', 'e',
    '_', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'p', 'r', 'o', 't',
    'o', '\022', '\024', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '\032',
    '\'', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i',
    'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'g', 'r',
    'p', 'c', '_', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a',
    'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's',
    't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i', 'o',
    'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027',
    'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l',
    'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"',
    '\251', '\001', '\n', '\022', 'E', 'v', 'e', 'n', 't', 'S', 'e', 'r',
    'v', 'i', 'c', 'e', 'C', 'o', 'n', 'f', 'i', 'g', '\022', 'F',
    '\n', '\014', 'g', 'r', 'p', 'c', '_', 's', 'e', 'r', 'v', 'i',
    'c', 'e', '\030', '\001', ' ', '\001', '(', '\013', '2', '!', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'G', 'r', 'p', 'c',
    'S', 'e', 'r', 'v', 'i', 'c', 'e', 'H', '\000', 'R', '\013', 'g',
    'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', ':', '+',
    '\232', '\305', '\210', '\036', '&', '\n', '$', 'e', 'n', 'v', 'o', 'y',
    '.', 'a', 'p', 'i', '.', 'v', '2', '.', 'c', 'o', 'r', 'e',
    '.', 'E', 'v', 'e', 'n', 't', 'S', 'e', 'r', 'v', 'i', 'c',
    'e', 'C', 'o', 'n', 'f', 'i', 'g', 'B', '\036', '\n', '\027', 'c',
    'o', 'n', 'f', 'i', 'g', '_', 's', 'o', 'u', 'r', 'c', 'e',
    '_', 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'r', '\022', '\003',
    '\370', 'B', '\001', 'B', '\213', '\001', '\n', '\"', 'i', 'o', '.', 'e',
    'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c',
    'o', 'r', 'e', '.', 'v', '3', 'B', '\027', 'E', 'v', 'e', 'n',
    't', 'S', 'e', 'r', 'v', 'i', 'c', 'e', 'C', 'o', 'n', 'f',
    'i', 'g', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', 'B', 'g',
    'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n',
    'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-',
    'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n',
    'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', ';', 'c',
    'o', 'r', 'e', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020',
    '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[5] = {
    &envoy_config_core_v3_grpc_service_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_core_v3_event_service_config_proto_upbdefinit = {
    deps,
    &envoy_config_core_v3_event_service_config_proto_upb_file_layout,
    "envoy/config/core/v3/event_service_config.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
