
#include "upb/reflection/def.h"
#include "envoy/type/http/v3/path_transformation.upbdefs.h"
#include "envoy/type/http/v3/path_transformation.upb_minitable.h"

extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[685] = {
    '\n', ',', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'h', 't', 't', 'p', '/', 'v', '3', '/', 'p', 'a', 't',
    'h', '_', 't', 'r', 'a', 'n', 's', 'f', 'o', 'r', 'm', 'a',
    't', 'i', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\022', '\022',
    'e', 'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'h',
    't', 't', 'p', '.', 'v', '3', '\032', '\035', 'u', 'd', 'p', 'a',
    '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't',
    'o', '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/',
    'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o',
    't', 'o', '\"', '\236', '\003', '\n', '\022', 'P', 'a', 't', 'h', 'T',
    'r', 'a', 'n', 's', 'f', 'o', 'r', 'm', 'a', 't', 'i', 'o',
    'n', '\022', 'P', '\n', '\n', 'o', 'p', 'e', 'r', 'a', 't', 'i',
    'o', 'n', 's', '\030', '\001', ' ', '\003', '(', '\013', '2', '0', '.',
    'e', 'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'h',
    't', 't', 'p', '.', 'v', '3', '.', 'P', 'a', 't', 'h', 'T',
    'r', 'a', 'n', 's', 'f', 'o', 'r', 'm', 'a', 't', 'i', 'o',
    'n', '.', 'O', 'p', 'e', 'r', 'a', 't', 'i', 'o', 'n', 'R',
    '\n', 'o', 'p', 'e', 'r', 'a', 't', 'i', 'o', 'n', 's', '\032',
    '\265', '\002', '\n', '\t', 'O', 'p', 'e', 'r', 'a', 't', 'i', 'o',
    'n', '\022', '~', '\n', '\027', 'n', 'o', 'r', 'm', 'a', 'l', 'i',
    'z', 'e', '_', 'p', 'a', 't', 'h', '_', 'r', 'f', 'c', '_',
    '3', '9', '8', '6', '\030', '\002', ' ', '\001', '(', '\013', '2', 'E',
    '.', 'e', 'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.',
    'h', 't', 't', 'p', '.', 'v', '3', '.', 'P', 'a', 't', 'h',
    'T', 'r', 'a', 'n', 's', 'f', 'o', 'r', 'm', 'a', 't', 'i',
    'o', 'n', '.', 'O', 'p', 'e', 'r', 'a', 't', 'i', 'o', 'n',
    '.', 'N', 'o', 'r', 'm', 'a', 'l', 'i', 'z', 'e', 'P', 'a',
    't', 'h', 'R', 'F', 'C', '3', '9', '8', '6', 'H', '\000', 'R',
    '\024', 'n', 'o', 'r', 'm', 'a', 'l', 'i', 'z', 'e', 'P', 'a',
    't', 'h', 'R', 'f', 'c', '3', '9', '8', '6', '\022', 'd', '\n',
    '\r', 'm', 'e', 'r', 'g', 'e', '_', 's', 'l', 'a', 's', 'h',
    'e', 's', '\030', '\003', ' ', '\001', '(', '\013', '2', '=', '.', 'e',
    'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'h', 't',
    't', 'p', '.', 'v', '3', '.', 'P', 'a', 't', 'h', 'T', 'r',
    'a', 'n', 's', 'f', 'o', 'r', 'm', 'a', 't', 'i', 'o', 'n',
    '.', 'O', 'p', 'e', 'r', 'a', 't', 'i', 'o', 'n', '.', 'M',
    'e', 'r', 'g', 'e', 'S', 'l', 'a', 's', 'h', 'e', 's', 'H',
    '\000', 'R', '\014', 'm', 'e', 'r', 'g', 'e', 'S', 'l', 'a', 's',
    'h', 'e', 's', '\032', '\026', '\n', '\024', 'N', 'o', 'r', 'm', 'a',
    'l', 'i', 'z', 'e', 'P', 'a', 't', 'h', 'R', 'F', 'C', '3',
    '9', '8', '6', '\032', '\016', '\n', '\014', 'M', 'e', 'r', 'g', 'e',
    'S', 'l', 'a', 's', 'h', 'e', 's', 'B', '\032', '\n', '\023', 'o',
    'p', 'e', 'r', 'a', 't', 'i', 'o', 'n', '_', 's', 'p', 'e',
    'c', 'i', 'f', 'i', 'e', 'r', '\022', '\003', '\370', 'B', '\001', 'B',
    '\207', '\001', '\n', ' ', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.',
    't', 'y', 'p', 'e', '.', 'h', 't', 't', 'p', '.', 'v', '3',
    'B', '\027', 'P', 'a', 't', 'h', 'T', 'r', 'a', 'n', 's', 'f',
    'o', 'r', 'm', 'a', 't', 'i', 'o', 'n', 'P', 'r', 'o', 't',
    'o', 'P', '\001', 'Z', '@', 'g', 'i', 't', 'h', 'u', 'b', '.',
    'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o',
    'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o',
    'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o',
    'y', '/', 't', 'y', 'p', 'e', '/', 'h', 't', 't', 'p', '/',
    'v', '3', ';', 'h', 't', 't', 'p', 'v', '3', '\272', '\200', '\310',
    '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o',
    '3',
};

static _upb_DefPool_Init *deps[3] = {
    &udpa_annotations_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_type_http_v3_path_transformation_proto_upbdefinit = {
    deps,
    &envoy_type_http_v3_path_transformation_proto_upb_file_layout,
    "envoy/type/http/v3/path_transformation.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
