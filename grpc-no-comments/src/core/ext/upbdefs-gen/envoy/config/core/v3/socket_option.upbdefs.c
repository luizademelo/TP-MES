
#include "upb/reflection/def.h"
#include "envoy/config/core/v3/socket_option.upbdefs.h"
#include "envoy/config/core/v3/socket_option.upb_minitable.h"

extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[1025] = {
    '\n', '(', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 's',
    'o', 'c', 'k', 'e', 't', '_', 'o', 'p', 't', 'i', 'o', 'n',
    '.', 'p', 'r', 'o', 't', 'o', '\022', '\024', 'e', 'n', 'v', 'o',
    'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r',
    'e', '.', 'v', '3', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a',
    'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's',
    't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i', 'o',
    'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027',
    'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l',
    'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"',
    '\357', '\004', '\n', '\014', 'S', 'o', 'c', 'k', 'e', 't', 'O', 'p',
    't', 'i', 'o', 'n', '\022', ' ', '\n', '\013', 'd', 'e', 's', 'c',
    'r', 'i', 'p', 't', 'i', 'o', 'n', '\030', '\001', ' ', '\001', '(',
    '\t', 'R', '\013', 'd', 'e', 's', 'c', 'r', 'i', 'p', 't', 'i',
    'o', 'n', '\022', '\024', '\n', '\005', 'l', 'e', 'v', 'e', 'l', '\030',
    '\002', ' ', '\001', '(', '\003', 'R', '\005', 'l', 'e', 'v', 'e', 'l',
    '\022', '\022', '\n', '\004', 'n', 'a', 'm', 'e', '\030', '\003', ' ', '\001',
    '(', '\003', 'R', '\004', 'n', 'a', 'm', 'e', '\022', '\035', '\n', '\t',
    'i', 'n', 't', '_', 'v', 'a', 'l', 'u', 'e', '\030', '\004', ' ',
    '\001', '(', '\003', 'H', '\000', 'R', '\010', 'i', 'n', 't', 'V', 'a',
    'l', 'u', 'e', '\022', '\035', '\n', '\t', 'b', 'u', 'f', '_', 'v',
    'a', 'l', 'u', 'e', '\030', '\005', ' ', '\001', '(', '\014', 'H', '\000',
    'R', '\010', 'b', 'u', 'f', 'V', 'a', 'l', 'u', 'e', '\022', 'N',
    '\n', '\005', 's', 't', 'a', 't', 'e', '\030', '\006', ' ', '\001', '(',
    '\016', '2', '.', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o',
    'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3',
    '.', 'S', 'o', 'c', 'k', 'e', 't', 'O', 'p', 't', 'i', 'o',
    'n', '.', 'S', 'o', 'c', 'k', 'e', 't', 'S', 't', 'a', 't',
    'e', 'B', '\010', '\372', 'B', '\005', '\202', '\001', '\002', '\020', '\001', 'R',
    '\005', 's', 't', 'a', 't', 'e', '\022', 'A', '\n', '\004', 't', 'y',
    'p', 'e', '\030', '\007', ' ', '\001', '(', '\013', '2', '-', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'S', 'o', 'c', 'k',
    'e', 't', 'O', 'p', 't', 'i', 'o', 'n', '.', 'S', 'o', 'c',
    'k', 'e', 't', 'T', 'y', 'p', 'e', 'R', '\004', 't', 'y', 'p',
    'e', '\032', '\304', '\001', '\n', '\n', 'S', 'o', 'c', 'k', 'e', 't',
    'T', 'y', 'p', 'e', '\022', 'L', '\n', '\006', 's', 't', 'r', 'e',
    'a', 'm', '\030', '\001', ' ', '\001', '(', '\013', '2', '4', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'S', 'o', 'c', 'k',
    'e', 't', 'O', 'p', 't', 'i', 'o', 'n', '.', 'S', 'o', 'c',
    'k', 'e', 't', 'T', 'y', 'p', 'e', '.', 'S', 't', 'r', 'e',
    'a', 'm', 'R', '\006', 's', 't', 'r', 'e', 'a', 'm', '\022', 'R',
    '\n', '\010', 'd', 'a', 't', 'a', 'g', 'r', 'a', 'm', '\030', '\002',
    ' ', '\001', '(', '\013', '2', '6', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e',
    '.', 'v', '3', '.', 'S', 'o', 'c', 'k', 'e', 't', 'O', 'p',
    't', 'i', 'o', 'n', '.', 'S', 'o', 'c', 'k', 'e', 't', 'T',
    'y', 'p', 'e', '.', 'D', 'a', 't', 'a', 'g', 'r', 'a', 'm',
    'R', '\010', 'd', 'a', 't', 'a', 'g', 'r', 'a', 'm', '\032', '\010',
    '\n', '\006', 'S', 't', 'r', 'e', 'a', 'm', '\032', '\n', '\n', '\010',
    'D', 'a', 't', 'a', 'g', 'r', 'a', 'm', '\"', 'F', '\n', '\013',
    'S', 'o', 'c', 'k', 'e', 't', 'S', 't', 'a', 't', 'e', '\022',
    '\021', '\n', '\r', 'S', 'T', 'A', 'T', 'E', '_', 'P', 'R', 'E',
    'B', 'I', 'N', 'D', '\020', '\000', '\022', '\017', '\n', '\013', 'S', 'T',
    'A', 'T', 'E', '_', 'B', 'O', 'U', 'N', 'D', '\020', '\001', '\022',
    '\023', '\n', '\017', 'S', 'T', 'A', 'T', 'E', '_', 'L', 'I', 'S',
    'T', 'E', 'N', 'I', 'N', 'G', '\020', '\002', ':', '%', '\232', '\305',
    '\210', '\036', ' ', '\n', '\036', 'e', 'n', 'v', 'o', 'y', '.', 'a',
    'p', 'i', '.', 'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'S',
    'o', 'c', 'k', 'e', 't', 'O', 'p', 't', 'i', 'o', 'n', 'B',
    '\014', '\n', '\005', 'v', 'a', 'l', 'u', 'e', '\022', '\003', '\370', 'B',
    '\001', '\"', 'b', '\n', '\025', 'S', 'o', 'c', 'k', 'e', 't', 'O',
    'p', 't', 'i', 'o', 'n', 's', 'O', 'v', 'e', 'r', 'r', 'i',
    'd', 'e', '\022', 'I', '\n', '\016', 's', 'o', 'c', 'k', 'e', 't',
    '_', 'o', 'p', 't', 'i', 'o', 'n', 's', '\030', '\001', ' ', '\003',
    '(', '\013', '2', '\"', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v',
    '3', '.', 'S', 'o', 'c', 'k', 'e', 't', 'O', 'p', 't', 'i',
    'o', 'n', 'R', '\r', 's', 'o', 'c', 'k', 'e', 't', 'O', 'p',
    't', 'i', 'o', 'n', 's', 'B', '\205', '\001', '\n', '\"', 'i', 'o',
    '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g',
    '.', 'c', 'o', 'r', 'e', '.', 'v', '3', 'B', '\021', 'S', 'o',
    'c', 'k', 'e', 't', 'O', 'p', 't', 'i', 'o', 'n', 'P', 'r',
    'o', 't', 'o', 'P', '\001', 'Z', 'B', 'g', 'i', 't', 'h', 'u',
    'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p',
    'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't',
    'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n',
    'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c',
    'o', 'r', 'e', '/', 'v', '3', ';', 'c', 'o', 'r', 'e', 'v',
    '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p',
    'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_core_v3_socket_option_proto_upbdefinit = {
    deps,
    &envoy_config_core_v3_socket_option_proto_upb_file_layout,
    "envoy/config/core/v3/socket_option.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
