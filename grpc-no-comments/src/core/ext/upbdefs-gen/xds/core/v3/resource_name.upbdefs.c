
#include "upb/reflection/def.h"
#include "xds/core/v3/resource_name.upbdefs.h"
#include "xds/core/v3/resource_name.upb_minitable.h"

extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;
extern _upb_DefPool_Init xds_core_v3_context_params_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[400] = {
    '\n', '\037', 'x', 'd', 's', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '/', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_', 'n',
    'a', 'm', 'e', '.', 'p', 'r', 'o', 't', 'o', '\022', '\013', 'x',
    'd', 's', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '\032', '\037',
    'x', 'd', 's', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 's', '/', 'v', '3', '/', 's', 't', 'a', 't', 'u',
    's', '.', 'p', 'r', 'o', 't', 'o', '\032', ' ', 'x', 'd', 's',
    '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'c', 'o', 'n',
    't', 'e', 'x', 't', '_', 'p', 'a', 'r', 'a', 'm', 's', '.',
    'p', 'r', 'o', 't', 'o', '\032', '\027', 'v', 'a', 'l', 'i', 'd',
    'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e',
    '.', 'p', 'r', 'o', 't', 'o', '\"', '\240', '\001', '\n', '\014', 'R',
    'e', 's', 'o', 'u', 'r', 'c', 'e', 'N', 'a', 'm', 'e', '\022',
    '\016', '\n', '\002', 'i', 'd', '\030', '\001', ' ', '\001', '(', '\t', 'R',
    '\002', 'i', 'd', '\022', '\034', '\n', '\t', 'a', 'u', 't', 'h', 'o',
    'r', 'i', 't', 'y', '\030', '\002', ' ', '\001', '(', '\t', 'R', '\t',
    'a', 'u', 't', 'h', 'o', 'r', 'i', 't', 'y', '\022', ',', '\n',
    '\r', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_', 't', 'y',
    'p', 'e', '\030', '\003', ' ', '\001', '(', '\t', 'B', '\007', '\372', 'B',
    '\004', 'r', '\002', '\020', '\001', 'R', '\014', 'r', 'e', 's', 'o', 'u',
    'r', 'c', 'e', 'T', 'y', 'p', 'e', '\022', '4', '\n', '\007', 'c',
    'o', 'n', 't', 'e', 'x', 't', '\030', '\004', ' ', '\001', '(', '\013',
    '2', '\032', '.', 'x', 'd', 's', '.', 'c', 'o', 'r', 'e', '.',
    'v', '3', '.', 'C', 'o', 'n', 't', 'e', 'x', 't', 'P', 'a',
    'r', 'a', 'm', 's', 'R', '\007', 'c', 'o', 'n', 't', 'e', 'x',
    't', 'B', 'Y', '\n', '\026', 'c', 'o', 'm', '.', 'g', 'i', 't',
    'h', 'u', 'b', '.', 'x', 'd', 's', '.', 'c', 'o', 'r', 'e',
    '.', 'v', '3', 'B', '\021', 'R', 'e', 's', 'o', 'u', 'r', 'c',
    'e', 'N', 'a', 'm', 'e', 'P', 'r', 'o', 't', 'o', 'P', '\001',
    'Z', '\"', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm',
    '/', 'c', 'n', 'c', 'f', '/', 'x', 'd', 's', '/', 'g', 'o',
    '/', 'x', 'd', 's', '/', 'c', 'o', 'r', 'e', '/', 'v', '3',
    '\322', '\306', '\244', '\341', '\006', '\002', '\010', '\001', 'b', '\006', 'p', 'r',
    'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &xds_annotations_v3_status_proto_upbdefinit,
    &xds_core_v3_context_params_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_core_v3_resource_name_proto_upbdefinit = {
    deps,
    &xds_core_v3_resource_name_proto_upb_file_layout,
    "xds/core/v3/resource_name.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
