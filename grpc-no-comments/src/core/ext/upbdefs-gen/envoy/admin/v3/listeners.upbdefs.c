
#include "upb/reflection/def.h"
#include "envoy/admin/v3/listeners.upbdefs.h"
#include "envoy/admin/v3/listeners.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_address_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;

static const char descriptor[650] = {
    '\n', '\036', 'e', 'n', 'v', 'o', 'y', '/', 'a', 'd', 'm', 'i',
    'n', '/', 'v', '3', '/', 'l', 'i', 's', 't', 'e', 'n', 'e',
    'r', 's', '.', 'p', 'r', 'o', 't', 'o', '\022', '\016', 'e', 'n',
    'v', 'o', 'y', '.', 'a', 'd', 'm', 'i', 'n', '.', 'v', '3',
    '\032', '\"', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'a',
    'd', 'd', 'r', 'e', 's', 's', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u',
    's', '.', 'p', 'r', 'o', 't', 'o', '\032', '!', 'u', 'd', 'p',
    'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n',
    's', '/', 'v', 'e', 'r', 's', 'i', 'o', 'n', 'i', 'n', 'g',
    '.', 'p', 'r', 'o', 't', 'o', '\"', '~', '\n', '\t', 'L', 'i',
    's', 't', 'e', 'n', 'e', 'r', 's', '\022', 'K', '\n', '\021', 'l',
    'i', 's', 't', 'e', 'n', 'e', 'r', '_', 's', 't', 'a', 't',
    'u', 's', 'e', 's', '\030', '\001', ' ', '\003', '(', '\013', '2', '\036',
    '.', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'd', 'm', 'i', 'n',
    '.', 'v', '3', '.', 'L', 'i', 's', 't', 'e', 'n', 'e', 'r',
    'S', 't', 'a', 't', 'u', 's', 'R', '\020', 'l', 'i', 's', 't',
    'e', 'n', 'e', 'r', 'S', 't', 'a', 't', 'u', 's', 'e', 's',
    ':', '$', '\232', '\305', '\210', '\036', '\037', '\n', '\035', 'e', 'n', 'v',
    'o', 'y', '.', 'a', 'd', 'm', 'i', 'n', '.', 'v', '2', 'a',
    'l', 'p', 'h', 'a', '.', 'L', 'i', 's', 't', 'e', 'n', 'e',
    'r', 's', '\"', '\360', '\001', '\n', '\016', 'L', 'i', 's', 't', 'e',
    'n', 'e', 'r', 'S', 't', 'a', 't', 'u', 's', '\022', '\022', '\n',
    '\004', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001', '(', '\t', 'R',
    '\004', 'n', 'a', 'm', 'e', '\022', 'B', '\n', '\r', 'l', 'o', 'c',
    'a', 'l', '_', 'a', 'd', 'd', 'r', 'e', 's', 's', '\030', '\002',
    ' ', '\001', '(', '\013', '2', '\035', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e',
    '.', 'v', '3', '.', 'A', 'd', 'd', 'r', 'e', 's', 's', 'R',
    '\014', 'l', 'o', 'c', 'a', 'l', 'A', 'd', 'd', 'r', 'e', 's',
    's', '\022', '[', '\n', '\032', 'a', 'd', 'd', 'i', 't', 'i', 'o',
    'n', 'a', 'l', '_', 'l', 'o', 'c', 'a', 'l', '_', 'a', 'd',
    'd', 'r', 'e', 's', 's', 'e', 's', '\030', '\003', ' ', '\003', '(',
    '\013', '2', '\035', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o',
    'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3',
    '.', 'A', 'd', 'd', 'r', 'e', 's', 's', 'R', '\030', 'a', 'd',
    'd', 'i', 't', 'i', 'o', 'n', 'a', 'l', 'L', 'o', 'c', 'a',
    'l', 'A', 'd', 'd', 'r', 'e', 's', 's', 'e', 's', ':', ')',
    '\232', '\305', '\210', '\036', '$', '\n', '\"', 'e', 'n', 'v', 'o', 'y',
    '.', 'a', 'd', 'm', 'i', 'n', '.', 'v', '2', 'a', 'l', 'p',
    'h', 'a', '.', 'L', 'i', 's', 't', 'e', 'n', 'e', 'r', 'S',
    't', 'a', 't', 'u', 's', 'B', 'w', '\n', '\034', 'i', 'o', '.',
    'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'a', 'd', 'm', 'i', 'n', '.', 'v',
    '3', 'B', '\016', 'L', 'i', 's', 't', 'e', 'n', 'e', 'r', 's',
    'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', '=', 'g', 'i', 't',
    'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o',
    'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o',
    'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/',
    'e', 'n', 'v', 'o', 'y', '/', 'a', 'd', 'm', 'i', 'n', '/',
    'v', '3', ';', 'a', 'd', 'm', 'i', 'n', 'v', '3', '\272', '\200',
    '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't',
    'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &envoy_config_core_v3_address_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_admin_v3_listeners_proto_upbdefinit = {
    deps,
    &envoy_admin_v3_listeners_proto_upb_file_layout,
    "envoy/admin/v3/listeners.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
