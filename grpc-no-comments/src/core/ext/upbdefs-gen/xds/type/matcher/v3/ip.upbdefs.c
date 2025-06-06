
#include "upb/reflection/def.h"
#include "xds/type/matcher/v3/ip.upbdefs.h"
#include "xds/type/matcher/v3/ip.upb_minitable.h"

extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;
extern _upb_DefPool_Init xds_core_v3_cidr_proto_upbdefinit;
extern _upb_DefPool_Init xds_type_matcher_v3_matcher_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[552] = {
    '\n', '\034', 'x', 'd', 's', '/', 't', 'y', 'p', 'e', '/', 'm',
    'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3', '/', 'i', 'p',
    '.', 'p', 'r', 'o', 't', 'o', '\022', '\023', 'x', 'd', 's', '.',
    't', 'y', 'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r',
    '.', 'v', '3', '\032', '\037', 'x', 'd', 's', '/', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 'v', '3', '/',
    's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\026', 'x', 'd', 's', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '/', 'c', 'i', 'd', 'r', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '!', 'x', 'd', 's', '/', 't', 'y', 'p', 'e', '/', 'm',
    'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3', '/', 'm', 'a',
    't', 'c', 'h', 'e', 'r', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a',
    'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o',
    '\"', '\215', '\002', '\n', '\t', 'I', 'P', 'M', 'a', 't', 'c', 'h',
    'e', 'r', '\022', 'T', '\n', '\016', 'r', 'a', 'n', 'g', 'e', '_',
    'm', 'a', 't', 'c', 'h', 'e', 'r', 's', '\030', '\001', ' ', '\003',
    '(', '\013', '2', '-', '.', 'x', 'd', 's', '.', 't', 'y', 'p',
    'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'v', '3',
    '.', 'I', 'P', 'M', 'a', 't', 'c', 'h', 'e', 'r', '.', 'I',
    'P', 'R', 'a', 'n', 'g', 'e', 'M', 'a', 't', 'c', 'h', 'e',
    'r', 'R', '\r', 'r', 'a', 'n', 'g', 'e', 'M', 'a', 't', 'c',
    'h', 'e', 'r', 's', '\032', '\251', '\001', '\n', '\016', 'I', 'P', 'R',
    'a', 'n', 'g', 'e', 'M', 'a', 't', 'c', 'h', 'e', 'r', '\022',
    '8', '\n', '\006', 'r', 'a', 'n', 'g', 'e', 's', '\030', '\001', ' ',
    '\003', '(', '\013', '2', '\026', '.', 'x', 'd', 's', '.', 'c', 'o',
    'r', 'e', '.', 'v', '3', '.', 'C', 'i', 'd', 'r', 'R', 'a',
    'n', 'g', 'e', 'B', '\010', '\372', 'B', '\005', '\222', '\001', '\002', '\010',
    '\001', 'R', '\006', 'r', 'a', 'n', 'g', 'e', 's', '\022', '?', '\n',
    '\010', 'o', 'n', '_', 'm', 'a', 't', 'c', 'h', '\030', '\002', ' ',
    '\001', '(', '\013', '2', '$', '.', 'x', 'd', 's', '.', 't', 'y',
    'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'v',
    '3', '.', 'M', 'a', 't', 'c', 'h', 'e', 'r', '.', 'O', 'n',
    'M', 'a', 't', 'c', 'h', 'R', '\007', 'o', 'n', 'M', 'a', 't',
    'c', 'h', '\022', '\034', '\n', '\t', 'e', 'x', 'c', 'l', 'u', 's',
    'i', 'v', 'e', '\030', '\003', ' ', '\001', '(', '\010', 'R', '\t', 'e',
    'x', 'c', 'l', 'u', 's', 'i', 'v', 'e', 'B', 'f', '\n', '\036',
    'c', 'o', 'm', '.', 'g', 'i', 't', 'h', 'u', 'b', '.', 'x',
    'd', 's', '.', 't', 'y', 'p', 'e', '.', 'm', 'a', 't', 'c',
    'h', 'e', 'r', '.', 'v', '3', 'B', '\016', 'I', 'P', 'M', 'a',
    't', 'c', 'h', 'e', 'r', 'P', 'r', 'o', 't', 'o', 'P', '\001',
    'Z', '*', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm',
    '/', 'c', 'n', 'c', 'f', '/', 'x', 'd', 's', '/', 'g', 'o',
    '/', 'x', 'd', 's', '/', 't', 'y', 'p', 'e', '/', 'm', 'a',
    't', 'c', 'h', 'e', 'r', '/', 'v', '3', '\322', '\306', '\244', '\341',
    '\006', '\002', '\010', '\001', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[5] = {
    &xds_annotations_v3_status_proto_upbdefinit,
    &xds_core_v3_cidr_proto_upbdefinit,
    &xds_type_matcher_v3_matcher_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_type_matcher_v3_ip_proto_upbdefinit = {
    deps,
    &xds_type_matcher_v3_ip_proto_upb_file_layout,
    "xds/type/matcher/v3/ip.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
