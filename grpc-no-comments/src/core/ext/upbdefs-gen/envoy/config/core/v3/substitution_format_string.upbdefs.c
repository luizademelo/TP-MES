
#include "upb/reflection/def.h"
#include "envoy/config/core/v3/substitution_format_string.upbdefs.h"
#include "envoy/config/core/v3/substitution_format_string.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_base_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_core_v3_extension_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_struct_proto_upbdefinit;
extern _upb_DefPool_Init envoy_annotations_deprecation_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[990] = {
    '\n', '5', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 's',
    'u', 'b', 's', 't', 'i', 't', 'u', 't', 'i', 'o', 'n', '_',
    'f', 'o', 'r', 'm', 'a', 't', '_', 's', 't', 'r', 'i', 'n',
    'g', '.', 'p', 'r', 'o', 't', 'o', '\022', '\024', 'e', 'n', 'v',
    'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o',
    'r', 'e', '.', 'v', '3', '\032', '\037', 'e', 'n', 'v', 'o', 'y',
    '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e',
    '/', 'v', '3', '/', 'b', 'a', 's', 'e', '.', 'p', 'r', 'o',
    't', 'o', '\032', '$', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o',
    'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3',
    '/', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\034', 'g', 'o', 'o', 'g', 'l', 'e',
    '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 's', 't',
    'r', 'u', 'c', 't', '.', 'p', 'r', 'o', 't', 'o', '\032', '#',
    'e', 'n', 'v', 'o', 'y', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'd', 'e', 'p', 'r', 'e', 'c',
    'a', 't', 'i', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u', 's',
    '.', 'p', 'r', 'o', 't', 'o', '\032', '\027', 'v', 'a', 'l', 'i',
    'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't',
    'e', '.', 'p', 'r', 'o', 't', 'o', '\"', '<', '\n', '\021', 'J',
    's', 'o', 'n', 'F', 'o', 'r', 'm', 'a', 't', 'O', 'p', 't',
    'i', 'o', 'n', 's', '\022', '\'', '\n', '\017', 's', 'o', 'r', 't',
    '_', 'p', 'r', 'o', 'p', 'e', 'r', 't', 'i', 'e', 's', '\030',
    '\001', ' ', '\001', '(', '\010', 'R', '\016', 's', 'o', 'r', 't', 'P',
    'r', 'o', 'p', 'e', 'r', 't', 'i', 'e', 's', '\"', '\362', '\003',
    '\n', '\030', 'S', 'u', 'b', 's', 't', 'i', 't', 'u', 't', 'i',
    'o', 'n', 'F', 'o', 'r', 'm', 'a', 't', 'S', 't', 'r', 'i',
    'n', 'g', '\022', '.', '\n', '\013', 't', 'e', 'x', 't', '_', 'f',
    'o', 'r', 'm', 'a', 't', '\030', '\001', ' ', '\001', '(', '\t', 'B',
    '\013', '\030', '\001', '\222', '\307', '\206', '\330', '\004', '\003', '3', '.', '0',
    'H', '\000', 'R', '\n', 't', 'e', 'x', 't', 'F', 'o', 'r', 'm',
    'a', 't', '\022', 'D', '\n', '\013', 'j', 's', 'o', 'n', '_', 'f',
    'o', 'r', 'm', 'a', 't', '\030', '\002', ' ', '\001', '(', '\013', '2',
    '\027', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '.', 'S', 't', 'r', 'u', 'c', 't',
    'B', '\010', '\372', 'B', '\005', '\212', '\001', '\002', '\020', '\001', 'H', '\000',
    'R', '\n', 'j', 's', 'o', 'n', 'F', 'o', 'r', 'm', 'a', 't',
    '\022', 'P', '\n', '\022', 't', 'e', 'x', 't', '_', 'f', 'o', 'r',
    'm', 'a', 't', '_', 's', 'o', 'u', 'r', 'c', 'e', '\030', '\005',
    ' ', '\001', '(', '\013', '2', ' ', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e',
    '.', 'v', '3', '.', 'D', 'a', 't', 'a', 'S', 'o', 'u', 'r',
    'c', 'e', 'H', '\000', 'R', '\020', 't', 'e', 'x', 't', 'F', 'o',
    'r', 'm', 'a', 't', 'S', 'o', 'u', 'r', 'c', 'e', '\022', '*',
    '\n', '\021', 'o', 'm', 'i', 't', '_', 'e', 'm', 'p', 't', 'y',
    '_', 'v', 'a', 'l', 'u', 'e', 's', '\030', '\003', ' ', '\001', '(',
    '\010', 'R', '\017', 'o', 'm', 'i', 't', 'E', 'm', 'p', 't', 'y',
    'V', 'a', 'l', 'u', 'e', 's', '\022', '.', '\n', '\014', 'c', 'o',
    'n', 't', 'e', 'n', 't', '_', 't', 'y', 'p', 'e', '\030', '\004',
    ' ', '\001', '(', '\t', 'B', '\013', '\372', 'B', '\010', 'r', '\006', '\300',
    '\001', '\002', '\310', '\001', '\000', 'R', '\013', 'c', 'o', 'n', 't', 'e',
    'n', 't', 'T', 'y', 'p', 'e', '\022', 'J', '\n', '\n', 'f', 'o',
    'r', 'm', 'a', 't', 't', 'e', 'r', 's', '\030', '\006', ' ', '\003',
    '(', '\013', '2', '*', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v',
    '3', '.', 'T', 'y', 'p', 'e', 'd', 'E', 'x', 't', 'e', 'n',
    's', 'i', 'o', 'n', 'C', 'o', 'n', 'f', 'i', 'g', 'R', '\n',
    'f', 'o', 'r', 'm', 'a', 't', 't', 'e', 'r', 's', '\022', 'W',
    '\n', '\023', 'j', 's', 'o', 'n', '_', 'f', 'o', 'r', 'm', 'a',
    't', '_', 'o', 'p', 't', 'i', 'o', 'n', 's', '\030', '\007', ' ',
    '\001', '(', '\013', '2', '\'', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.',
    'v', '3', '.', 'J', 's', 'o', 'n', 'F', 'o', 'r', 'm', 'a',
    't', 'O', 'p', 't', 'i', 'o', 'n', 's', 'R', '\021', 'j', 's',
    'o', 'n', 'F', 'o', 'r', 'm', 'a', 't', 'O', 'p', 't', 'i',
    'o', 'n', 's', 'B', '\r', '\n', '\006', 'f', 'o', 'r', 'm', 'a',
    't', '\022', '\003', '\370', 'B', '\001', 'B', '\221', '\001', '\n', '\"', 'i',
    'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y',
    '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i',
    'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', 'B', '\035', 'S',
    'u', 'b', 's', 't', 'i', 't', 'u', 't', 'i', 'o', 'n', 'F',
    'o', 'r', 'm', 'a', 't', 'S', 't', 'r', 'i', 'n', 'g', 'P',
    'r', 'o', 't', 'o', 'P', '\001', 'Z', 'B', 'g', 'i', 't', 'h',
    'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n',
    't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e',
    'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/',
    'c', 'o', 'r', 'e', '/', 'v', '3', ';', 'c', 'o', 'r', 'e',
    'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006',
    'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[7] = {
    &envoy_config_core_v3_base_proto_upbdefinit,
    &envoy_config_core_v3_extension_proto_upbdefinit,
    &google_protobuf_struct_proto_upbdefinit,
    &envoy_annotations_deprecation_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_core_v3_substitution_format_string_proto_upbdefinit = {
    deps,
    &envoy_config_core_v3_substitution_format_string_proto_upb_file_layout,
    "envoy/config/core/v3/substitution_format_string.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
