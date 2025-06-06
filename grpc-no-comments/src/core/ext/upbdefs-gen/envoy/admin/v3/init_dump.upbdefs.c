
#include "upb/reflection/def.h"
#include "envoy/admin/v3/init_dump.upbdefs.h"
#include "envoy/admin/v3/init_dump.upb_minitable.h"

extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;

static const char descriptor[416] = {
    '\n', '\036', 'e', 'n', 'v', 'o', 'y', '/', 'a', 'd', 'm', 'i',
    'n', '/', 'v', '3', '/', 'i', 'n', 'i', 't', '_', 'd', 'u',
    'm', 'p', '.', 'p', 'r', 'o', 't', 'o', '\022', '\016', 'e', 'n',
    'v', 'o', 'y', '.', 'a', 'd', 'm', 'i', 'n', '.', 'v', '3',
    '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u',
    's', '.', 'p', 'r', 'o', 't', 'o', '\"', '\316', '\001', '\n', '\023',
    'U', 'n', 'r', 'e', 'a', 'd', 'y', 'T', 'a', 'r', 'g', 'e',
    't', 's', 'D', 'u', 'm', 'p', 's', '\022', 'j', '\n', '\025', 'u',
    'n', 'r', 'e', 'a', 'd', 'y', '_', 't', 'a', 'r', 'g', 'e',
    't', 's', '_', 'd', 'u', 'm', 'p', 's', '\030', '\001', ' ', '\003',
    '(', '\013', '2', '6', '.', 'e', 'n', 'v', 'o', 'y', '.', 'a',
    'd', 'm', 'i', 'n', '.', 'v', '3', '.', 'U', 'n', 'r', 'e',
    'a', 'd', 'y', 'T', 'a', 'r', 'g', 'e', 't', 's', 'D', 'u',
    'm', 'p', 's', '.', 'U', 'n', 'r', 'e', 'a', 'd', 'y', 'T',
    'a', 'r', 'g', 'e', 't', 's', 'D', 'u', 'm', 'p', 'R', '\023',
    'u', 'n', 'r', 'e', 'a', 'd', 'y', 'T', 'a', 'r', 'g', 'e',
    't', 's', 'D', 'u', 'm', 'p', 's', '\032', 'K', '\n', '\022', 'U',
    'n', 'r', 'e', 'a', 'd', 'y', 'T', 'a', 'r', 'g', 'e', 't',
    's', 'D', 'u', 'm', 'p', '\022', '\022', '\n', '\004', 'n', 'a', 'm',
    'e', '\030', '\001', ' ', '\001', '(', '\t', 'R', '\004', 'n', 'a', 'm',
    'e', '\022', '!', '\n', '\014', 't', 'a', 'r', 'g', 'e', 't', '_',
    'n', 'a', 'm', 'e', 's', '\030', '\002', ' ', '\003', '(', '\t', 'R',
    '\013', 't', 'a', 'r', 'g', 'e', 't', 'N', 'a', 'm', 'e', 's',
    'B', 'v', '\n', '\034', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'a', 'd', 'm', 'i', 'n', '.', 'v', '3', 'B', '\r', 'I', 'n',
    'i', 't', 'D', 'u', 'm', 'p', 'P', 'r', 'o', 't', 'o', 'P',
    '\001', 'Z', '=', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o',
    'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y',
    '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-',
    'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/',
    'a', 'd', 'm', 'i', 'n', '/', 'v', '3', ';', 'a', 'd', 'm',
    'i', 'n', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002',
    'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &udpa_annotations_status_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_admin_v3_init_dump_proto_upbdefinit = {
    deps,
    &envoy_admin_v3_init_dump_proto_upb_file_layout,
    "envoy/admin/v3/init_dump.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
