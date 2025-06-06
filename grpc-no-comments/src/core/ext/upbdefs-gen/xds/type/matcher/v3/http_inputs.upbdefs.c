
#include "upb/reflection/def.h"
#include "xds/type/matcher/v3/http_inputs.upbdefs.h"
#include "xds/type/matcher/v3/http_inputs.upb_minitable.h"

extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;

static const char descriptor[237] = {
    '\n', '%', 'x', 'd', 's', '/', 't', 'y', 'p', 'e', '/', 'm',
    'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3', '/', 'h', 't',
    't', 'p', '_', 'i', 'n', 'p', 'u', 't', 's', '.', 'p', 'r',
    'o', 't', 'o', '\022', '\023', 'x', 'd', 's', '.', 't', 'y', 'p',
    'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'v', '3',
    '\032', '\037', 'x', 'd', 's', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'v', '3', '/', 's', 't', 'a',
    't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\"', '\035', '\n',
    '\033', 'H', 't', 't', 'p', 'A', 't', 't', 'r', 'i', 'b', 'u',
    't', 'e', 's', 'C', 'e', 'l', 'M', 'a', 't', 'c', 'h', 'I',
    'n', 'p', 'u', 't', 'B', 'g', '\n', '\036', 'c', 'o', 'm', '.',
    'g', 'i', 't', 'h', 'u', 'b', '.', 'x', 'd', 's', '.', 't',
    'y', 'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.',
    'v', '3', 'B', '\017', 'H', 't', 't', 'p', 'I', 'n', 'p', 'u',
    't', 's', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', '*', 'g',
    'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'c', 'n',
    'c', 'f', '/', 'x', 'd', 's', '/', 'g', 'o', '/', 'x', 'd',
    's', '/', 't', 'y', 'p', 'e', '/', 'm', 'a', 't', 'c', 'h',
    'e', 'r', '/', 'v', '3', '\322', '\306', '\244', '\341', '\006', '\002', '\010',
    '\001', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &xds_annotations_v3_status_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_type_matcher_v3_http_inputs_proto_upbdefinit = {
    deps,
    &xds_type_matcher_v3_http_inputs_proto_upb_file_layout,
    "xds/type/matcher/v3/http_inputs.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
