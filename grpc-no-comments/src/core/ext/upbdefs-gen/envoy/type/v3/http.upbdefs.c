
#include "upb/reflection/def.h"
#include "envoy/type/v3/http.upbdefs.h"
#include "envoy/type/v3/http.upb_minitable.h"

extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;

static const char descriptor[245] = {
    '\n', '\030', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'v', '3', '/', 'h', 't', 't', 'p', '.', 'p', 'r', 'o',
    't', 'o', '\022', '\r', 'e', 'n', 'v', 'o', 'y', '.', 't', 'y',
    'p', 'e', '.', 'v', '3', '\032', '\035', 'u', 'd', 'p', 'a', '/',
    'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/',
    's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o',
    '*', '2', '\n', '\017', 'C', 'o', 'd', 'e', 'c', 'C', 'l', 'i',
    'e', 'n', 't', 'T', 'y', 'p', 'e', '\022', '\t', '\n', '\005', 'H',
    'T', 'T', 'P', '1', '\020', '\000', '\022', '\t', '\n', '\005', 'H', 'T',
    'T', 'P', '2', '\020', '\001', '\022', '\t', '\n', '\005', 'H', 'T', 'T',
    'P', '3', '\020', '\002', 'B', 'o', '\n', '\033', 'i', 'o', '.', 'e',
    'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n',
    'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'v', '3', 'B',
    '\t', 'H', 't', 't', 'p', 'P', 'r', 'o', 't', 'o', 'P', '\001',
    'Z', ';', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm',
    '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/',
    'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p',
    'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 't',
    'y', 'p', 'e', '/', 'v', '3', ';', 't', 'y', 'p', 'e', 'v',
    '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p',
    'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &udpa_annotations_status_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_type_v3_http_proto_upbdefinit = {
    deps,
    &envoy_type_v3_http_proto_upb_file_layout,
    "envoy/type/v3/http.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
