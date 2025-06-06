
#include "upb/reflection/def.h"
#include "envoy/annotations/resource.upbdefs.h"
#include "envoy/annotations/resource.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_descriptor_proto_upbdefinit;

static const char descriptor[300] = {
    '\n', ' ', 'e', 'n', 'v', 'o', 'y', '/', 'a', 'n', 'n', 'o',
    't', 'a', 't', 'i', 'o', 'n', 's', '/', 'r', 'e', 's', 'o',
    'u', 'r', 'c', 'e', '.', 'p', 'r', 'o', 't', 'o', '\022', '\021',
    'e', 'n', 'v', 'o', 'y', '.', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '\032', ' ', 'g', 'o', 'o', 'g', 'l',
    'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'd',
    'e', 's', 'c', 'r', 'i', 'p', 't', 'o', 'r', '.', 'p', 'r',
    'o', 't', 'o', '\"', '(', '\n', '\022', 'R', 'e', 's', 'o', 'u',
    'r', 'c', 'e', 'A', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o',
    'n', '\022', '\022', '\n', '\004', 't', 'y', 'p', 'e', '\030', '\001', ' ',
    '\001', '(', '\t', 'R', '\004', 't', 'y', 'p', 'e', ':', 'e', '\n',
    '\010', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '\022', '\037', '.',
    'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o',
    'b', 'u', 'f', '.', 'S', 'e', 'r', 'v', 'i', 'c', 'e', 'O',
    'p', 't', 'i', 'o', 'n', 's', '\030', '\301', '\344', '\262', '~', ' ',
    '\001', '(', '\013', '2', '%', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '.',
    'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'A', 'n', 'n', 'o',
    't', 'a', 't', 'i', 'o', 'n', 'R', '\010', 'r', 'e', 's', 'o',
    'u', 'r', 'c', 'e', 'B', ':', 'Z', '8', 'g', 'i', 't', 'h',
    'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n',
    't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e',
    'n', 'v', 'o', 'y', '/', 'a', 'n', 'n', 'o', 't', 'a', 't',
    'i', 'o', 'n', 's', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &google_protobuf_descriptor_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_annotations_resource_proto_upbdefinit = {
    deps,
    &envoy_annotations_resource_proto_upb_file_layout,
    "envoy/annotations/resource.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
