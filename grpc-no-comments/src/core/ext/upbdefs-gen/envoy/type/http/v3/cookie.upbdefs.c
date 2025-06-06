
#include "upb/reflection/def.h"
#include "envoy/type/http/v3/cookie.upbdefs.h"
#include "envoy/type/http/v3/cookie.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_duration_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[388] = {
    '\n', '\037', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'h', 't', 't', 'p', '/', 'v', '3', '/', 'c', 'o', 'o',
    'k', 'i', 'e', '.', 'p', 'r', 'o', 't', 'o', '\022', '\022', 'e',
    'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'h', 't',
    't', 'p', '.', 'v', '3', '\032', '\036', 'g', 'o', 'o', 'g', 'l',
    'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'd',
    'u', 'r', 'a', 't', 'i', 'o', 'n', '.', 'p', 'r', 'o', 't',
    'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o',
    't', 'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't',
    'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027', 'v', 'a',
    'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd',
    'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"', 'p', '\n',
    '\006', 'C', 'o', 'o', 'k', 'i', 'e', '\022', '\033', '\n', '\004', 'n',
    'a', 'm', 'e', '\030', '\001', ' ', '\001', '(', '\t', 'B', '\007', '\372',
    'B', '\004', 'r', '\002', '\020', '\001', 'R', '\004', 'n', 'a', 'm', 'e',
    '\022', '5', '\n', '\003', 't', 't', 'l', '\030', '\002', ' ', '\001', '(',
    '\013', '2', '\031', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p',
    'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'D', 'u', 'r', 'a',
    't', 'i', 'o', 'n', 'B', '\010', '\372', 'B', '\005', '\252', '\001', '\002',
    '2', '\000', 'R', '\003', 't', 't', 'l', '\022', '\022', '\n', '\004', 'p',
    'a', 't', 'h', '\030', '\003', ' ', '\001', '(', '\t', 'R', '\004', 'p',
    'a', 't', 'h', 'B', '{', '\n', ' ', 'i', 'o', '.', 'e', 'n',
    'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v',
    'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'h', 't', 't', 'p',
    '.', 'v', '3', 'B', '\013', 'C', 'o', 'o', 'k', 'i', 'e', 'P',
    'r', 'o', 't', 'o', 'P', '\001', 'Z', '@', 'g', 'i', 't', 'h',
    'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n',
    't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e',
    'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e', '/', 'h', 't',
    't', 'p', '/', 'v', '3', ';', 'h', 't', 't', 'p', 'v', '3',
    '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r',
    'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &google_protobuf_duration_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_type_http_v3_cookie_proto_upbdefinit = {
    deps,
    &envoy_type_http_v3_cookie_proto_upb_file_layout,
    "envoy/type/http/v3/cookie.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
