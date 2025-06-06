
#include "upb/reflection/def.h"
#include "envoy/admin/v3/tap.upbdefs.h"
#include "envoy/admin/v3/tap.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_tap_v3_common_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[455] = {
    '\n', '\030', 'e', 'n', 'v', 'o', 'y', '/', 'a', 'd', 'm', 'i',
    'n', '/', 'v', '3', '/', 't', 'a', 'p', '.', 'p', 'r', 'o',
    't', 'o', '\022', '\016', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'd',
    'm', 'i', 'n', '.', 'v', '3', '\032', ' ', 'e', 'n', 'v', 'o',
    'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 't', 'a', 'p',
    '/', 'v', '3', '/', 'c', 'o', 'm', 'm', 'o', 'n', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a',
    'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's',
    't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i', 'o',
    'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027',
    'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l',
    'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"',
    '\242', '\001', '\n', '\n', 'T', 'a', 'p', 'R', 'e', 'q', 'u', 'e',
    's', 't', '\022', '$', '\n', '\t', 'c', 'o', 'n', 'f', 'i', 'g',
    '_', 'i', 'd', '\030', '\001', ' ', '\001', '(', '\t', 'B', '\007', '\372',
    'B', '\004', 'r', '\002', '\020', '\001', 'R', '\010', 'c', 'o', 'n', 'f',
    'i', 'g', 'I', 'd', '\022', 'G', '\n', '\n', 't', 'a', 'p', '_',
    'c', 'o', 'n', 'f', 'i', 'g', '\030', '\002', ' ', '\001', '(', '\013',
    '2', '\036', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 't', 'a', 'p', '.', 'v', '3', '.', 'T',
    'a', 'p', 'C', 'o', 'n', 'f', 'i', 'g', 'B', '\010', '\372', 'B',
    '\005', '\212', '\001', '\002', '\020', '\001', 'R', '\t', 't', 'a', 'p', 'C',
    'o', 'n', 'f', 'i', 'g', ':', '%', '\232', '\305', '\210', '\036', ' ',
    '\n', '\036', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'd', 'm', 'i',
    'n', '.', 'v', '2', 'a', 'l', 'p', 'h', 'a', '.', 'T', 'a',
    'p', 'R', 'e', 'q', 'u', 'e', 's', 't', 'B', 'q', '\n', '\034',
    'i', 'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x',
    'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'd', 'm', 'i',
    'n', '.', 'v', '3', 'B', '\010', 'T', 'a', 'p', 'P', 'r', 'o',
    't', 'o', 'P', '\001', 'Z', '=', 'g', 'i', 't', 'h', 'u', 'b',
    '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r',
    'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r',
    'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v',
    'o', 'y', '/', 'a', 'd', 'm', 'i', 'n', '/', 'v', '3', ';',
    'a', 'd', 'm', 'i', 'n', 'v', '3', '\272', '\200', '\310', '\321', '\006',
    '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[5] = {
    &envoy_config_tap_v3_common_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_admin_v3_tap_proto_upbdefinit = {
    deps,
    &envoy_admin_v3_tap_proto_upb_file_layout,
    "envoy/admin/v3/tap.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
