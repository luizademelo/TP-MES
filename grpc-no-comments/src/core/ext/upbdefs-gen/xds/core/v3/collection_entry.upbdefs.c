
#include "upb/reflection/def.h"
#include "xds/core/v3/collection_entry.upbdefs.h"
#include "xds/core/v3/collection_entry.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;
extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;
extern _upb_DefPool_Init xds_core_v3_resource_locator_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[598] = {
    '\n', '\"', 'x', 'd', 's', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '/', 'c', 'o', 'l', 'l', 'e', 'c', 't', 'i', 'o', 'n',
    '_', 'e', 'n', 't', 'r', 'y', '.', 'p', 'r', 'o', 't', 'o',
    '\022', '\013', 'x', 'd', 's', '.', 'c', 'o', 'r', 'e', '.', 'v',
    '3', '\032', '\031', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r',
    'o', 't', 'o', 'b', 'u', 'f', '/', 'a', 'n', 'y', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\037', 'x', 'd', 's', '/', 'a', 'n',
    'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 'v', '3',
    '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't',
    'o', '\032', '\"', 'x', 'd', 's', '/', 'c', 'o', 'r', 'e', '/',
    'v', '3', '/', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_',
    'l', 'o', 'c', 'a', 't', 'o', 'r', '.', 'p', 'r', 'o', 't',
    'o', '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/',
    'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o',
    't', 'o', '\"', '\303', '\002', '\n', '\017', 'C', 'o', 'l', 'l', 'e',
    'c', 't', 'i', 'o', 'n', 'E', 'n', 't', 'r', 'y', '\022', '8',
    '\n', '\007', 'l', 'o', 'c', 'a', 't', 'o', 'r', '\030', '\001', ' ',
    '\001', '(', '\013', '2', '\034', '.', 'x', 'd', 's', '.', 'c', 'o',
    'r', 'e', '.', 'v', '3', '.', 'R', 'e', 's', 'o', 'u', 'r',
    'c', 'e', 'L', 'o', 'c', 'a', 't', 'o', 'r', 'H', '\000', 'R',
    '\007', 'l', 'o', 'c', 'a', 't', 'o', 'r', '\022', 'M', '\n', '\014',
    'i', 'n', 'l', 'i', 'n', 'e', '_', 'e', 'n', 't', 'r', 'y',
    '\030', '\002', ' ', '\001', '(', '\013', '2', '(', '.', 'x', 'd', 's',
    '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'C', 'o', 'l',
    'l', 'e', 'c', 't', 'i', 'o', 'n', 'E', 'n', 't', 'r', 'y',
    '.', 'I', 'n', 'l', 'i', 'n', 'e', 'E', 'n', 't', 'r', 'y',
    'H', '\000', 'R', '\013', 'i', 'n', 'l', 'i', 'n', 'e', 'E', 'n',
    't', 'r', 'y', '\032', '\213', '\001', '\n', '\013', 'I', 'n', 'l', 'i',
    'n', 'e', 'E', 'n', 't', 'r', 'y', '\022', '0', '\n', '\004', 'n',
    'a', 'm', 'e', '\030', '\001', ' ', '\001', '(', '\t', 'B', '\034', '\372',
    'B', '\031', 'r', '\027', '2', '\025', '^', '[', '0', '-', '9', 'a',
    '-', 'z', 'A', '-', 'Z', '_', '\\', '-', '\\', '.', '~', ':',
    ']', '+', '$', 'R', '\004', 'n', 'a', 'm', 'e', '\022', '\030', '\n',
    '\007', 'v', 'e', 'r', 's', 'i', 'o', 'n', '\030', '\002', ' ', '\001',
    '(', '\t', 'R', '\007', 'v', 'e', 'r', 's', 'i', 'o', 'n', '\022',
    '0', '\n', '\010', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '\030',
    '\003', ' ', '\001', '(', '\013', '2', '\024', '.', 'g', 'o', 'o', 'g',
    'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.',
    'A', 'n', 'y', 'R', '\010', 'r', 'e', 's', 'o', 'u', 'r', 'c',
    'e', 'B', '\031', '\n', '\022', 'r', 'e', 's', 'o', 'u', 'r', 'c',
    'e', '_', 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'r', '\022',
    '\003', '\370', 'B', '\001', 'B', '\\', '\n', '\026', 'c', 'o', 'm', '.',
    'g', 'i', 't', 'h', 'u', 'b', '.', 'x', 'd', 's', '.', 'c',
    'o', 'r', 'e', '.', 'v', '3', 'B', '\024', 'C', 'o', 'l', 'l',
    'e', 'c', 't', 'i', 'o', 'n', 'E', 'n', 't', 'r', 'y', 'P',
    'r', 'o', 't', 'o', 'P', '\001', 'Z', '\"', 'g', 'i', 't', 'h',
    'u', 'b', '.', 'c', 'o', 'm', '/', 'c', 'n', 'c', 'f', '/',
    'x', 'd', 's', '/', 'g', 'o', '/', 'x', 'd', 's', '/', 'c',
    'o', 'r', 'e', '/', 'v', '3', '\322', '\306', '\244', '\341', '\006', '\002',
    '\010', '\001', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[5] = {
    &google_protobuf_any_proto_upbdefinit,
    &xds_annotations_v3_status_proto_upbdefinit,
    &xds_core_v3_resource_locator_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_core_v3_collection_entry_proto_upbdefinit = {
    deps,
    &xds_core_v3_collection_entry_proto_upb_file_layout,
    "xds/core/v3/collection_entry.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
