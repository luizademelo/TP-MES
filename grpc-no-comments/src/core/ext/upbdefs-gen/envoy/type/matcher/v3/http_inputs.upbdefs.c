
#include "upb/reflection/def.h"
#include "envoy/type/matcher/v3/http_inputs.upbdefs.h"
#include "envoy/type/matcher/v3/http_inputs.upb_minitable.h"

extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[656] = {
    '\n', '\'', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'm', 'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3', '/',
    'h', 't', 't', 'p', '_', 'i', 'n', 'p', 'u', 't', 's', '.',
    'p', 'r', 'o', 't', 'o', '\022', '\025', 'e', 'n', 'v', 'o', 'y',
    '.', 't', 'y', 'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e',
    'r', '.', 'v', '3', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a',
    'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's',
    't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a',
    'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o',
    '\"', 'K', '\n', '\033', 'H', 't', 't', 'p', 'R', 'e', 'q', 'u',
    'e', 's', 't', 'H', 'e', 'a', 'd', 'e', 'r', 'M', 'a', 't',
    'c', 'h', 'I', 'n', 'p', 'u', 't', '\022', ',', '\n', '\013', 'h',
    'e', 'a', 'd', 'e', 'r', '_', 'n', 'a', 'm', 'e', '\030', '\001',
    ' ', '\001', '(', '\t', 'B', '\013', '\372', 'B', '\010', 'r', '\006', '\300',
    '\001', '\001', '\310', '\001', '\000', 'R', '\n', 'h', 'e', 'a', 'd', 'e',
    'r', 'N', 'a', 'm', 'e', '\"', 'L', '\n', '\034', 'H', 't', 't',
    'p', 'R', 'e', 'q', 'u', 'e', 's', 't', 'T', 'r', 'a', 'i',
    'l', 'e', 'r', 'M', 'a', 't', 'c', 'h', 'I', 'n', 'p', 'u',
    't', '\022', ',', '\n', '\013', 'h', 'e', 'a', 'd', 'e', 'r', '_',
    'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001', '(', '\t', 'B', '\013',
    '\372', 'B', '\010', 'r', '\006', '\300', '\001', '\001', '\310', '\001', '\000', 'R',
    '\n', 'h', 'e', 'a', 'd', 'e', 'r', 'N', 'a', 'm', 'e', '\"',
    'L', '\n', '\034', 'H', 't', 't', 'p', 'R', 'e', 's', 'p', 'o',
    'n', 's', 'e', 'H', 'e', 'a', 'd', 'e', 'r', 'M', 'a', 't',
    'c', 'h', 'I', 'n', 'p', 'u', 't', '\022', ',', '\n', '\013', 'h',
    'e', 'a', 'd', 'e', 'r', '_', 'n', 'a', 'm', 'e', '\030', '\001',
    ' ', '\001', '(', '\t', 'B', '\013', '\372', 'B', '\010', 'r', '\006', '\300',
    '\001', '\001', '\310', '\001', '\000', 'R', '\n', 'h', 'e', 'a', 'd', 'e',
    'r', 'N', 'a', 'm', 'e', '\"', 'M', '\n', '\035', 'H', 't', 't',
    'p', 'R', 'e', 's', 'p', 'o', 'n', 's', 'e', 'T', 'r', 'a',
    'i', 'l', 'e', 'r', 'M', 'a', 't', 'c', 'h', 'I', 'n', 'p',
    'u', 't', '\022', ',', '\n', '\013', 'h', 'e', 'a', 'd', 'e', 'r',
    '_', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001', '(', '\t', 'B',
    '\013', '\372', 'B', '\010', 'r', '\006', '\300', '\001', '\001', '\310', '\001', '\000',
    'R', '\n', 'h', 'e', 'a', 'd', 'e', 'r', 'N', 'a', 'm', 'e',
    '\"', 'K', '\n', '\037', 'H', 't', 't', 'p', 'R', 'e', 'q', 'u',
    'e', 's', 't', 'Q', 'u', 'e', 'r', 'y', 'P', 'a', 'r', 'a',
    'm', 'M', 'a', 't', 'c', 'h', 'I', 'n', 'p', 'u', 't', '\022',
    '(', '\n', '\013', 'q', 'u', 'e', 'r', 'y', '_', 'p', 'a', 'r',
    'a', 'm', '\030', '\001', ' ', '\001', '(', '\t', 'B', '\007', '\372', 'B',
    '\004', 'r', '\002', '\020', '\001', 'R', '\n', 'q', 'u', 'e', 'r', 'y',
    'P', 'a', 'r', 'a', 'm', 'B', '\210', '\001', '\n', '#', 'i', 'o',
    '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.',
    'e', 'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'm',
    'a', 't', 'c', 'h', 'e', 'r', '.', 'v', '3', 'B', '\017', 'H',
    't', 't', 'p', 'I', 'n', 'p', 'u', 't', 's', 'P', 'r', 'o',
    't', 'o', 'P', '\001', 'Z', 'F', 'g', 'i', 't', 'h', 'u', 'b',
    '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r',
    'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r',
    'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v',
    'o', 'y', '/', 't', 'y', 'p', 'e', '/', 'm', 'a', 't', 'c',
    'h', 'e', 'r', '/', 'v', '3', ';', 'm', 'a', 't', 'c', 'h',
    'e', 'r', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002',
    'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[3] = {
    &udpa_annotations_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_type_matcher_v3_http_inputs_proto_upbdefinit = {
    deps,
    &envoy_type_matcher_v3_http_inputs_proto_upb_file_layout,
    "envoy/type/matcher/v3/http_inputs.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
