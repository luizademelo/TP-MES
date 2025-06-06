
#include "upb/reflection/def.h"
#include "xds/core/v3/extension.upbdefs.h"
#include "xds/core/v3/extension.upb_minitable.h"

extern _upb_DefPool_Init validate_validate_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;

static const char descriptor[302] = {
    '\n', '\033', 'x', 'd', 's', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '/', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', '.',
    'p', 'r', 'o', 't', 'o', '\022', '\013', 'x', 'd', 's', '.', 'c',
    'o', 'r', 'e', '.', 'v', '3', '\032', '\027', 'v', 'a', 'l', 'i',
    'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't',
    'e', '.', 'p', 'r', 'o', 't', 'o', '\032', '\031', 'g', 'o', 'o',
    'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f',
    '/', 'a', 'n', 'y', '.', 'p', 'r', 'o', 't', 'o', '\"', 'v',
    '\n', '\024', 'T', 'y', 'p', 'e', 'd', 'E', 'x', 't', 'e', 'n',
    's', 'i', 'o', 'n', 'C', 'o', 'n', 'f', 'i', 'g', '\022', '\033',
    '\n', '\004', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001', '(', '\t',
    'B', '\007', '\372', 'B', '\004', 'r', '\002', '\020', '\001', 'R', '\004', 'n',
    'a', 'm', 'e', '\022', 'A', '\n', '\014', 't', 'y', 'p', 'e', 'd',
    '_', 'c', 'o', 'n', 'f', 'i', 'g', '\030', '\002', ' ', '\001', '(',
    '\013', '2', '\024', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p',
    'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'A', 'n', 'y', 'B',
    '\010', '\372', 'B', '\005', '\242', '\001', '\002', '\010', '\001', 'R', '\013', 't',
    'y', 'p', 'e', 'd', 'C', 'o', 'n', 'f', 'i', 'g', 'B', 'N',
    '\n', '\026', 'c', 'o', 'm', '.', 'g', 'i', 't', 'h', 'u', 'b',
    '.', 'x', 'd', 's', '.', 'c', 'o', 'r', 'e', '.', 'v', '3',
    'B', '\016', 'E', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 'P',
    'r', 'o', 't', 'o', 'P', '\001', 'Z', '\"', 'g', 'i', 't', 'h',
    'u', 'b', '.', 'c', 'o', 'm', '/', 'c', 'n', 'c', 'f', '/',
    'x', 'd', 's', '/', 'g', 'o', '/', 'x', 'd', 's', '/', 'c',
    'o', 'r', 'e', '/', 'v', '3', 'b', '\006', 'p', 'r', 'o', 't',
    'o', '3',
};

static _upb_DefPool_Init *deps[3] = {
    &validate_validate_proto_upbdefinit,
    &google_protobuf_any_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_core_v3_extension_proto_upbdefinit = {
    deps,
    &xds_core_v3_extension_proto_upb_file_layout,
    "xds/core/v3/extension.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
