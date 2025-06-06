
#include "upb/reflection/def.h"
#include "envoy/config/core/v3/socket_cmsg_headers.upbdefs.h"
#include "envoy/config/core/v3/socket_cmsg_headers.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_wrappers_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;

static const char descriptor[443] = {
    '\n', '.', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 's',
    'o', 'c', 'k', 'e', 't', '_', 'c', 'm', 's', 'g', '_', 'h',
    'e', 'a', 'd', 'e', 'r', 's', '.', 'p', 'r', 'o', 't', 'o',
    '\022', '\024', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '\032', '\036',
    'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o',
    'b', 'u', 'f', '/', 'w', 'r', 'a', 'p', 'p', 'e', 'r', 's',
    '.', 'p', 'r', 'o', 't', 'o', '\032', '\035', 'u', 'd', 'p', 'a',
    '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't',
    'o', '\"', '\236', '\001', '\n', '\021', 'S', 'o', 'c', 'k', 'e', 't',
    'C', 'm', 's', 'g', 'H', 'e', 'a', 'd', 'e', 'r', 's', '\022',
    '2', '\n', '\005', 'l', 'e', 'v', 'e', 'l', '\030', '\001', ' ', '\001',
    '(', '\013', '2', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n',
    't', '3', '2', 'V', 'a', 'l', 'u', 'e', 'R', '\005', 'l', 'e',
    'v', 'e', 'l', '\022', '0', '\n', '\004', 't', 'y', 'p', 'e', '\030',
    '\002', ' ', '\001', '(', '\013', '2', '\034', '.', 'g', 'o', 'o', 'g',
    'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.',
    'U', 'I', 'n', 't', '3', '2', 'V', 'a', 'l', 'u', 'e', 'R',
    '\004', 't', 'y', 'p', 'e', '\022', '#', '\n', '\r', 'e', 'x', 'p',
    'e', 'c', 't', 'e', 'd', '_', 's', 'i', 'z', 'e', '\030', '\003',
    ' ', '\001', '(', '\r', 'R', '\014', 'e', 'x', 'p', 'e', 'c', 't',
    'e', 'd', 'S', 'i', 'z', 'e', 'B', '\212', '\001', '\n', '\"', 'i',
    'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y',
    '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i',
    'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', 'B', '\026', 'S',
    'o', 'c', 'k', 'e', 't', 'C', 'm', 's', 'g', 'H', 'e', 'a',
    'd', 'e', 'r', 's', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z',
    'B', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/',
    'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g',
    'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l',
    'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o',
    'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3',
    ';', 'c', 'o', 'r', 'e', 'v', '3', '\272', '\200', '\310', '\321', '\006',
    '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[3] = {
    &google_protobuf_wrappers_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_core_v3_socket_cmsg_headers_proto_upbdefinit = {
    deps,
    &envoy_config_core_v3_socket_cmsg_headers_proto_upb_file_layout,
    "envoy/config/core/v3/socket_cmsg_headers.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
