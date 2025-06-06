
#include "upb/reflection/def.h"
#include "envoy/config/listener/v3/api_listener.upbdefs.h"
#include "envoy/config/listener/v3/api_listener.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;

static const char descriptor[436] = {
    '\n', '+', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'l', 'i', 's', 't', 'e', 'n', 'e', 'r', '/',
    'v', '3', '/', 'a', 'p', 'i', '_', 'l', 'i', 's', 't', 'e',
    'n', 'e', 'r', '.', 'p', 'r', 'o', 't', 'o', '\022', '\030', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'l', 'i', 's', 't', 'e', 'n', 'e', 'r', '.', 'v', '3', '\032',
    '\031', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't',
    'o', 'b', 'u', 'f', '/', 'a', 'n', 'y', '.', 'p', 'r', 'o',
    't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a',
    't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '!', 'u',
    'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i', 'o', 'n', 'i',
    'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\"', 's', '\n', '\013',
    'A', 'p', 'i', 'L', 'i', 's', 't', 'e', 'n', 'e', 'r', '\022',
    '7', '\n', '\014', 'a', 'p', 'i', '_', 'l', 'i', 's', 't', 'e',
    'n', 'e', 'r', '\030', '\001', ' ', '\001', '(', '\013', '2', '\024', '.',
    'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o',
    'b', 'u', 'f', '.', 'A', 'n', 'y', 'R', '\013', 'a', 'p', 'i',
    'L', 'i', 's', 't', 'e', 'n', 'e', 'r', ':', '+', '\232', '\305',
    '\210', '\036', '&', '\n', '$', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'l', 'i', 's', 't', 'e', 'n',
    'e', 'r', '.', 'v', '2', '.', 'A', 'p', 'i', 'L', 'i', 's',
    't', 'e', 'n', 'e', 'r', 'B', '\220', '\001', '\n', '&', 'i', 'o',
    '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g',
    '.', 'l', 'i', 's', 't', 'e', 'n', 'e', 'r', '.', 'v', '3',
    'B', '\020', 'A', 'p', 'i', 'L', 'i', 's', 't', 'e', 'n', 'e',
    'r', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', 'J', 'g', 'i',
    't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v',
    'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c',
    'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e',
    '/', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i',
    'g', '/', 'l', 'i', 's', 't', 'e', 'n', 'e', 'r', '/', 'v',
    '3', ';', 'l', 'i', 's', 't', 'e', 'n', 'e', 'r', 'v', '3',
    '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r',
    'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &google_protobuf_any_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_listener_v3_api_listener_proto_upbdefinit = {
    deps,
    &envoy_config_listener_v3_api_listener_proto_upb_file_layout,
    "envoy/config/listener/v3/api_listener.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
