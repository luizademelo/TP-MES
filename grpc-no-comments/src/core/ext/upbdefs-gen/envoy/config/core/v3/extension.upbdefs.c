
#include "upb/reflection/def.h"
#include "envoy/config/core/v3/extension.upbdefs.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[404] = {
    '\n', '$', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'e',
    'x', 't', 'e', 'n', 's', 'i', 'o', 'n', '.', 'p', 'r', 'o',
    't', 'o', '\022', '\024', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o',
    'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3',
    '\032', '\031', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '/', 'a', 'n', 'y', '.', 'p', 'r',
    'o', 't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n',
    'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's', 't',
    'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027',
    'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l',
    'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"',
    'v', '\n', '\024', 'T', 'y', 'p', 'e', 'd', 'E', 'x', 't', 'e',
    'n', 's', 'i', 'o', 'n', 'C', 'o', 'n', 'f', 'i', 'g', '\022',
    '\033', '\n', '\004', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001', '(',
    '\t', 'B', '\007', '\372', 'B', '\004', 'r', '\002', '\020', '\001', 'R', '\004',
    'n', 'a', 'm', 'e', '\022', 'A', '\n', '\014', 't', 'y', 'p', 'e',
    'd', '_', 'c', 'o', 'n', 'f', 'i', 'g', '\030', '\002', ' ', '\001',
    '(', '\013', '2', '\024', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'A', 'n', 'y',
    'B', '\010', '\372', 'B', '\005', '\242', '\001', '\002', '\010', '\001', 'R', '\013',
    't', 'y', 'p', 'e', 'd', 'C', 'o', 'n', 'f', 'i', 'g', 'B',
    '\202', '\001', '\n', '\"', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.',
    'v', '3', 'B', '\016', 'E', 'x', 't', 'e', 'n', 's', 'i', 'o',
    'n', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', 'B', 'g', 'i',
    't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v',
    'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c',
    'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e',
    '/', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i',
    'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', ';', 'c', 'o',
    'r', 'e', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002',
    'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &google_protobuf_any_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_core_v3_extension_proto_upbdefinit = {
    deps,
    &envoy_config_core_v3_extension_proto_upb_file_layout,
    "envoy/config/core/v3/extension.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
