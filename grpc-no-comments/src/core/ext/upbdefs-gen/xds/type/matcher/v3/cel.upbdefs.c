
#include "upb/reflection/def.h"
#include "xds/type/matcher/v3/cel.upbdefs.h"
#include "xds/type/matcher/v3/cel.upb_minitable.h"

extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;
extern _upb_DefPool_Init xds_type_v3_cel_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[356] = {
    '\n', '\035', 'x', 'd', 's', '/', 't', 'y', 'p', 'e', '/', 'm',
    'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3', '/', 'c', 'e',
    'l', '.', 'p', 'r', 'o', 't', 'o', '\022', '\023', 'x', 'd', 's',
    '.', 't', 'y', 'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e',
    'r', '.', 'v', '3', '\032', '\037', 'x', 'd', 's', '/', 'a', 'n',
    'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 'v', '3',
    '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't',
    'o', '\032', '\025', 'x', 'd', 's', '/', 't', 'y', 'p', 'e', '/',
    'v', '3', '/', 'c', 'e', 'l', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v',
    'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't',
    'o', '\"', 's', '\n', '\n', 'C', 'e', 'l', 'M', 'a', 't', 'c',
    'h', 'e', 'r', '\022', 'C', '\n', '\n', 'e', 'x', 'p', 'r', '_',
    'm', 'a', 't', 'c', 'h', '\030', '\001', ' ', '\001', '(', '\013', '2',
    '\032', '.', 'x', 'd', 's', '.', 't', 'y', 'p', 'e', '.', 'v',
    '3', '.', 'C', 'e', 'l', 'E', 'x', 'p', 'r', 'e', 's', 's',
    'i', 'o', 'n', 'B', '\010', '\372', 'B', '\005', '\212', '\001', '\002', '\020',
    '\001', 'R', '\t', 'e', 'x', 'p', 'r', 'M', 'a', 't', 'c', 'h',
    '\022', ' ', '\n', '\013', 'd', 'e', 's', 'c', 'r', 'i', 'p', 't',
    'i', 'o', 'n', '\030', '\002', ' ', '\001', '(', '\t', 'R', '\013', 'd',
    'e', 's', 'c', 'r', 'i', 'p', 't', 'i', 'o', 'n', 'B', '`',
    '\n', '\036', 'c', 'o', 'm', '.', 'g', 'i', 't', 'h', 'u', 'b',
    '.', 'x', 'd', 's', '.', 't', 'y', 'p', 'e', '.', 'm', 'a',
    't', 'c', 'h', 'e', 'r', '.', 'v', '3', 'B', '\010', 'C', 'e',
    'l', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', '*', 'g', 'i',
    't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'c', 'n', 'c',
    'f', '/', 'x', 'd', 's', '/', 'g', 'o', '/', 'x', 'd', 's',
    '/', 't', 'y', 'p', 'e', '/', 'm', 'a', 't', 'c', 'h', 'e',
    'r', '/', 'v', '3', '\322', '\306', '\244', '\341', '\006', '\002', '\010', '\001',
    'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &xds_annotations_v3_status_proto_upbdefinit,
    &xds_type_v3_cel_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_type_matcher_v3_cel_proto_upbdefinit = {
    deps,
    &xds_type_matcher_v3_cel_proto_upb_file_layout,
    "xds/type/matcher/v3/cel.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
