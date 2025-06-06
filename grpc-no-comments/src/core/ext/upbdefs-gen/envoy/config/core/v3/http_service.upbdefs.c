
#include "upb/reflection/def.h"
#include "envoy/config/core/v3/http_service.upbdefs.h"
#include "envoy/config/core/v3/http_service.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_base_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_core_v3_http_uri_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[511] = {
    '\n', '\'', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'h',
    't', 't', 'p', '_', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.',
    'p', 'r', 'o', 't', 'o', '\022', '\024', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e',
    '.', 'v', '3', '\032', '\037', 'e', 'n', 'v', 'o', 'y', '/', 'c',
    'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '/', 'b', 'a', 's', 'e', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '#', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'h',
    't', 't', 'p', '_', 'u', 'r', 'i', '.', 'p', 'r', 'o', 't',
    'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o',
    't', 'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't',
    'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027', 'v', 'a',
    'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd',
    'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"', '\260', '\001',
    '\n', '\013', 'H', 't', 't', 'p', 'S', 'e', 'r', 'v', 'i', 'c',
    'e', '\022', '8', '\n', '\010', 'h', 't', 't', 'p', '_', 'u', 'r',
    'i', '\030', '\001', ' ', '\001', '(', '\013', '2', '\035', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c',
    'o', 'r', 'e', '.', 'v', '3', '.', 'H', 't', 't', 'p', 'U',
    'r', 'i', 'R', '\007', 'h', 't', 't', 'p', 'U', 'r', 'i', '\022',
    'g', '\n', '\026', 'r', 'e', 'q', 'u', 'e', 's', 't', '_', 'h',
    'e', 'a', 'd', 'e', 'r', 's', '_', 't', 'o', '_', 'a', 'd',
    'd', '\030', '\002', ' ', '\003', '(', '\013', '2', '\'', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c',
    'o', 'r', 'e', '.', 'v', '3', '.', 'H', 'e', 'a', 'd', 'e',
    'r', 'V', 'a', 'l', 'u', 'e', 'O', 'p', 't', 'i', 'o', 'n',
    'B', '\t', '\372', 'B', '\006', '\222', '\001', '\003', '\020', '\350', '\007', 'R',
    '\023', 'r', 'e', 'q', 'u', 'e', 's', 't', 'H', 'e', 'a', 'd',
    'e', 'r', 's', 'T', 'o', 'A', 'd', 'd', 'B', '\204', '\001', '\n',
    '\"', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o',
    'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', 'B',
    '\020', 'H', 't', 't', 'p', 'S', 'e', 'r', 'v', 'i', 'c', 'e',
    'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', 'B', 'g', 'i', 't',
    'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o',
    'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o',
    'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/',
    'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g',
    '/', 'c', 'o', 'r', 'e', '/', 'v', '3', ';', 'c', 'o', 'r',
    'e', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b',
    '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[5] = {
    &envoy_config_core_v3_base_proto_upbdefinit,
    &envoy_config_core_v3_http_uri_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_core_v3_http_service_proto_upbdefinit = {
    deps,
    &envoy_config_core_v3_http_service_proto_upb_file_layout,
    "envoy/config/core/v3/http_service.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
