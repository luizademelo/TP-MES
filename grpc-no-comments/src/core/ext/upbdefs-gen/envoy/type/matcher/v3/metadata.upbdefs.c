
#include "upb/reflection/def.h"
#include "envoy/type/matcher/v3/metadata.upbdefs.h"
#include "envoy/type/matcher/v3/metadata.upb_minitable.h"

extern _upb_DefPool_Init envoy_type_matcher_v3_value_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[718] = {
    '\n', '$', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'm', 'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3', '/',
    'm', 'e', 't', 'a', 'd', 'a', 't', 'a', '.', 'p', 'r', 'o',
    't', 'o', '\022', '\025', 'e', 'n', 'v', 'o', 'y', '.', 't', 'y',
    'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'v',
    '3', '\032', '!', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p',
    'e', '/', 'm', 'a', 't', 'c', 'h', 'e', 'r', '/', 'v', '3',
    '/', 'v', 'a', 'l', 'u', 'e', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u',
    's', '.', 'p', 'r', 'o', 't', 'o', '\032', '!', 'u', 'd', 'p',
    'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n',
    's', '/', 'v', 'e', 'r', 's', 'i', 'o', 'n', 'i', 'n', 'g',
    '.', 'p', 'r', 'o', 't', 'o', '\032', '\027', 'v', 'a', 'l', 'i',
    'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't',
    'e', '.', 'p', 'r', 'o', 't', 'o', '\"', '\377', '\002', '\n', '\017',
    'M', 'e', 't', 'a', 'd', 'a', 't', 'a', 'M', 'a', 't', 'c',
    'h', 'e', 'r', '\022', '\037', '\n', '\006', 'f', 'i', 'l', 't', 'e',
    'r', '\030', '\001', ' ', '\001', '(', '\t', 'B', '\007', '\372', 'B', '\004',
    'r', '\002', '\020', '\001', 'R', '\006', 'f', 'i', 'l', 't', 'e', 'r',
    '\022', 'P', '\n', '\004', 'p', 'a', 't', 'h', '\030', '\002', ' ', '\003',
    '(', '\013', '2', '2', '.', 'e', 'n', 'v', 'o', 'y', '.', 't',
    'y', 'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.',
    'v', '3', '.', 'M', 'e', 't', 'a', 'd', 'a', 't', 'a', 'M',
    'a', 't', 'c', 'h', 'e', 'r', '.', 'P', 'a', 't', 'h', 'S',
    'e', 'g', 'm', 'e', 'n', 't', 'B', '\010', '\372', 'B', '\005', '\222',
    '\001', '\002', '\010', '\001', 'R', '\004', 'p', 'a', 't', 'h', '\022', 'C',
    '\n', '\005', 'v', 'a', 'l', 'u', 'e', '\030', '\003', ' ', '\001', '(',
    '\013', '2', '#', '.', 'e', 'n', 'v', 'o', 'y', '.', 't', 'y',
    'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'v',
    '3', '.', 'V', 'a', 'l', 'u', 'e', 'M', 'a', 't', 'c', 'h',
    'e', 'r', 'B', '\010', '\372', 'B', '\005', '\212', '\001', '\002', '\020', '\001',
    'R', '\005', 'v', 'a', 'l', 'u', 'e', '\022', '\026', '\n', '\006', 'i',
    'n', 'v', 'e', 'r', 't', '\030', '\004', ' ', '\001', '(', '\010', 'R',
    '\006', 'i', 'n', 'v', 'e', 'r', 't', '\032', 'q', '\n', '\013', 'P',
    'a', 't', 'h', 'S', 'e', 'g', 'm', 'e', 'n', 't', '\022', '\033',
    '\n', '\003', 'k', 'e', 'y', '\030', '\001', ' ', '\001', '(', '\t', 'B',
    '\007', '\372', 'B', '\004', 'r', '\002', '\020', '\001', 'H', '\000', 'R', '\003',
    'k', 'e', 'y', ':', '5', '\232', '\305', '\210', '\036', '0', '\n', '.',
    'e', 'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'm',
    'a', 't', 'c', 'h', 'e', 'r', '.', 'M', 'e', 't', 'a', 'd',
    'a', 't', 'a', 'M', 'a', 't', 'c', 'h', 'e', 'r', '.', 'P',
    'a', 't', 'h', 'S', 'e', 'g', 'm', 'e', 'n', 't', 'B', '\016',
    '\n', '\007', 's', 'e', 'g', 'm', 'e', 'n', 't', '\022', '\003', '\370',
    'B', '\001', ':', ')', '\232', '\305', '\210', '\036', '$', '\n', '\"', 'e',
    'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'm', 'a',
    't', 'c', 'h', 'e', 'r', '.', 'M', 'e', 't', 'a', 'd', 'a',
    't', 'a', 'M', 'a', 't', 'c', 'h', 'e', 'r', 'B', '\206', '\001',
    '\n', '#', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r',
    'o', 'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 't', 'y',
    'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'v',
    '3', 'B', '\r', 'M', 'e', 't', 'a', 'd', 'a', 't', 'a', 'P',
    'r', 'o', 't', 'o', 'P', '\001', 'Z', 'F', 'g', 'i', 't', 'h',
    'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n',
    't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e',
    'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e', '/', 'm', 'a',
    't', 'c', 'h', 'e', 'r', '/', 'v', '3', ';', 'm', 'a', 't',
    'c', 'h', 'e', 'r', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002',
    '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[5] = {
    &envoy_type_matcher_v3_value_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_type_matcher_v3_metadata_proto_upbdefinit = {
    deps,
    &envoy_type_matcher_v3_metadata_proto_upb_file_layout,
    "envoy/type/matcher/v3/metadata.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
