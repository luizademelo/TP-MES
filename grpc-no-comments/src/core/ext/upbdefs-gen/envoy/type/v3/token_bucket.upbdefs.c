
#include "upb/reflection/def.h"
#include "envoy/type/v3/token_bucket.upbdefs.h"
#include "envoy/type/v3/token_bucket.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_duration_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_wrappers_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[574] = {
    '\n', ' ', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'v', '3', '/', 't', 'o', 'k', 'e', 'n', '_', 'b', 'u',
    'c', 'k', 'e', 't', '.', 'p', 'r', 'o', 't', 'o', '\022', '\r',
    'e', 'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'v',
    '3', '\032', '\036', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r',
    'o', 't', 'o', 'b', 'u', 'f', '/', 'd', 'u', 'r', 'a', 't',
    'i', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032', '\036', 'g',
    'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b',
    'u', 'f', '/', 'w', 'r', 'a', 'p', 'p', 'e', 'r', 's', '.',
    'p', 'r', 'o', 't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/',
    'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/',
    's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i',
    'o', 'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a',
    'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o',
    '\"', '\357', '\001', '\n', '\013', 'T', 'o', 'k', 'e', 'n', 'B', 'u',
    'c', 'k', 'e', 't', '\022', '&', '\n', '\n', 'm', 'a', 'x', '_',
    't', 'o', 'k', 'e', 'n', 's', '\030', '\001', ' ', '\001', '(', '\r',
    'B', '\007', '\372', 'B', '\004', '*', '\002', ' ', '\000', 'R', '\t', 'm',
    'a', 'x', 'T', 'o', 'k', 'e', 'n', 's', '\022', 'M', '\n', '\017',
    't', 'o', 'k', 'e', 'n', 's', '_', 'p', 'e', 'r', '_', 'f',
    'i', 'l', 'l', '\030', '\002', ' ', '\001', '(', '\013', '2', '\034', '.',
    'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o',
    'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '3', '2', 'V', 'a',
    'l', 'u', 'e', 'B', '\007', '\372', 'B', '\004', '*', '\002', ' ', '\000',
    'R', '\r', 't', 'o', 'k', 'e', 'n', 's', 'P', 'e', 'r', 'F',
    'i', 'l', 'l', '\022', 'J', '\n', '\r', 'f', 'i', 'l', 'l', '_',
    'i', 'n', 't', 'e', 'r', 'v', 'a', 'l', '\030', '\003', ' ', '\001',
    '(', '\013', '2', '\031', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'D', 'u', 'r',
    'a', 't', 'i', 'o', 'n', 'B', '\n', '\372', 'B', '\007', '\252', '\001',
    '\004', '\010', '\001', '*', '\000', 'R', '\014', 'f', 'i', 'l', 'l', 'I',
    'n', 't', 'e', 'r', 'v', 'a', 'l', ':', '\035', '\232', '\305', '\210',
    '\036', '\030', '\n', '\026', 'e', 'n', 'v', 'o', 'y', '.', 't', 'y',
    'p', 'e', '.', 'T', 'o', 'k', 'e', 'n', 'B', 'u', 'c', 'k',
    'e', 't', 'B', 'v', '\n', '\033', 'i', 'o', '.', 'e', 'n', 'v',
    'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o',
    'y', '.', 't', 'y', 'p', 'e', '.', 'v', '3', 'B', '\020', 'T',
    'o', 'k', 'e', 'n', 'B', 'u', 'c', 'k', 'e', 't', 'P', 'r',
    'o', 't', 'o', 'P', '\001', 'Z', ';', 'g', 'i', 't', 'h', 'u',
    'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p',
    'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't',
    'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n',
    'v', 'o', 'y', '/', 't', 'y', 'p', 'e', '/', 'v', '3', ';',
    't', 'y', 'p', 'e', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002',
    '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[6] = {
    &google_protobuf_duration_proto_upbdefinit,
    &google_protobuf_wrappers_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_type_v3_token_bucket_proto_upbdefinit = {
    deps,
    &envoy_type_v3_token_bucket_proto_upb_file_layout,
    "envoy/type/v3/token_bucket.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
