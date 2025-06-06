
#include "upb/reflection/def.h"
#include "envoy/type/v3/hash_policy.upbdefs.h"
#include "envoy/type/v3/hash_policy.upb_minitable.h"

extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[572] = {
    '\n', '\037', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'v', '3', '/', 'h', 'a', 's', 'h', '_', 'p', 'o', 'l',
    'i', 'c', 'y', '.', 'p', 'r', 'o', 't', 'o', '\022', '\r', 'e',
    'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'v', '3',
    '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u',
    's', '.', 'p', 'r', 'o', 't', 'o', '\032', '!', 'u', 'd', 'p',
    'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n',
    's', '/', 'v', 'e', 'r', 's', 'i', 'o', 'n', 'i', 'n', 'g',
    '.', 'p', 'r', 'o', 't', 'o', '\032', '\027', 'v', 'a', 'l', 'i',
    'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't',
    'e', '.', 'p', 'r', 'o', 't', 'o', '\"', '\257', '\002', '\n', '\n',
    'H', 'a', 's', 'h', 'P', 'o', 'l', 'i', 'c', 'y', '\022', 'A',
    '\n', '\t', 's', 'o', 'u', 'r', 'c', 'e', '_', 'i', 'p', '\030',
    '\001', ' ', '\001', '(', '\013', '2', '\"', '.', 'e', 'n', 'v', 'o',
    'y', '.', 't', 'y', 'p', 'e', '.', 'v', '3', '.', 'H', 'a',
    's', 'h', 'P', 'o', 'l', 'i', 'c', 'y', '.', 'S', 'o', 'u',
    'r', 'c', 'e', 'I', 'p', 'H', '\000', 'R', '\010', 's', 'o', 'u',
    'r', 'c', 'e', 'I', 'p', '\022', 'J', '\n', '\014', 'f', 'i', 'l',
    't', 'e', 'r', '_', 's', 't', 'a', 't', 'e', '\030', '\002', ' ',
    '\001', '(', '\013', '2', '%', '.', 'e', 'n', 'v', 'o', 'y', '.',
    't', 'y', 'p', 'e', '.', 'v', '3', '.', 'H', 'a', 's', 'h',
    'P', 'o', 'l', 'i', 'c', 'y', '.', 'F', 'i', 'l', 't', 'e',
    'r', 'S', 't', 'a', 't', 'e', 'H', '\000', 'R', '\013', 'f', 'i',
    'l', 't', 'e', 'r', 'S', 't', 'a', 't', 'e', '\032', '1', '\n',
    '\010', 'S', 'o', 'u', 'r', 'c', 'e', 'I', 'p', ':', '%', '\232',
    '\305', '\210', '\036', ' ', '\n', '\036', 'e', 'n', 'v', 'o', 'y', '.',
    't', 'y', 'p', 'e', '.', 'H', 'a', 's', 'h', 'P', 'o', 'l',
    'i', 'c', 'y', '.', 'S', 'o', 'u', 'r', 'c', 'e', 'I', 'p',
    '\032', '(', '\n', '\013', 'F', 'i', 'l', 't', 'e', 'r', 'S', 't',
    'a', 't', 'e', '\022', '\031', '\n', '\003', 'k', 'e', 'y', '\030', '\001',
    ' ', '\001', '(', '\t', 'B', '\007', '\372', 'B', '\004', 'r', '\002', '\020',
    '\001', 'R', '\003', 'k', 'e', 'y', ':', '\034', '\232', '\305', '\210', '\036',
    '\027', '\n', '\025', 'e', 'n', 'v', 'o', 'y', '.', 't', 'y', 'p',
    'e', '.', 'H', 'a', 's', 'h', 'P', 'o', 'l', 'i', 'c', 'y',
    'B', '\027', '\n', '\020', 'p', 'o', 'l', 'i', 'c', 'y', '_', 's',
    'p', 'e', 'c', 'i', 'f', 'i', 'e', 'r', '\022', '\003', '\370', 'B',
    '\001', 'B', 'u', '\n', '\033', 'i', 'o', '.', 'e', 'n', 'v', 'o',
    'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 't', 'y', 'p', 'e', '.', 'v', '3', 'B', '\017', 'H', 'a',
    's', 'h', 'P', 'o', 'l', 'i', 'c', 'y', 'P', 'r', 'o', 't',
    'o', 'P', '\001', 'Z', ';', 'g', 'i', 't', 'h', 'u', 'b', '.',
    'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o',
    'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o',
    'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o',
    'y', '/', 't', 'y', 'p', 'e', '/', 'v', '3', ';', 't', 'y',
    'p', 'e', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002',
    'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_type_v3_hash_policy_proto_upbdefinit = {
    deps,
    &envoy_type_v3_hash_policy_proto_upb_file_layout,
    "envoy/type/v3/hash_policy.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
