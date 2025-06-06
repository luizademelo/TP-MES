
#include "upb/reflection/def.h"
#include "xds/annotations/v3/security.upbdefs.h"
#include "xds/annotations/v3/security.upb_minitable.h"

extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_descriptor_proto_upbdefinit;

static const char descriptor[468] = {
    '\n', '!', 'x', 'd', 's', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'v', '3', '/', 's', 'e', 'c',
    'u', 'r', 'i', 't', 'y', '.', 'p', 'r', 'o', 't', 'o', '\022',
    '\022', 'x', 'd', 's', '.', 'a', 'n', 'n', 'o', 't', 'a', 't',
    'i', 'o', 'n', 's', '.', 'v', '3', '\032', '\037', 'x', 'd', 's',
    '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '/', 'v', '3', '/', 's', 't', 'a', 't', 'u', 's', '.', 'p',
    'r', 'o', 't', 'o', '\032', ' ', 'g', 'o', 'o', 'g', 'l', 'e',
    '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'd', 'e',
    's', 'c', 'r', 'i', 'p', 't', 'o', 'r', '.', 'p', 'r', 'o',
    't', 'o', '\"', '\257', '\001', '\n', '\027', 'F', 'i', 'e', 'l', 'd',
    'S', 'e', 'c', 'u', 'r', 'i', 't', 'y', 'A', 'n', 'n', 'o',
    't', 'a', 't', 'i', 'o', 'n', '\022', 'K', '\n', '\"', 'c', 'o',
    'n', 'f', 'i', 'g', 'u', 'r', 'e', '_', 'f', 'o', 'r', '_',
    'u', 'n', 't', 'r', 'u', 's', 't', 'e', 'd', '_', 'd', 'o',
    'w', 'n', 's', 't', 'r', 'e', 'a', 'm', '\030', '\001', ' ', '\001',
    '(', '\010', 'R', '\037', 'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r',
    'e', 'F', 'o', 'r', 'U', 'n', 't', 'r', 'u', 's', 't', 'e',
    'd', 'D', 'o', 'w', 'n', 's', 't', 'r', 'e', 'a', 'm', '\022',
    'G', '\n', ' ', 'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'e',
    '_', 'f', 'o', 'r', '_', 'u', 'n', 't', 'r', 'u', 's', 't',
    'e', 'd', '_', 'u', 'p', 's', 't', 'r', 'e', 'a', 'm', '\030',
    '\002', ' ', '\001', '(', '\010', 'R', '\035', 'c', 'o', 'n', 'f', 'i',
    'g', 'u', 'r', 'e', 'F', 'o', 'r', 'U', 'n', 't', 'r', 'u',
    's', 't', 'e', 'd', 'U', 'p', 's', 't', 'r', 'e', 'a', 'm',
    ':', 'i', '\n', '\010', 's', 'e', 'c', 'u', 'r', 'i', 't', 'y',
    '\022', '\035', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r',
    'o', 't', 'o', 'b', 'u', 'f', '.', 'F', 'i', 'e', 'l', 'd',
    'O', 'p', 't', 'i', 'o', 'n', 's', '\030', '\247', '\226', '\235', '/',
    ' ', '\001', '(', '\013', '2', '+', '.', 'x', 'd', 's', '.', 'a',
    'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '.', 'v',
    '3', '.', 'F', 'i', 'e', 'l', 'd', 'S', 'e', 'c', 'u', 'r',
    'i', 't', 'y', 'A', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o',
    'n', 'R', '\010', 's', 'e', 'c', 'u', 'r', 'i', 't', 'y', 'B',
    '3', 'Z', ')', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o',
    'm', '/', 'c', 'n', 'c', 'f', '/', 'x', 'd', 's', '/', 'g',
    'o', '/', 'x', 'd', 's', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'v', '3', '\322', '\306', '\244', '\341',
    '\006', '\002', '\010', '\001', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[3] = {
    &xds_annotations_v3_status_proto_upbdefinit,
    &google_protobuf_descriptor_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_annotations_v3_security_proto_upbdefinit = {
    deps,
    &xds_annotations_v3_security_proto_upb_file_layout,
    "xds/annotations/v3/security.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
