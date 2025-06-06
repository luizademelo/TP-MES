
#include "upb/reflection/def.h"
#include "google/rpc/status.upbdefs.h"
#include "google/rpc/status.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;

static const char descriptor[275] = {
    '\n', '\027', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'r', 'p', 'c',
    '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't',
    'o', '\022', '\n', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'r', 'p',
    'c', '\032', '\031', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r',
    'o', 't', 'o', 'b', 'u', 'f', '/', 'a', 'n', 'y', '.', 'p',
    'r', 'o', 't', 'o', '\"', 'f', '\n', '\006', 'S', 't', 'a', 't',
    'u', 's', '\022', '\022', '\n', '\004', 'c', 'o', 'd', 'e', '\030', '\001',
    ' ', '\001', '(', '\005', 'R', '\004', 'c', 'o', 'd', 'e', '\022', '\030',
    '\n', '\007', 'm', 'e', 's', 's', 'a', 'g', 'e', '\030', '\002', ' ',
    '\001', '(', '\t', 'R', '\007', 'm', 'e', 's', 's', 'a', 'g', 'e',
    '\022', '.', '\n', '\007', 'd', 'e', 't', 'a', 'i', 'l', 's', '\030',
    '\003', ' ', '\003', '(', '\013', '2', '\024', '.', 'g', 'o', 'o', 'g',
    'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.',
    'A', 'n', 'y', 'R', '\007', 'd', 'e', 't', 'a', 'i', 'l', 's',
    'B', 'a', '\n', '\016', 'c', 'o', 'm', '.', 'g', 'o', 'o', 'g',
    'l', 'e', '.', 'r', 'p', 'c', 'B', '\013', 'S', 't', 'a', 't',
    'u', 's', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', '7', 'g',
    'o', 'o', 'g', 'l', 'e', '.', 'g', 'o', 'l', 'a', 'n', 'g',
    '.', 'o', 'r', 'g', '/', 'g', 'e', 'n', 'p', 'r', 'o', 't',
    'o', '/', 'g', 'o', 'o', 'g', 'l', 'e', 'a', 'p', 'i', 's',
    '/', 'r', 'p', 'c', '/', 's', 't', 'a', 't', 'u', 's', ';',
    's', 't', 'a', 't', 'u', 's', '\370', '\001', '\001', '\242', '\002', '\003',
    'R', 'P', 'C', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &google_protobuf_any_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init google_rpc_status_proto_upbdefinit = {
    deps,
    &google_rpc_status_proto_upb_file_layout,
    "google/rpc/status.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
