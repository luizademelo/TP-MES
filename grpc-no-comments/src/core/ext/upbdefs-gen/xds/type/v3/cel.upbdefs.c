
#include "upb/reflection/def.h"
#include "xds/type/v3/cel.upbdefs.h"
#include "xds/type/v3/cel.upb_minitable.h"

extern _upb_DefPool_Init google_api_expr_v1alpha1_checked_proto_upbdefinit;
extern _upb_DefPool_Init google_api_expr_v1alpha1_syntax_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_wrappers_proto_upbdefinit;
extern _upb_DefPool_Init xds_annotations_v3_status_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[646] = {
    '\n', '\025', 'x', 'd', 's', '/', 't', 'y', 'p', 'e', '/', 'v',
    '3', '/', 'c', 'e', 'l', '.', 'p', 'r', 'o', 't', 'o', '\022',
    '\013', 'x', 'd', 's', '.', 't', 'y', 'p', 'e', '.', 'v', '3',
    '\032', '&', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'a', 'p', 'i',
    '/', 'e', 'x', 'p', 'r', '/', 'v', '1', 'a', 'l', 'p', 'h',
    'a', '1', '/', 'c', 'h', 'e', 'c', 'k', 'e', 'd', '.', 'p',
    'r', 'o', 't', 'o', '\032', '%', 'g', 'o', 'o', 'g', 'l', 'e',
    '/', 'a', 'p', 'i', '/', 'e', 'x', 'p', 'r', '/', 'v', '1',
    'a', 'l', 'p', 'h', 'a', '1', '/', 's', 'y', 'n', 't', 'a',
    'x', '.', 'p', 'r', 'o', 't', 'o', '\032', '\036', 'g', 'o', 'o',
    'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f',
    '/', 'w', 'r', 'a', 'p', 'p', 'e', 'r', 's', '.', 'p', 'r',
    'o', 't', 'o', '\032', '\037', 'x', 'd', 's', '/', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 'v', '3', '/',
    's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v',
    'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't',
    'o', '\"', '\273', '\001', '\n', '\r', 'C', 'e', 'l', 'E', 'x', 'p',
    'r', 'e', 's', 's', 'i', 'o', 'n', '\022', 'G', '\n', '\013', 'p',
    'a', 'r', 's', 'e', 'd', '_', 'e', 'x', 'p', 'r', '\030', '\001',
    ' ', '\001', '(', '\013', '2', '$', '.', 'g', 'o', 'o', 'g', 'l',
    'e', '.', 'a', 'p', 'i', '.', 'e', 'x', 'p', 'r', '.', 'v',
    '1', 'a', 'l', 'p', 'h', 'a', '1', '.', 'P', 'a', 'r', 's',
    'e', 'd', 'E', 'x', 'p', 'r', 'H', '\000', 'R', '\n', 'p', 'a',
    'r', 's', 'e', 'd', 'E', 'x', 'p', 'r', '\022', 'J', '\n', '\014',
    'c', 'h', 'e', 'c', 'k', 'e', 'd', '_', 'e', 'x', 'p', 'r',
    '\030', '\002', ' ', '\001', '(', '\013', '2', '%', '.', 'g', 'o', 'o',
    'g', 'l', 'e', '.', 'a', 'p', 'i', '.', 'e', 'x', 'p', 'r',
    '.', 'v', '1', 'a', 'l', 'p', 'h', 'a', '1', '.', 'C', 'h',
    'e', 'c', 'k', 'e', 'd', 'E', 'x', 'p', 'r', 'H', '\000', 'R',
    '\013', 'c', 'h', 'e', 'c', 'k', 'e', 'd', 'E', 'x', 'p', 'r',
    'B', '\025', '\n', '\016', 'e', 'x', 'p', 'r', '_', 's', 'p', 'e',
    'c', 'i', 'f', 'i', 'e', 'r', '\022', '\003', '\370', 'B', '\001', '\"',
    '\236', '\001', '\n', '\020', 'C', 'e', 'l', 'E', 'x', 't', 'r', 'a',
    'c', 't', 'S', 't', 'r', 'i', 'n', 'g', '\022', 'G', '\n', '\014',
    'e', 'x', 'p', 'r', '_', 'e', 'x', 't', 'r', 'a', 'c', 't',
    '\030', '\001', ' ', '\001', '(', '\013', '2', '\032', '.', 'x', 'd', 's',
    '.', 't', 'y', 'p', 'e', '.', 'v', '3', '.', 'C', 'e', 'l',
    'E', 'x', 'p', 'r', 'e', 's', 's', 'i', 'o', 'n', 'B', '\010',
    '\372', 'B', '\005', '\212', '\001', '\002', '\020', '\001', 'R', '\013', 'e', 'x',
    'p', 'r', 'E', 'x', 't', 'r', 'a', 'c', 't', '\022', 'A', '\n',
    '\r', 'd', 'e', 'f', 'a', 'u', 'l', 't', '_', 'v', 'a', 'l',
    'u', 'e', '\030', '\002', ' ', '\001', '(', '\013', '2', '\034', '.', 'g',
    'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b',
    'u', 'f', '.', 'S', 't', 'r', 'i', 'n', 'g', 'V', 'a', 'l',
    'u', 'e', 'R', '\014', 'd', 'e', 'f', 'a', 'u', 'l', 't', 'V',
    'a', 'l', 'u', 'e', 'B', 'P', '\n', '\026', 'c', 'o', 'm', '.',
    'g', 'i', 't', 'h', 'u', 'b', '.', 'x', 'd', 's', '.', 't',
    'y', 'p', 'e', '.', 'v', '3', 'B', '\010', 'C', 'e', 'l', 'P',
    'r', 'o', 't', 'o', 'P', '\001', 'Z', '\"', 'g', 'i', 't', 'h',
    'u', 'b', '.', 'c', 'o', 'm', '/', 'c', 'n', 'c', 'f', '/',
    'x', 'd', 's', '/', 'g', 'o', '/', 'x', 'd', 's', '/', 't',
    'y', 'p', 'e', '/', 'v', '3', '\322', '\306', '\244', '\341', '\006', '\002',
    '\010', '\001', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[6] = {
    &google_api_expr_v1alpha1_checked_proto_upbdefinit,
    &google_api_expr_v1alpha1_syntax_proto_upbdefinit,
    &google_protobuf_wrappers_proto_upbdefinit,
    &xds_annotations_v3_status_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_type_v3_cel_proto_upbdefinit = {
    deps,
    &xds_type_v3_cel_proto_upb_file_layout,
    "xds/type/v3/cel.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
