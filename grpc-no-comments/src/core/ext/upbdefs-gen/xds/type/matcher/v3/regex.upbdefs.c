
#include "upb/reflection/def.h"
#include "xds/type/matcher/v3/regex.upbdefs.h"
#include "xds/type/matcher/v3/regex.upb_minitable.h"

extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[348] = {
    '\n', '\037', 'x', 'd', 's', '/', 't', 'y', 'p', 'e', '/', 'm',
    'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3', '/', 'r', 'e',
    'g', 'e', 'x', '.', 'p', 'r', 'o', 't', 'o', '\022', '\023', 'x',
    'd', 's', '.', 't', 'y', 'p', 'e', '.', 'm', 'a', 't', 'c',
    'h', 'e', 'r', '.', 'v', '3', '\032', '\027', 'v', 'a', 'l', 'i',
    'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't',
    'e', '.', 'p', 'r', 'o', 't', 'o', '\"', '\246', '\001', '\n', '\014',
    'R', 'e', 'g', 'e', 'x', 'M', 'a', 't', 'c', 'h', 'e', 'r',
    '\022', 'V', '\n', '\n', 'g', 'o', 'o', 'g', 'l', 'e', '_', 'r',
    'e', '2', '\030', '\001', ' ', '\001', '(', '\013', '2', '+', '.', 'x',
    'd', 's', '.', 't', 'y', 'p', 'e', '.', 'm', 'a', 't', 'c',
    'h', 'e', 'r', '.', 'v', '3', '.', 'R', 'e', 'g', 'e', 'x',
    'M', 'a', 't', 'c', 'h', 'e', 'r', '.', 'G', 'o', 'o', 'g',
    'l', 'e', 'R', 'E', '2', 'B', '\010', '\372', 'B', '\005', '\212', '\001',
    '\002', '\020', '\001', 'H', '\000', 'R', '\t', 'g', 'o', 'o', 'g', 'l',
    'e', 'R', 'e', '2', '\022', '\035', '\n', '\005', 'r', 'e', 'g', 'e',
    'x', '\030', '\002', ' ', '\001', '(', '\t', 'B', '\007', '\372', 'B', '\004',
    'r', '\002', '\020', '\001', 'R', '\005', 'r', 'e', 'g', 'e', 'x', '\032',
    '\013', '\n', '\t', 'G', 'o', 'o', 'g', 'l', 'e', 'R', 'E', '2',
    'B', '\022', '\n', '\013', 'e', 'n', 'g', 'i', 'n', 'e', '_', 't',
    'y', 'p', 'e', '\022', '\003', '\370', 'B', '\001', 'B', 'Z', '\n', '\036',
    'c', 'o', 'm', '.', 'g', 'i', 't', 'h', 'u', 'b', '.', 'x',
    'd', 's', '.', 't', 'y', 'p', 'e', '.', 'm', 'a', 't', 'c',
    'h', 'e', 'r', '.', 'v', '3', 'B', '\n', 'R', 'e', 'g', 'e',
    'x', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', '*', 'g', 'i',
    't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'c', 'n', 'c',
    'f', '/', 'x', 'd', 's', '/', 'g', 'o', '/', 'x', 'd', 's',
    '/', 't', 'y', 'p', 'e', '/', 'm', 'a', 't', 'c', 'h', 'e',
    'r', '/', 'v', '3', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_type_matcher_v3_regex_proto_upbdefinit = {
    deps,
    &xds_type_matcher_v3_regex_proto_upb_file_layout,
    "xds/type/matcher/v3/regex.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
