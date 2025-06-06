
#include "upb/reflection/def.h"
#include "envoy/config/core/v3/backoff.upbdefs.h"
#include "envoy/config/core/v3/backoff.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_duration_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[534] = {
    '\n', '\"', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'b',
    'a', 'c', 'k', 'o', 'f', 'f', '.', 'p', 'r', 'o', 't', 'o',
    '\022', '\024', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '\032', '\036',
    'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o',
    'b', 'u', 'f', '/', 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n',
    '.', 'p', 'r', 'o', 't', 'o', '\032', '\035', 'u', 'd', 'p', 'a',
    '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't',
    'o', '\032', '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o',
    't', 'a', 't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r', 's',
    'i', 'o', 'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v',
    'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't',
    'o', '\"', '\323', '\001', '\n', '\017', 'B', 'a', 'c', 'k', 'o', 'f',
    'f', 'S', 't', 'r', 'a', 't', 'e', 'g', 'y', '\022', 'N', '\n',
    '\r', 'b', 'a', 's', 'e', '_', 'i', 'n', 't', 'e', 'r', 'v',
    'a', 'l', '\030', '\001', ' ', '\001', '(', '\013', '2', '\031', '.', 'g',
    'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b',
    'u', 'f', '.', 'D', 'u', 'r', 'a', 't', 'i', 'o', 'n', 'B',
    '\016', '\372', 'B', '\013', '\252', '\001', '\010', '\010', '\001', '2', '\004', '\020',
    '\300', '\204', '=', 'R', '\014', 'b', 'a', 's', 'e', 'I', 'n', 't',
    'e', 'r', 'v', 'a', 'l', '\022', 'F', '\n', '\014', 'm', 'a', 'x',
    '_', 'i', 'n', 't', 'e', 'r', 'v', 'a', 'l', '\030', '\002', ' ',
    '\001', '(', '\013', '2', '\031', '.', 'g', 'o', 'o', 'g', 'l', 'e',
    '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'D', 'u',
    'r', 'a', 't', 'i', 'o', 'n', 'B', '\010', '\372', 'B', '\005', '\252',
    '\001', '\002', '*', '\000', 'R', '\013', 'm', 'a', 'x', 'I', 'n', 't',
    'e', 'r', 'v', 'a', 'l', ':', '(', '\232', '\305', '\210', '\036', '#',
    '\n', '!', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.',
    'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'B', 'a', 'c', 'k',
    'o', 'f', 'f', 'S', 't', 'r', 'a', 't', 'e', 'g', 'y', 'B',
    '\200', '\001', '\n', '\"', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.',
    'v', '3', 'B', '\014', 'B', 'a', 'c', 'k', 'o', 'f', 'f', 'P',
    'r', 'o', 't', 'o', 'P', '\001', 'Z', 'B', 'g', 'i', 't', 'h',
    'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n',
    't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e',
    'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/',
    'c', 'o', 'r', 'e', '/', 'v', '3', ';', 'c', 'o', 'r', 'e',
    'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006',
    'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[5] = {
    &google_protobuf_duration_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_core_v3_backoff_proto_upbdefinit = {
    deps,
    &envoy_config_core_v3_backoff_proto_upb_file_layout,
    "envoy/config/core/v3/backoff.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
