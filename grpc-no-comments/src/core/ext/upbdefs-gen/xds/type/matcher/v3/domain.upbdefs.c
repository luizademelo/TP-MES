
#include "upb/reflection/def.h"
#include "xds/type/matcher/v3/domain.upbdefs.h"
#include "xds/type/matcher/v3/domain.upb_minitable.h"

extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;
extern _upb_DefPool_Init xds_type_matcher_v3_matcher_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[503] = {
    '\n', ' ', 'x', 'd', 's', '/', 't', 'y', 'p', 'e', '/', 'm',
    'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3', '/', 'd', 'o',
    'm', 'a', 'i', 'n', '.', 'p', 'r', 'o', 't', 'o', '\022', '\023',
    'x', 'd', 's', '.', 't', 'y', 'p', 'e', '.', 'm', 'a', 't',
    'c', 'h', 'e', 'r', '.', 'v', '3', '\032', '\037', 'x', 'd', 's',
    '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '/', 'v', '3', '/', 's', 't', 'a', 't', 'u', 's', '.', 'p',
    'r', 'o', 't', 'o', '\032', '!', 'x', 'd', 's', '/', 't', 'y',
    'p', 'e', '/', 'm', 'a', 't', 'c', 'h', 'e', 'r', '/', 'v',
    '3', '/', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'p', 'r',
    'o', 't', 'o', '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't',
    'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p',
    'r', 'o', 't', 'o', '\"', '\350', '\001', '\n', '\021', 'S', 'e', 'r',
    'v', 'e', 'r', 'N', 'a', 'm', 'e', 'M', 'a', 't', 'c', 'h',
    'e', 'r', '\022', ']', '\n', '\017', 'd', 'o', 'm', 'a', 'i', 'n',
    '_', 'm', 'a', 't', 'c', 'h', 'e', 'r', 's', '\030', '\001', ' ',
    '\003', '(', '\013', '2', '4', '.', 'x', 'd', 's', '.', 't', 'y',
    'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'v',
    '3', '.', 'S', 'e', 'r', 'v', 'e', 'r', 'N', 'a', 'm', 'e',
    'M', 'a', 't', 'c', 'h', 'e', 'r', '.', 'D', 'o', 'm', 'a',
    'i', 'n', 'M', 'a', 't', 'c', 'h', 'e', 'r', 'R', '\016', 'd',
    'o', 'm', 'a', 'i', 'n', 'M', 'a', 't', 'c', 'h', 'e', 'r',
    's', '\032', 't', '\n', '\r', 'D', 'o', 'm', 'a', 'i', 'n', 'M',
    'a', 't', 'c', 'h', 'e', 'r', '\022', '\"', '\n', '\007', 'd', 'o',
    'm', 'a', 'i', 'n', 's', '\030', '\001', ' ', '\003', '(', '\t', 'B',
    '\010', '\372', 'B', '\005', '\222', '\001', '\002', '\010', '\001', 'R', '\007', 'd',
    'o', 'm', 'a', 'i', 'n', 's', '\022', '?', '\n', '\010', 'o', 'n',
    '_', 'm', 'a', 't', 'c', 'h', '\030', '\002', ' ', '\001', '(', '\013',
    '2', '$', '.', 'x', 'd', 's', '.', 't', 'y', 'p', 'e', '.',
    'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'v', '3', '.', 'M',
    'a', 't', 'c', 'h', 'e', 'r', '.', 'O', 'n', 'M', 'a', 't',
    'c', 'h', 'R', '\007', 'o', 'n', 'M', 'a', 't', 'c', 'h', 'B',
    'n', '\n', '\036', 'c', 'o', 'm', '.', 'g', 'i', 't', 'h', 'u',
    'b', '.', 'x', 'd', 's', '.', 't', 'y', 'p', 'e', '.', 'm',
    'a', 't', 'c', 'h', 'e', 'r', '.', 'v', '3', 'B', '\026', 'S',
    'e', 'r', 'v', 'e', 'r', 'N', 'a', 'm', 'e', 'M', 'a', 't',
    'c', 'h', 'e', 'r', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z',
    '*', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/',
    'c', 'n', 'c', 'f', '/', 'x', 'd', 's', '/', 'g', 'o', '/',
    'x', 'd', 's', '/', 't', 'y', 'p', 'e', '/', 'm', 'a', 't',
    'c', 'h', 'e', 'r', '/', 'v', '3', '\322', '\306', '\244', '\341', '\006',
    '\002', '\010', '\001', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &xds_annotations_v3_status_proto_upbdefinit,
    &xds_type_matcher_v3_matcher_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_type_matcher_v3_domain_proto_upbdefinit = {
    deps,
    &xds_type_matcher_v3_domain_proto_upb_file_layout,
    "xds/type/matcher/v3/domain.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
