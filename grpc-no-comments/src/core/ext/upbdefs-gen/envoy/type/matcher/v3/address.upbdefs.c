
#include "upb/reflection/def.h"
#include "envoy/type/matcher/v3/address.upbdefs.h"
#include "envoy/type/matcher/v3/address.upb_minitable.h"

extern _upb_DefPool_Init xds_core_v3_cidr_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;

static const char descriptor[325] = {
    '\n', '#', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'm', 'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3', '/',
    'a', 'd', 'd', 'r', 'e', 's', 's', '.', 'p', 'r', 'o', 't',
    'o', '\022', '\025', 'e', 'n', 'v', 'o', 'y', '.', 't', 'y', 'p',
    'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'v', '3',
    '\032', '\026', 'x', 'd', 's', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '/', 'c', 'i', 'd', 'r', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u',
    's', '.', 'p', 'r', 'o', 't', 'o', '\"', '@', '\n', '\016', 'A',
    'd', 'd', 'r', 'e', 's', 's', 'M', 'a', 't', 'c', 'h', 'e',
    'r', '\022', '.', '\n', '\006', 'r', 'a', 'n', 'g', 'e', 's', '\030',
    '\001', ' ', '\003', '(', '\013', '2', '\026', '.', 'x', 'd', 's', '.',
    'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'C', 'i', 'd', 'r',
    'R', 'a', 'n', 'g', 'e', 'R', '\006', 'r', 'a', 'n', 'g', 'e',
    's', 'B', '\205', '\001', '\n', '#', 'i', 'o', '.', 'e', 'n', 'v',
    'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o',
    'y', '.', 't', 'y', 'p', 'e', '.', 'm', 'a', 't', 'c', 'h',
    'e', 'r', '.', 'v', '3', 'B', '\014', 'A', 'd', 'd', 'r', 'e',
    's', 's', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', 'F', 'g',
    'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n',
    'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-',
    'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n',
    'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'm', 'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3', ';',
    'm', 'a', 't', 'c', 'h', 'e', 'r', 'v', '3', '\272', '\200', '\310',
    '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o',
    '3',
};

static _upb_DefPool_Init *deps[3] = {
    &xds_core_v3_cidr_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_type_matcher_v3_address_proto_upbdefinit = {
    deps,
    &envoy_type_matcher_v3_address_proto_upb_file_layout,
    "envoy/type/matcher/v3/address.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
