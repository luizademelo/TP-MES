
#include "upb/reflection/def.h"
#include "envoy/config/core/v3/grpc_method_list.upbdefs.h"
#include "envoy/config/core/v3/grpc_method_list.upb_minitable.h"

extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[573] = {
    '\n', '+', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'g',
    'r', 'p', 'c', '_', 'm', 'e', 't', 'h', 'o', 'd', '_', 'l',
    'i', 's', 't', '.', 'p', 'r', 'o', 't', 'o', '\022', '\024', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'c', 'o', 'r', 'e', '.', 'v', '3', '\032', '\035', 'u', 'd', 'p',
    'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n',
    's', '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o',
    't', 'o', '\032', '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r',
    's', 'i', 'o', 'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't',
    'o', '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/',
    'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o',
    't', 'o', '\"', '\212', '\002', '\n', '\016', 'G', 'r', 'p', 'c', 'M',
    'e', 't', 'h', 'o', 'd', 'L', 'i', 's', 't', '\022', 'H', '\n',
    '\010', 's', 'e', 'r', 'v', 'i', 'c', 'e', 's', '\030', '\001', ' ',
    '\003', '(', '\013', '2', ',', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.',
    'v', '3', '.', 'G', 'r', 'p', 'c', 'M', 'e', 't', 'h', 'o',
    'd', 'L', 'i', 's', 't', '.', 'S', 'e', 'r', 'v', 'i', 'c',
    'e', 'R', '\010', 's', 'e', 'r', 'v', 'i', 'c', 'e', 's', '\032',
    '\204', '\001', '\n', '\007', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '\022',
    '\033', '\n', '\004', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001', '(',
    '\t', 'B', '\007', '\372', 'B', '\004', 'r', '\002', '\020', '\001', 'R', '\004',
    'n', 'a', 'm', 'e', '\022', '+', '\n', '\014', 'm', 'e', 't', 'h',
    'o', 'd', '_', 'n', 'a', 'm', 'e', 's', '\030', '\002', ' ', '\003',
    '(', '\t', 'B', '\010', '\372', 'B', '\005', '\222', '\001', '\002', '\010', '\001',
    'R', '\013', 'm', 'e', 't', 'h', 'o', 'd', 'N', 'a', 'm', 'e',
    's', ':', '/', '\232', '\305', '\210', '\036', '*', '\n', '(', 'e', 'n',
    'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.', 'c',
    'o', 'r', 'e', '.', 'G', 'r', 'p', 'c', 'M', 'e', 't', 'h',
    'o', 'd', 'L', 'i', 's', 't', '.', 'S', 'e', 'r', 'v', 'i',
    'c', 'e', ':', '\'', '\232', '\305', '\210', '\036', '\"', '\n', ' ', 'e',
    'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.',
    'c', 'o', 'r', 'e', '.', 'G', 'r', 'p', 'c', 'M', 'e', 't',
    'h', 'o', 'd', 'L', 'i', 's', 't', 'B', '\207', '\001', '\n', '\"',
    'i', 'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x',
    'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', 'B', '\023',
    'G', 'r', 'p', 'c', 'M', 'e', 't', 'h', 'o', 'd', 'L', 'i',
    's', 't', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', 'B', 'g',
    'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n',
    'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-',
    'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n',
    'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', ';', 'c',
    'o', 'r', 'e', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020',
    '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_core_v3_grpc_method_list_proto_upbdefinit = {
    deps,
    &envoy_config_core_v3_grpc_method_list_proto_upb_file_layout,
    "envoy/config/core/v3/grpc_method_list.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
