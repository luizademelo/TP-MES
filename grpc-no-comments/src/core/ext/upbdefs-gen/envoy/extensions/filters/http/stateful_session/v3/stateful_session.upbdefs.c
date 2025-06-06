
#include "upb/reflection/def.h"
#include "envoy/extensions/filters/http/stateful_session/v3/stateful_session.upbdefs.h"
#include "envoy/extensions/filters/http/stateful_session/v3/stateful_session.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_extension_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[757] = {
    '\n', 'H', 'e', 'n', 'v', 'o', 'y', '/', 'e', 'x', 't', 'e',
    'n', 's', 'i', 'o', 'n', 's', '/', 'f', 'i', 'l', 't', 'e',
    'r', 's', '/', 'h', 't', 't', 'p', '/', 's', 't', 'a', 't',
    'e', 'f', 'u', 'l', '_', 's', 'e', 's', 's', 'i', 'o', 'n',
    '/', 'v', '3', '/', 's', 't', 'a', 't', 'e', 'f', 'u', 'l',
    '_', 's', 'e', 's', 's', 'i', 'o', 'n', '.', 'p', 'r', 'o',
    't', 'o', '\022', '1', 'e', 'n', 'v', 'o', 'y', '.', 'e', 'x',
    't', 'e', 'n', 's', 'i', 'o', 'n', 's', '.', 'f', 'i', 'l',
    't', 'e', 'r', 's', '.', 'h', 't', 't', 'p', '.', 's', 't',
    'a', 't', 'e', 'f', 'u', 'l', '_', 's', 'e', 's', 's', 'i',
    'o', 'n', '.', 'v', '3', '\032', '$', 'e', 'n', 'v', 'o', 'y',
    '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e',
    '/', 'v', '3', '/', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o',
    'n', '.', 'p', 'r', 'o', 't', 'o', '\032', '\035', 'u', 'd', 'p',
    'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n',
    's', '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o',
    't', 'o', '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e',
    '/', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r',
    'o', 't', 'o', '\"', 'z', '\n', '\017', 'S', 't', 'a', 't', 'e',
    'f', 'u', 'l', 'S', 'e', 's', 's', 'i', 'o', 'n', '\022', 'O',
    '\n', '\r', 's', 'e', 's', 's', 'i', 'o', 'n', '_', 's', 't',
    'a', 't', 'e', '\030', '\001', ' ', '\001', '(', '\013', '2', '*', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g',
    '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'T', 'y', 'p',
    'e', 'd', 'E', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 'C',
    'o', 'n', 'f', 'i', 'g', 'R', '\014', 's', 'e', 's', 's', 'i',
    'o', 'n', 'S', 't', 'a', 't', 'e', '\022', '\026', '\n', '\006', 's',
    't', 'r', 'i', 'c', 't', '\030', '\002', ' ', '\001', '(', '\010', 'R',
    '\006', 's', 't', 'r', 'i', 'c', 't', '\"', '\302', '\001', '\n', '\027',
    'S', 't', 'a', 't', 'e', 'f', 'u', 'l', 'S', 'e', 's', 's',
    'i', 'o', 'n', 'P', 'e', 'r', 'R', 'o', 'u', 't', 'e', '\022',
    '%', '\n', '\010', 'd', 'i', 's', 'a', 'b', 'l', 'e', 'd', '\030',
    '\001', ' ', '\001', '(', '\010', 'B', '\007', '\372', 'B', '\004', 'j', '\002',
    '\010', '\001', 'H', '\000', 'R', '\010', 'd', 'i', 's', 'a', 'b', 'l',
    'e', 'd', '\022', 'o', '\n', '\020', 's', 't', 'a', 't', 'e', 'f',
    'u', 'l', '_', 's', 'e', 's', 's', 'i', 'o', 'n', '\030', '\002',
    ' ', '\001', '(', '\013', '2', 'B', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 's', '.',
    'f', 'i', 'l', 't', 'e', 'r', 's', '.', 'h', 't', 't', 'p',
    '.', 's', 't', 'a', 't', 'e', 'f', 'u', 'l', '_', 's', 'e',
    's', 's', 'i', 'o', 'n', '.', 'v', '3', '.', 'S', 't', 'a',
    't', 'e', 'f', 'u', 'l', 'S', 'e', 's', 's', 'i', 'o', 'n',
    'H', '\000', 'R', '\017', 's', 't', 'a', 't', 'e', 'f', 'u', 'l',
    'S', 'e', 's', 's', 'i', 'o', 'n', 'B', '\017', '\n', '\010', 'o',
    'v', 'e', 'r', 'r', 'i', 'd', 'e', '\022', '\003', '\370', 'B', '\001',
    'B', '\316', '\001', '\n', '?', 'i', 'o', '.', 'e', 'n', 'v', 'o',
    'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 's', '.',
    'f', 'i', 'l', 't', 'e', 'r', 's', '.', 'h', 't', 't', 'p',
    '.', 's', 't', 'a', 't', 'e', 'f', 'u', 'l', '_', 's', 'e',
    's', 's', 'i', 'o', 'n', '.', 'v', '3', 'B', '\024', 'S', 't',
    'a', 't', 'e', 'f', 'u', 'l', 'S', 'e', 's', 's', 'i', 'o',
    'n', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', 'k', 'g', 'i',
    't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v',
    'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c',
    'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e',
    '/', 'e', 'n', 'v', 'o', 'y', '/', 'e', 'x', 't', 'e', 'n',
    's', 'i', 'o', 'n', 's', '/', 'f', 'i', 'l', 't', 'e', 'r',
    's', '/', 'h', 't', 't', 'p', '/', 's', 't', 'a', 't', 'e',
    'f', 'u', 'l', '_', 's', 'e', 's', 's', 'i', 'o', 'n', '/',
    'v', '3', ';', 's', 't', 'a', 't', 'e', 'f', 'u', 'l', '_',
    's', 'e', 's', 's', 'i', 'o', 'n', 'v', '3', '\272', '\200', '\310',
    '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o',
    '3',
};

static _upb_DefPool_Init *deps[4] = {
    &envoy_config_core_v3_extension_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_extensions_filters_http_stateful_session_v3_stateful_session_proto_upbdefinit = {
    deps,
    &envoy_extensions_filters_http_stateful_session_v3_stateful_session_proto_upb_file_layout,
    "envoy/extensions/filters/http/stateful_session/v3/stateful_session.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
