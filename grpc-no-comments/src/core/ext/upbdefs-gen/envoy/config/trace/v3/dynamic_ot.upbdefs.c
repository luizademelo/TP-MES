
#include "upb/reflection/def.h"
#include "envoy/config/trace/v3/dynamic_ot.upbdefs.h"
#include "envoy/config/trace/v3/dynamic_ot.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_struct_proto_upbdefinit;
extern _upb_DefPool_Init envoy_annotations_deprecation_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_migrate_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[634] = {
    '\n', '&', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 't', 'r', 'a', 'c', 'e', '/', 'v', '3', '/',
    'd', 'y', 'n', 'a', 'm', 'i', 'c', '_', 'o', 't', '.', 'p',
    'r', 'o', 't', 'o', '\022', '\025', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'r', 'a', 'c', 'e',
    '.', 'v', '3', '\032', '\034', 'g', 'o', 'o', 'g', 'l', 'e', '/',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 's', 't', 'r',
    'u', 'c', 't', '.', 'p', 'r', 'o', 't', 'o', '\032', '#', 'e',
    'n', 'v', 'o', 'y', '/', 'a', 'n', 'n', 'o', 't', 'a', 't',
    'i', 'o', 'n', 's', '/', 'd', 'e', 'p', 'r', 'e', 'c', 'a',
    't', 'i', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032', '\036',
    'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't',
    'i', 'o', 'n', 's', '/', 'm', 'i', 'g', 'r', 'a', 't', 'e',
    '.', 'p', 'r', 'o', 't', 'o', '\032', '\035', 'u', 'd', 'p', 'a',
    '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't',
    'o', '\032', '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o',
    't', 'a', 't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r', 's',
    'i', 'o', 'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v',
    'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't',
    'o', '\"', '\267', '\001', '\n', '\017', 'D', 'y', 'n', 'a', 'm', 'i',
    'c', 'O', 't', 'C', 'o', 'n', 'f', 'i', 'g', '\022', '2', '\n',
    '\007', 'l', 'i', 'b', 'r', 'a', 'r', 'y', '\030', '\001', ' ', '\001',
    '(', '\t', 'B', '\030', '\030', '\001', '\372', 'B', '\004', 'r', '\002', '\020',
    '\001', '\222', '\307', '\206', '\330', '\004', '\003', '3', '.', '0', '\270', '\356',
    '\362', '\322', '\005', '\001', 'R', '\007', 'l', 'i', 'b', 'r', 'a', 'r',
    'y', '\022', 'B', '\n', '\006', 'c', 'o', 'n', 'f', 'i', 'g', '\030',
    '\002', ' ', '\001', '(', '\013', '2', '\027', '.', 'g', 'o', 'o', 'g',
    'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.',
    'S', 't', 'r', 'u', 'c', 't', 'B', '\021', '\030', '\001', '\222', '\307',
    '\206', '\330', '\004', '\003', '3', '.', '0', '\270', '\356', '\362', '\322', '\005',
    '\001', 'R', '\006', 'c', 'o', 'n', 'f', 'i', 'g', ':', ',', '\232',
    '\305', '\210', '\036', '\'', '\n', '%', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'r', 'a', 'c', 'e',
    '.', 'v', '2', '.', 'D', 'y', 'n', 'a', 'm', 'i', 'c', 'O',
    't', 'C', 'o', 'n', 'f', 'i', 'g', 'B', '\270', '\001', '\n', '#',
    'i', 'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x',
    'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 't', 'r', 'a', 'c', 'e', '.', 'v', '3', 'B',
    '\016', 'D', 'y', 'n', 'a', 'm', 'i', 'c', 'O', 't', 'P', 'r',
    'o', 't', 'o', 'P', '\001', 'Z', 'D', 'g', 'i', 't', 'h', 'u',
    'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p',
    'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't',
    'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n',
    'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 't',
    'r', 'a', 'c', 'e', '/', 'v', '3', ';', 't', 'r', 'a', 'c',
    'e', 'v', '3', '\362', '\230', '\376', '\217', '\005', '-', '\022', '+', 'e',
    'n', 'v', 'o', 'y', '.', 'e', 'x', 't', 'e', 'n', 's', 'i',
    'o', 'n', 's', '.', 't', 'r', 'a', 'c', 'e', 'r', 's', '.',
    'd', 'y', 'n', 'a', 'm', 'i', 'c', '_', 'o', 't', '.', 'v',
    '4', 'a', 'l', 'p', 'h', 'a', '\272', '\200', '\310', '\321', '\006', '\002',
    '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[7] = {
    &google_protobuf_struct_proto_upbdefinit,
    &envoy_annotations_deprecation_proto_upbdefinit,
    &udpa_annotations_migrate_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_trace_v3_dynamic_ot_proto_upbdefinit = {
    deps,
    &envoy_config_trace_v3_dynamic_ot_proto_upb_file_layout,
    "envoy/config/trace/v3/dynamic_ot.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
