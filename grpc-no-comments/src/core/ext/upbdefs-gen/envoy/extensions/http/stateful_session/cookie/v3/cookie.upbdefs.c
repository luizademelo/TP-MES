
#include "upb/reflection/def.h"
#include "envoy/extensions/http/stateful_session/cookie/v3/cookie.upbdefs.h"
#include "envoy/extensions/http/stateful_session/cookie/v3/cookie.upb_minitable.h"

extern _upb_DefPool_Init envoy_type_http_v3_cookie_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[487] = {
    '\n', '=', 'e', 'n', 'v', 'o', 'y', '/', 'e', 'x', 't', 'e',
    'n', 's', 'i', 'o', 'n', 's', '/', 'h', 't', 't', 'p', '/',
    's', 't', 'a', 't', 'e', 'f', 'u', 'l', '_', 's', 'e', 's',
    's', 'i', 'o', 'n', '/', 'c', 'o', 'o', 'k', 'i', 'e', '/',
    'v', '3', '/', 'c', 'o', 'o', 'k', 'i', 'e', '.', 'p', 'r',
    'o', 't', 'o', '\022', '0', 'e', 'n', 'v', 'o', 'y', '.', 'e',
    'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 's', '.', 'h', 't',
    't', 'p', '.', 's', 't', 'a', 't', 'e', 'f', 'u', 'l', '_',
    's', 'e', 's', 's', 'i', 'o', 'n', '.', 'c', 'o', 'o', 'k',
    'i', 'e', '.', 'v', '3', '\032', '\037', 'e', 'n', 'v', 'o', 'y',
    '/', 't', 'y', 'p', 'e', '/', 'h', 't', 't', 'p', '/', 'v',
    '3', '/', 'c', 'o', 'o', 'k', 'i', 'e', '.', 'p', 'r', 'o',
    't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a',
    't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027', 'v',
    'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i',
    'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"', 'W',
    '\n', '\027', 'C', 'o', 'o', 'k', 'i', 'e', 'B', 'a', 's', 'e',
    'd', 'S', 'e', 's', 's', 'i', 'o', 'n', 'S', 't', 'a', 't',
    'e', '\022', '<', '\n', '\006', 'c', 'o', 'o', 'k', 'i', 'e', '\030',
    '\001', ' ', '\001', '(', '\013', '2', '\032', '.', 'e', 'n', 'v', 'o',
    'y', '.', 't', 'y', 'p', 'e', '.', 'h', 't', 't', 'p', '.',
    'v', '3', '.', 'C', 'o', 'o', 'k', 'i', 'e', 'B', '\010', '\372',
    'B', '\005', '\212', '\001', '\002', '\020', '\001', 'R', '\006', 'c', 'o', 'o',
    'k', 'i', 'e', 'B', '\271', '\001', '\n', '>', 'i', 'o', '.', 'e',
    'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o',
    'n', 's', '.', 'h', 't', 't', 'p', '.', 's', 't', 'a', 't',
    'e', 'f', 'u', 'l', '_', 's', 'e', 's', 's', 'i', 'o', 'n',
    '.', 'c', 'o', 'o', 'k', 'i', 'e', '.', 'v', '3', 'B', '\013',
    'C', 'o', 'o', 'k', 'i', 'e', 'P', 'r', 'o', 't', 'o', 'P',
    '\001', 'Z', '`', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o',
    'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y',
    '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-',
    'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/',
    'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 's', '/', 'h',
    't', 't', 'p', '/', 's', 't', 'a', 't', 'e', 'f', 'u', 'l',
    '_', 's', 'e', 's', 's', 'i', 'o', 'n', '/', 'c', 'o', 'o',
    'k', 'i', 'e', '/', 'v', '3', ';', 'c', 'o', 'o', 'k', 'i',
    'e', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b',
    '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &envoy_type_http_v3_cookie_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_extensions_http_stateful_session_cookie_v3_cookie_proto_upbdefinit = {
    deps,
    &envoy_extensions_http_stateful_session_cookie_v3_cookie_proto_upb_file_layout,
    "envoy/extensions/http/stateful_session/cookie/v3/cookie.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
