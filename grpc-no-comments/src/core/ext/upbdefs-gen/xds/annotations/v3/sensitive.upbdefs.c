
#include "upb/reflection/def.h"
#include "xds/annotations/v3/sensitive.upbdefs.h"
#include "xds/annotations/v3/sensitive.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_descriptor_proto_upbdefinit;

static const char descriptor[207] = {
    '\n', '\"', 'x', 'd', 's', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'v', '3', '/', 's', 'e', 'n',
    's', 'i', 't', 'i', 'v', 'e', '.', 'p', 'r', 'o', 't', 'o',
    '\022', '\022', 'x', 'd', 's', '.', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '.', 'v', '3', '\032', ' ', 'g', 'o',
    'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u',
    'f', '/', 'd', 'e', 's', 'c', 'r', 'i', 'p', 't', 'o', 'r',
    '.', 'p', 'r', 'o', 't', 'o', ':', '>', '\n', '\t', 's', 'e',
    'n', 's', 'i', 't', 'i', 'v', 'e', '\022', '\035', '.', 'g', 'o',
    'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u',
    'f', '.', 'F', 'i', 'e', 'l', 'd', 'O', 'p', 't', 'i', 'o',
    'n', 's', '\030', '\265', '\321', '\213', '\035', ' ', '\001', '(', '\010', 'R',
    '\t', 's', 'e', 'n', 's', 'i', 't', 'i', 'v', 'e', 'B', '+',
    'Z', ')', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm',
    '/', 'c', 'n', 'c', 'f', '/', 'x', 'd', 's', '/', 'g', 'o',
    '/', 'x', 'd', 's', '/', 'a', 'n', 'n', 'o', 't', 'a', 't',
    'i', 'o', 'n', 's', '/', 'v', '3', 'b', '\006', 'p', 'r', 'o',
    't', 'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &google_protobuf_descriptor_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_annotations_v3_sensitive_proto_upbdefinit = {
    deps,
    &xds_annotations_v3_sensitive_proto_upb_file_layout,
    "xds/annotations/v3/sensitive.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
