
#include "upb/reflection/def.h"
#include "envoy/admin/v3/mutex_stats.upbdefs.h"
#include "envoy/admin/v3/mutex_stats.upb_minitable.h"

extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;

static const char descriptor[439] = {
    '\n', ' ', 'e', 'n', 'v', 'o', 'y', '/', 'a', 'd', 'm', 'i',
    'n', '/', 'v', '3', '/', 'm', 'u', 't', 'e', 'x', '_', 's',
    't', 'a', 't', 's', '.', 'p', 'r', 'o', 't', 'o', '\022', '\016',
    'e', 'n', 'v', 'o', 'y', '.', 'a', 'd', 'm', 'i', 'n', '.',
    'v', '3', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a',
    't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '!', 'u',
    'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i', 'o', 'n', 'i',
    'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\"', '\276', '\001', '\n',
    '\n', 'M', 'u', 't', 'e', 'x', 'S', 't', 'a', 't', 's', '\022',
    '\'', '\n', '\017', 'n', 'u', 'm', '_', 'c', 'o', 'n', 't', 'e',
    'n', 't', 'i', 'o', 'n', 's', '\030', '\001', ' ', '\001', '(', '\004',
    'R', '\016', 'n', 'u', 'm', 'C', 'o', 'n', 't', 'e', 'n', 't',
    'i', 'o', 'n', 's', '\022', '.', '\n', '\023', 'c', 'u', 'r', 'r',
    'e', 'n', 't', '_', 'w', 'a', 'i', 't', '_', 'c', 'y', 'c',
    'l', 'e', 's', '\030', '\002', ' ', '\001', '(', '\004', 'R', '\021', 'c',
    'u', 'r', 'r', 'e', 'n', 't', 'W', 'a', 'i', 't', 'C', 'y',
    'c', 'l', 'e', 's', '\022', '0', '\n', '\024', 'l', 'i', 'f', 'e',
    't', 'i', 'm', 'e', '_', 'w', 'a', 'i', 't', '_', 'c', 'y',
    'c', 'l', 'e', 's', '\030', '\003', ' ', '\001', '(', '\004', 'R', '\022',
    'l', 'i', 'f', 'e', 't', 'i', 'm', 'e', 'W', 'a', 'i', 't',
    'C', 'y', 'c', 'l', 'e', 's', ':', '%', '\232', '\305', '\210', '\036',
    ' ', '\n', '\036', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'd', 'm',
    'i', 'n', '.', 'v', '2', 'a', 'l', 'p', 'h', 'a', '.', 'M',
    'u', 't', 'e', 'x', 'S', 't', 'a', 't', 's', 'B', 'x', '\n',
    '\034', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o',
    'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'd', 'm',
    'i', 'n', '.', 'v', '3', 'B', '\017', 'M', 'u', 't', 'e', 'x',
    'S', 't', 'a', 't', 's', 'P', 'r', 'o', 't', 'o', 'P', '\001',
    'Z', '=', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm',
    '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/',
    'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p',
    'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 'a',
    'd', 'm', 'i', 'n', '/', 'v', '3', ';', 'a', 'd', 'm', 'i',
    'n', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b',
    '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[3] = {
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_admin_v3_mutex_stats_proto_upbdefinit = {
    deps,
    &envoy_admin_v3_mutex_stats_proto_upb_file_layout,
    "envoy/admin/v3/mutex_stats.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
