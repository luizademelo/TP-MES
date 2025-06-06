
#include "upb/reflection/def.h"
#include "xds/core/v3/resource.upbdefs.h"
#include "xds/core/v3/resource.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;
extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;
extern _upb_DefPool_Init xds_core_v3_resource_name_proto_upbdefinit;

static const char descriptor[365] = {
    '\n', '\032', 'x', 'd', 's', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '/', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '.', 'p',
    'r', 'o', 't', 'o', '\022', '\013', 'x', 'd', 's', '.', 'c', 'o',
    'r', 'e', '.', 'v', '3', '\032', '\031', 'g', 'o', 'o', 'g', 'l',
    'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'a',
    'n', 'y', '.', 'p', 'r', 'o', 't', 'o', '\032', '\037', 'x', 'd',
    's', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n',
    's', '/', 'v', '3', '/', 's', 't', 'a', 't', 'u', 's', '.',
    'p', 'r', 'o', 't', 'o', '\032', '\037', 'x', 'd', 's', '/', 'c',
    'o', 'r', 'e', '/', 'v', '3', '/', 'r', 'e', 's', 'o', 'u',
    'r', 'c', 'e', '_', 'n', 'a', 'm', 'e', '.', 'p', 'r', 'o',
    't', 'o', '\"', '\205', '\001', '\n', '\010', 'R', 'e', 's', 'o', 'u',
    'r', 'c', 'e', '\022', '-', '\n', '\004', 'n', 'a', 'm', 'e', '\030',
    '\001', ' ', '\001', '(', '\013', '2', '\031', '.', 'x', 'd', 's', '.',
    'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'R', 'e', 's', 'o',
    'u', 'r', 'c', 'e', 'N', 'a', 'm', 'e', 'R', '\004', 'n', 'a',
    'm', 'e', '\022', '\030', '\n', '\007', 'v', 'e', 'r', 's', 'i', 'o',
    'n', '\030', '\002', ' ', '\001', '(', '\t', 'R', '\007', 'v', 'e', 'r',
    's', 'i', 'o', 'n', '\022', '0', '\n', '\010', 'r', 'e', 's', 'o',
    'u', 'r', 'c', 'e', '\030', '\003', ' ', '\001', '(', '\013', '2', '\024',
    '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't',
    'o', 'b', 'u', 'f', '.', 'A', 'n', 'y', 'R', '\010', 'r', 'e',
    's', 'o', 'u', 'r', 'c', 'e', 'B', 'U', '\n', '\026', 'c', 'o',
    'm', '.', 'g', 'i', 't', 'h', 'u', 'b', '.', 'x', 'd', 's',
    '.', 'c', 'o', 'r', 'e', '.', 'v', '3', 'B', '\r', 'R', 'e',
    's', 'o', 'u', 'r', 'c', 'e', 'P', 'r', 'o', 't', 'o', 'P',
    '\001', 'Z', '\"', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o',
    'm', '/', 'c', 'n', 'c', 'f', '/', 'x', 'd', 's', '/', 'g',
    'o', '/', 'x', 'd', 's', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '\322', '\306', '\244', '\341', '\006', '\002', '\010', '\001', 'b', '\006', 'p',
    'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &google_protobuf_any_proto_upbdefinit,
    &xds_annotations_v3_status_proto_upbdefinit,
    &xds_core_v3_resource_name_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_core_v3_resource_proto_upbdefinit = {
    deps,
    &xds_core_v3_resource_proto_upb_file_layout,
    "xds/core/v3/resource.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
