
#include "upb/reflection/def.h"
#include "envoy/extensions/clusters/aggregate/v3/cluster.upbdefs.h"
#include "envoy/extensions/clusters/aggregate/v3/cluster.upb_minitable.h"

extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[481] = {
    '\n', '4', 'e', 'n', 'v', 'o', 'y', '/', 'e', 'x', 't', 'e',
    'n', 's', 'i', 'o', 'n', 's', '/', 'c', 'l', 'u', 's', 't',
    'e', 'r', 's', '/', 'a', 'g', 'g', 'r', 'e', 'g', 'a', 't',
    'e', '/', 'v', '3', '/', 'c', 'l', 'u', 's', 't', 'e', 'r',
    '.', 'p', 'r', 'o', 't', 'o', '\022', '&', 'e', 'n', 'v', 'o',
    'y', '.', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 's',
    '.', 'c', 'l', 'u', 's', 't', 'e', 'r', 's', '.', 'a', 'g',
    'g', 'r', 'e', 'g', 'a', 't', 'e', '.', 'v', '3', '\032', '\035',
    'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't',
    'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u', 's', '.',
    'p', 'r', 'o', 't', 'o', '\032', '!', 'u', 'd', 'p', 'a', '/',
    'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/',
    'v', 'e', 'r', 's', 'i', 'o', 'n', 'i', 'n', 'g', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a',
    't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '.',
    'p', 'r', 'o', 't', 'o', '\"', 'r', '\n', '\r', 'C', 'l', 'u',
    's', 't', 'e', 'r', 'C', 'o', 'n', 'f', 'i', 'g', '\022', '$',
    '\n', '\010', 'c', 'l', 'u', 's', 't', 'e', 'r', 's', '\030', '\001',
    ' ', '\003', '(', '\t', 'B', '\010', '\372', 'B', '\005', '\222', '\001', '\002',
    '\010', '\001', 'R', '\010', 'c', 'l', 'u', 's', 't', 'e', 'r', 's',
    ':', ';', '\232', '\305', '\210', '\036', '6', '\n', '4', 'e', 'n', 'v',
    'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'l',
    'u', 's', 't', 'e', 'r', '.', 'a', 'g', 'g', 'r', 'e', 'g',
    'a', 't', 'e', '.', 'v', '2', 'a', 'l', 'p', 'h', 'a', '.',
    'C', 'l', 'u', 's', 't', 'e', 'r', 'C', 'o', 'n', 'f', 'i',
    'g', 'B', '\251', '\001', '\n', '4', 'i', 'o', '.', 'e', 'n', 'v',
    'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o',
    'y', '.', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 's',
    '.', 'c', 'l', 'u', 's', 't', 'e', 'r', 's', '.', 'a', 'g',
    'g', 'r', 'e', 'g', 'a', 't', 'e', '.', 'v', '3', 'B', '\014',
    'C', 'l', 'u', 's', 't', 'e', 'r', 'P', 'r', 'o', 't', 'o',
    'P', '\001', 'Z', 'Y', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c',
    'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x',
    'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l',
    '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y',
    '/', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 's', '/',
    'c', 'l', 'u', 's', 't', 'e', 'r', 's', '/', 'a', 'g', 'g',
    'r', 'e', 'g', 'a', 't', 'e', '/', 'v', '3', ';', 'a', 'g',
    'g', 'r', 'e', 'g', 'a', 't', 'e', 'v', '3', '\272', '\200', '\310',
    '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o',
    '3',
};

static _upb_DefPool_Init *deps[4] = {
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_extensions_clusters_aggregate_v3_cluster_proto_upbdefinit = {
    deps,
    &envoy_extensions_clusters_aggregate_v3_cluster_proto_upb_file_layout,
    "envoy/extensions/clusters/aggregate/v3/cluster.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
