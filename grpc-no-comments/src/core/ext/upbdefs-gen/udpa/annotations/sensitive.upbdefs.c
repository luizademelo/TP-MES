
#include "upb/reflection/def.h"
#include "udpa/annotations/sensitive.upbdefs.h"
#include "udpa/annotations/sensitive.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_descriptor_proto_upbdefinit;

static const char descriptor[196] = {
    '\n', ' ', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 's', 'e', 'n', 's', 'i',
    't', 'i', 'v', 'e', '.', 'p', 'r', 'o', 't', 'o', '\022', '\020',
    'u', 'd', 'p', 'a', '.', 'a', 'n', 'n', 'o', 't', 'a', 't',
    'i', 'o', 'n', 's', '\032', ' ', 'g', 'o', 'o', 'g', 'l', 'e',
    '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'd', 'e',
    's', 'c', 'r', 'i', 'p', 't', 'o', 'r', '.', 'p', 'r', 'o',
    't', 'o', ':', '>', '\n', '\t', 's', 'e', 'n', 's', 'i', 't',
    'i', 'v', 'e', '\022', '\035', '.', 'g', 'o', 'o', 'g', 'l', 'e',
    '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'F', 'i',
    'e', 'l', 'd', 'O', 'p', 't', 'i', 'o', 'n', 's', '\030', '\367',
    '\266', '\301', '$', ' ', '\001', '(', '\010', 'R', '\t', 's', 'e', 'n',
    's', 'i', 't', 'i', 'v', 'e', 'B', '$', 'Z', '\"', 'g', 'i',
    't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'c', 'n', 'c',
    'f', '/', 'x', 'd', 's', '/', 'g', 'o', '/', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', 'b', '\006', 'p', 'r',
    'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &google_protobuf_descriptor_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init udpa_annotations_sensitive_proto_upbdefinit = {
    deps,
    &udpa_annotations_sensitive_proto_upb_file_layout,
    "udpa/annotations/sensitive.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
