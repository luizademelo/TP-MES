
#include "upb/reflection/def.h"
#include "envoy/config/core/v3/resolver.upbdefs.h"
#include "envoy/config/core/v3/resolver.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_address_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[612] = {
    '\n', '#', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'r',
    'e', 's', 'o', 'l', 'v', 'e', 'r', '.', 'p', 'r', 'o', 't',
    'o', '\022', '\024', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '\032',
    '\"', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i',
    'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'a', 'd',
    'd', 'r', 'e', 's', 's', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u', 's',
    '.', 'p', 'r', 'o', 't', 'o', '\032', '\027', 'v', 'a', 'l', 'i',
    'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't',
    'e', '.', 'p', 'r', 'o', 't', 'o', '\"', '\203', '\001', '\n', '\022',
    'D', 'n', 's', 'R', 'e', 's', 'o', 'l', 'v', 'e', 'r', 'O',
    'p', 't', 'i', 'o', 'n', 's', '\022', '4', '\n', '\027', 'u', 's',
    'e', '_', 't', 'c', 'p', '_', 'f', 'o', 'r', '_', 'd', 'n',
    's', '_', 'l', 'o', 'o', 'k', 'u', 'p', 's', '\030', '\001', ' ',
    '\001', '(', '\010', 'R', '\023', 'u', 's', 'e', 'T', 'c', 'p', 'F',
    'o', 'r', 'D', 'n', 's', 'L', 'o', 'o', 'k', 'u', 'p', 's',
    '\022', '7', '\n', '\030', 'n', 'o', '_', 'd', 'e', 'f', 'a', 'u',
    'l', 't', '_', 's', 'e', 'a', 'r', 'c', 'h', '_', 'd', 'o',
    'm', 'a', 'i', 'n', '\030', '\002', ' ', '\001', '(', '\010', 'R', '\025',
    'n', 'o', 'D', 'e', 'f', 'a', 'u', 'l', 't', 'S', 'e', 'a',
    'r', 'c', 'h', 'D', 'o', 'm', 'a', 'i', 'n', '\"', '\270', '\001',
    '\n', '\023', 'D', 'n', 's', 'R', 'e', 's', 'o', 'l', 'u', 't',
    'i', 'o', 'n', 'C', 'o', 'n', 'f', 'i', 'g', '\022', 'E', '\n',
    '\t', 'r', 'e', 's', 'o', 'l', 'v', 'e', 'r', 's', '\030', '\001',
    ' ', '\003', '(', '\013', '2', '\035', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e',
    '.', 'v', '3', '.', 'A', 'd', 'd', 'r', 'e', 's', 's', 'B',
    '\010', '\372', 'B', '\005', '\222', '\001', '\002', '\010', '\001', 'R', '\t', 'r',
    'e', 's', 'o', 'l', 'v', 'e', 'r', 's', '\022', 'Z', '\n', '\024',
    'd', 'n', 's', '_', 'r', 'e', 's', 'o', 'l', 'v', 'e', 'r',
    '_', 'o', 'p', 't', 'i', 'o', 'n', 's', '\030', '\002', ' ', '\001',
    '(', '\013', '2', '(', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v',
    '3', '.', 'D', 'n', 's', 'R', 'e', 's', 'o', 'l', 'v', 'e',
    'r', 'O', 'p', 't', 'i', 'o', 'n', 's', 'R', '\022', 'd', 'n',
    's', 'R', 'e', 's', 'o', 'l', 'v', 'e', 'r', 'O', 'p', 't',
    'i', 'o', 'n', 's', 'B', '\201', '\001', '\n', '\"', 'i', 'o', '.',
    'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'c', 'o', 'r', 'e', '.', 'v', '3', 'B', '\r', 'R', 'e', 's',
    'o', 'l', 'v', 'e', 'r', 'P', 'r', 'o', 't', 'o', 'P', '\001',
    'Z', 'B', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm',
    '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/',
    'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p',
    'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 'c',
    'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', ';', 'c', 'o', 'r', 'e', 'v', '3', '\272', '\200', '\310', '\321',
    '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &envoy_config_core_v3_address_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_core_v3_resolver_proto_upbdefinit = {
    deps,
    &envoy_config_core_v3_resolver_proto_upb_file_layout,
    "envoy/config/core/v3/resolver.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
