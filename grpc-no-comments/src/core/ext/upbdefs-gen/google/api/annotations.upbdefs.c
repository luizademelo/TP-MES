
#include "upb/reflection/def.h"
#include "google/api/annotations.upbdefs.h"
#include "google/api/annotations.upb_minitable.h"

extern _upb_DefPool_Init google_api_http_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_descriptor_proto_upbdefinit;

static const char descriptor[296] = {
    '\n', '\034', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'a', 'p', 'i',
    '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '.', 'p', 'r', 'o', 't', 'o', '\022', '\n', 'g', 'o', 'o', 'g',
    'l', 'e', '.', 'a', 'p', 'i', '\032', '\025', 'g', 'o', 'o', 'g',
    'l', 'e', '/', 'a', 'p', 'i', '/', 'h', 't', 't', 'p', '.',
    'p', 'r', 'o', 't', 'o', '\032', ' ', 'g', 'o', 'o', 'g', 'l',
    'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'd',
    'e', 's', 'c', 'r', 'i', 'p', 't', 'o', 'r', '.', 'p', 'r',
    'o', 't', 'o', ':', 'K', '\n', '\004', 'h', 't', 't', 'p', '\022',
    '\036', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '.', 'M', 'e', 't', 'h', 'o', 'd',
    'O', 'p', 't', 'i', 'o', 'n', 's', '\030', '\260', '\312', '\274', '\"',
    ' ', '\001', '(', '\013', '2', '\024', '.', 'g', 'o', 'o', 'g', 'l',
    'e', '.', 'a', 'p', 'i', '.', 'H', 't', 't', 'p', 'R', 'u',
    'l', 'e', 'R', '\004', 'h', 't', 't', 'p', 'B', 'n', '\n', '\016',
    'c', 'o', 'm', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'a',
    'p', 'i', 'B', '\020', 'A', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 's', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', 'A',
    'g', 'o', 'o', 'g', 'l', 'e', '.', 'g', 'o', 'l', 'a', 'n',
    'g', '.', 'o', 'r', 'g', '/', 'g', 'e', 'n', 'p', 'r', 'o',
    't', 'o', '/', 'g', 'o', 'o', 'g', 'l', 'e', 'a', 'p', 'i',
    's', '/', 'a', 'p', 'i', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', ';', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '\242', '\002', '\004', 'G', 'A', 'P', 'I',
    'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[3] = {
    &google_api_http_proto_upbdefinit,
    &google_protobuf_descriptor_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init google_api_annotations_proto_upbdefinit = {
    deps,
    &google_api_annotations_proto_upb_file_layout,
    "google/api/annotations.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
