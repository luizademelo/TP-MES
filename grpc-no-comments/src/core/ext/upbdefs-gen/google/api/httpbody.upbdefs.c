
#include "upb/reflection/def.h"
#include "google/api/httpbody.upbdefs.h"
#include "google/api/httpbody.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;

static const char descriptor[301] = {
    '\n', '\031', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'a', 'p', 'i',
    '/', 'h', 't', 't', 'p', 'b', 'o', 'd', 'y', '.', 'p', 'r',
    'o', 't', 'o', '\022', '\n', 'g', 'o', 'o', 'g', 'l', 'e', '.',
    'a', 'p', 'i', '\032', '\031', 'g', 'o', 'o', 'g', 'l', 'e', '/',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'a', 'n', 'y',
    '.', 'p', 'r', 'o', 't', 'o', '\"', 'w', '\n', '\010', 'H', 't',
    't', 'p', 'B', 'o', 'd', 'y', '\022', '!', '\n', '\014', 'c', 'o',
    'n', 't', 'e', 'n', 't', '_', 't', 'y', 'p', 'e', '\030', '\001',
    ' ', '\001', '(', '\t', 'R', '\013', 'c', 'o', 'n', 't', 'e', 'n',
    't', 'T', 'y', 'p', 'e', '\022', '\022', '\n', '\004', 'd', 'a', 't',
    'a', '\030', '\002', ' ', '\001', '(', '\014', 'R', '\004', 'd', 'a', 't',
    'a', '\022', '4', '\n', '\n', 'e', 'x', 't', 'e', 'n', 's', 'i',
    'o', 'n', 's', '\030', '\003', ' ', '\003', '(', '\013', '2', '\024', '.',
    'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o',
    'b', 'u', 'f', '.', 'A', 'n', 'y', 'R', '\n', 'e', 'x', 't',
    'e', 'n', 's', 'i', 'o', 'n', 's', 'B', 'h', '\n', '\016', 'c',
    'o', 'm', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'a', 'p',
    'i', 'B', '\r', 'H', 't', 't', 'p', 'B', 'o', 'd', 'y', 'P',
    'r', 'o', 't', 'o', 'P', '\001', 'Z', ';', 'g', 'o', 'o', 'g',
    'l', 'e', '.', 'g', 'o', 'l', 'a', 'n', 'g', '.', 'o', 'r',
    'g', '/', 'g', 'e', 'n', 'p', 'r', 'o', 't', 'o', '/', 'g',
    'o', 'o', 'g', 'l', 'e', 'a', 'p', 'i', 's', '/', 'a', 'p',
    'i', '/', 'h', 't', 't', 'p', 'b', 'o', 'd', 'y', ';', 'h',
    't', 't', 'p', 'b', 'o', 'd', 'y', '\370', '\001', '\001', '\242', '\002',
    '\004', 'G', 'A', 'P', 'I', 'b', '\006', 'p', 'r', 'o', 't', 'o',
    '3',
};

static _upb_DefPool_Init *deps[2] = {
    &google_protobuf_any_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init google_api_httpbody_proto_upbdefinit = {
    deps,
    &google_api_httpbody_proto_upb_file_layout,
    "google/api/httpbody.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
