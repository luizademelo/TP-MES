
#include "upb/reflection/def.h"
#include "xds/core/v3/context_params.upbdefs.h"
#include "xds/core/v3/context_params.upb_minitable.h"

extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;

static const char descriptor[321] = {
    '\n', ' ', 'x', 'd', 's', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '/', 'c', 'o', 'n', 't', 'e', 'x', 't', '_', 'p', 'a',
    'r', 'a', 'm', 's', '.', 'p', 'r', 'o', 't', 'o', '\022', '\013',
    'x', 'd', 's', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '\032',
    '\037', 'x', 'd', 's', '/', 'a', 'n', 'n', 'o', 't', 'a', 't',
    'i', 'o', 'n', 's', '/', 'v', '3', '/', 's', 't', 'a', 't',
    'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\"', '\212', '\001', '\n',
    '\r', 'C', 'o', 'n', 't', 'e', 'x', 't', 'P', 'a', 'r', 'a',
    'm', 's', '\022', '>', '\n', '\006', 'p', 'a', 'r', 'a', 'm', 's',
    '\030', '\001', ' ', '\003', '(', '\013', '2', '&', '.', 'x', 'd', 's',
    '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'C', 'o', 'n',
    't', 'e', 'x', 't', 'P', 'a', 'r', 'a', 'm', 's', '.', 'P',
    'a', 'r', 'a', 'm', 's', 'E', 'n', 't', 'r', 'y', 'R', '\006',
    'p', 'a', 'r', 'a', 'm', 's', '\032', '9', '\n', '\013', 'P', 'a',
    'r', 'a', 'm', 's', 'E', 'n', 't', 'r', 'y', '\022', '\020', '\n',
    '\003', 'k', 'e', 'y', '\030', '\001', ' ', '\001', '(', '\t', 'R', '\003',
    'k', 'e', 'y', '\022', '\024', '\n', '\005', 'v', 'a', 'l', 'u', 'e',
    '\030', '\002', ' ', '\001', '(', '\t', 'R', '\005', 'v', 'a', 'l', 'u',
    'e', ':', '\002', '8', '\001', 'B', 'Z', '\n', '\026', 'c', 'o', 'm',
    '.', 'g', 'i', 't', 'h', 'u', 'b', '.', 'x', 'd', 's', '.',
    'c', 'o', 'r', 'e', '.', 'v', '3', 'B', '\022', 'C', 'o', 'n',
    't', 'e', 'x', 't', 'P', 'a', 'r', 'a', 'm', 's', 'P', 'r',
    'o', 't', 'o', 'P', '\001', 'Z', '\"', 'g', 'i', 't', 'h', 'u',
    'b', '.', 'c', 'o', 'm', '/', 'c', 'n', 'c', 'f', '/', 'x',
    'd', 's', '/', 'g', 'o', '/', 'x', 'd', 's', '/', 'c', 'o',
    'r', 'e', '/', 'v', '3', '\322', '\306', '\244', '\341', '\006', '\002', '\010',
    '\001', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &xds_annotations_v3_status_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_core_v3_context_params_proto_upbdefinit = {
    deps,
    &xds_core_v3_context_params_proto_upb_file_layout,
    "xds/core/v3/context_params.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
