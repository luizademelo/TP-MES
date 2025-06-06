
#include "upb/reflection/def.h"
#include "envoy/admin/v3/config_dump.upbdefs.h"
#include "envoy/admin/v3/config_dump.upb_minitable.h"

extern _upb_DefPool_Init envoy_admin_v3_config_dump_shared_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_timestamp_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;

static const char descriptor[1648] = {
    '\n', ' ', 'e', 'n', 'v', 'o', 'y', '/', 'a', 'd', 'm', 'i',
    'n', '/', 'v', '3', '/', 'c', 'o', 'n', 'f', 'i', 'g', '_',
    'd', 'u', 'm', 'p', '.', 'p', 'r', 'o', 't', 'o', '\022', '\016',
    'e', 'n', 'v', 'o', 'y', '.', 'a', 'd', 'm', 'i', 'n', '.',
    'v', '3', '\032', '\'', 'e', 'n', 'v', 'o', 'y', '/', 'a', 'd',
    'm', 'i', 'n', '/', 'v', '3', '/', 'c', 'o', 'n', 'f', 'i',
    'g', '_', 'd', 'u', 'm', 'p', '_', 's', 'h', 'a', 'r', 'e',
    'd', '.', 'p', 'r', 'o', 't', 'o', '\032', ')', 'e', 'n', 'v',
    'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'b', 'o',
    'o', 't', 's', 't', 'r', 'a', 'p', '/', 'v', '3', '/', 'b',
    'o', 'o', 't', 's', 't', 'r', 'a', 'p', '.', 'p', 'r', 'o',
    't', 'o', '\032', '\031', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p',
    'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'a', 'n', 'y', '.',
    'p', 'r', 'o', 't', 'o', '\032', '\037', 'g', 'o', 'o', 'g', 'l',
    'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 't',
    'i', 'm', 'e', 's', 't', 'a', 'm', 'p', '.', 'p', 'r', 'o',
    't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a',
    't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '!', 'u',
    'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i', 'o', 'n', 'i',
    'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\"', 'c', '\n', '\n',
    'C', 'o', 'n', 'f', 'i', 'g', 'D', 'u', 'm', 'p', '\022', '.',
    '\n', '\007', 'c', 'o', 'n', 'f', 'i', 'g', 's', '\030', '\001', ' ',
    '\003', '(', '\013', '2', '\024', '.', 'g', 'o', 'o', 'g', 'l', 'e',
    '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'A', 'n',
    'y', 'R', '\007', 'c', 'o', 'n', 'f', 'i', 'g', 's', ':', '%',
    '\232', '\305', '\210', '\036', ' ', '\n', '\036', 'e', 'n', 'v', 'o', 'y',
    '.', 'a', 'd', 'm', 'i', 'n', '.', 'v', '2', 'a', 'l', 'p',
    'h', 'a', '.', 'C', 'o', 'n', 'f', 'i', 'g', 'D', 'u', 'm',
    'p', '\"', '\310', '\001', '\n', '\023', 'B', 'o', 'o', 't', 's', 't',
    'r', 'a', 'p', 'C', 'o', 'n', 'f', 'i', 'g', 'D', 'u', 'm',
    'p', '\022', 'B', '\n', '\t', 'b', 'o', 'o', 't', 's', 't', 'r',
    'a', 'p', '\030', '\001', ' ', '\001', '(', '\013', '2', '$', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'b', 'o', 'o', 't', 's', 't', 'r', 'a', 'p', '.', 'v', '3',
    '.', 'B', 'o', 'o', 't', 's', 't', 'r', 'a', 'p', 'R', '\t',
    'b', 'o', 'o', 't', 's', 't', 'r', 'a', 'p', '\022', '=', '\n',
    '\014', 'l', 'a', 's', 't', '_', 'u', 'p', 'd', 'a', 't', 'e',
    'd', '\030', '\002', ' ', '\001', '(', '\013', '2', '\032', '.', 'g', 'o',
    'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u',
    'f', '.', 'T', 'i', 'm', 'e', 's', 't', 'a', 'm', 'p', 'R',
    '\013', 'l', 'a', 's', 't', 'U', 'p', 'd', 'a', 't', 'e', 'd',
    ':', '.', '\232', '\305', '\210', '\036', ')', '\n', '\'', 'e', 'n', 'v',
    'o', 'y', '.', 'a', 'd', 'm', 'i', 'n', '.', 'v', '2', 'a',
    'l', 'p', 'h', 'a', '.', 'B', 'o', 'o', 't', 's', 't', 'r',
    'a', 'p', 'C', 'o', 'n', 'f', 'i', 'g', 'D', 'u', 'm', 'p',
    '\"', '\267', '\007', '\n', '\021', 'S', 'e', 'c', 'r', 'e', 't', 's',
    'C', 'o', 'n', 'f', 'i', 'g', 'D', 'u', 'm', 'p', '\022', 'U',
    '\n', '\016', 's', 't', 'a', 't', 'i', 'c', '_', 's', 'e', 'c',
    'r', 'e', 't', 's', '\030', '\001', ' ', '\003', '(', '\013', '2', '.',
    '.', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'd', 'm', 'i', 'n',
    '.', 'v', '3', '.', 'S', 'e', 'c', 'r', 'e', 't', 's', 'C',
    'o', 'n', 'f', 'i', 'g', 'D', 'u', 'm', 'p', '.', 'S', 't',
    'a', 't', 'i', 'c', 'S', 'e', 'c', 'r', 'e', 't', 'R', '\r',
    's', 't', 'a', 't', 'i', 'c', 'S', 'e', 'c', 'r', 'e', 't',
    's', '\022', 'e', '\n', '\026', 'd', 'y', 'n', 'a', 'm', 'i', 'c',
    '_', 'a', 'c', 't', 'i', 'v', 'e', '_', 's', 'e', 'c', 'r',
    'e', 't', 's', '\030', '\002', ' ', '\003', '(', '\013', '2', '/', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'a', 'd', 'm', 'i', 'n', '.',
    'v', '3', '.', 'S', 'e', 'c', 'r', 'e', 't', 's', 'C', 'o',
    'n', 'f', 'i', 'g', 'D', 'u', 'm', 'p', '.', 'D', 'y', 'n',
    'a', 'm', 'i', 'c', 'S', 'e', 'c', 'r', 'e', 't', 'R', '\024',
    'd', 'y', 'n', 'a', 'm', 'i', 'c', 'A', 'c', 't', 'i', 'v',
    'e', 'S', 'e', 'c', 'r', 'e', 't', 's', '\022', 'g', '\n', '\027',
    'd', 'y', 'n', 'a', 'm', 'i', 'c', '_', 'w', 'a', 'r', 'm',
    'i', 'n', 'g', '_', 's', 'e', 'c', 'r', 'e', 't', 's', '\030',
    '\003', ' ', '\003', '(', '\013', '2', '/', '.', 'e', 'n', 'v', 'o',
    'y', '.', 'a', 'd', 'm', 'i', 'n', '.', 'v', '3', '.', 'S',
    'e', 'c', 'r', 'e', 't', 's', 'C', 'o', 'n', 'f', 'i', 'g',
    'D', 'u', 'm', 'p', '.', 'D', 'y', 'n', 'a', 'm', 'i', 'c',
    'S', 'e', 'c', 'r', 'e', 't', 'R', '\025', 'd', 'y', 'n', 'a',
    'm', 'i', 'c', 'W', 'a', 'r', 'm', 'i', 'n', 'g', 'S', 'e',
    'c', 'r', 'e', 't', 's', '\032', '\377', '\002', '\n', '\r', 'D', 'y',
    'n', 'a', 'm', 'i', 'c', 'S', 'e', 'c', 'r', 'e', 't', '\022',
    '\022', '\n', '\004', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001', '(',
    '\t', 'R', '\004', 'n', 'a', 'm', 'e', '\022', '!', '\n', '\014', 'v',
    'e', 'r', 's', 'i', 'o', 'n', '_', 'i', 'n', 'f', 'o', '\030',
    '\002', ' ', '\001', '(', '\t', 'R', '\013', 'v', 'e', 'r', 's', 'i',
    'o', 'n', 'I', 'n', 'f', 'o', '\022', '=', '\n', '\014', 'l', 'a',
    's', 't', '_', 'u', 'p', 'd', 'a', 't', 'e', 'd', '\030', '\003',
    ' ', '\001', '(', '\013', '2', '\032', '.', 'g', 'o', 'o', 'g', 'l',
    'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'T',
    'i', 'm', 'e', 's', 't', 'a', 'm', 'p', 'R', '\013', 'l', 'a',
    's', 't', 'U', 'p', 'd', 'a', 't', 'e', 'd', '\022', ',', '\n',
    '\006', 's', 'e', 'c', 'r', 'e', 't', '\030', '\004', ' ', '\001', '(',
    '\013', '2', '\024', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p',
    'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'A', 'n', 'y', 'R',
    '\006', 's', 'e', 'c', 'r', 'e', 't', '\022', 'C', '\n', '\013', 'e',
    'r', 'r', 'o', 'r', '_', 's', 't', 'a', 't', 'e', '\030', '\005',
    ' ', '\001', '(', '\013', '2', '\"', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'a', 'd', 'm', 'i', 'n', '.', 'v', '3', '.', 'U', 'p',
    'd', 'a', 't', 'e', 'F', 'a', 'i', 'l', 'u', 'r', 'e', 'S',
    't', 'a', 't', 'e', 'R', '\n', 'e', 'r', 'r', 'o', 'r', 'S',
    't', 'a', 't', 'e', '\022', 'I', '\n', '\r', 'c', 'l', 'i', 'e',
    'n', 't', '_', 's', 't', 'a', 't', 'u', 's', '\030', '\006', ' ',
    '\001', '(', '\016', '2', '$', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'a', 'd', 'm', 'i', 'n', '.', 'v', '3', '.', 'C', 'l', 'i',
    'e', 'n', 't', 'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'S',
    't', 'a', 't', 'u', 's', 'R', '\014', 'c', 'l', 'i', 'e', 'n',
    't', 'S', 't', 'a', 't', 'u', 's', ':', ':', '\232', '\305', '\210',
    '\036', '5', '\n', '3', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'd',
    'm', 'i', 'n', '.', 'v', '2', 'a', 'l', 'p', 'h', 'a', '.',
    'S', 'e', 'c', 'r', 'e', 't', 's', 'C', 'o', 'n', 'f', 'i',
    'g', 'D', 'u', 'm', 'p', '.', 'D', 'y', 'n', 'a', 'm', 'i',
    'c', 'S', 'e', 'c', 'r', 'e', 't', '\032', '\312', '\001', '\n', '\014',
    'S', 't', 'a', 't', 'i', 'c', 'S', 'e', 'c', 'r', 'e', 't',
    '\022', '\022', '\n', '\004', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001',
    '(', '\t', 'R', '\004', 'n', 'a', 'm', 'e', '\022', '=', '\n', '\014',
    'l', 'a', 's', 't', '_', 'u', 'p', 'd', 'a', 't', 'e', 'd',
    '\030', '\002', ' ', '\001', '(', '\013', '2', '\032', '.', 'g', 'o', 'o',
    'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f',
    '.', 'T', 'i', 'm', 'e', 's', 't', 'a', 'm', 'p', 'R', '\013',
    'l', 'a', 's', 't', 'U', 'p', 'd', 'a', 't', 'e', 'd', '\022',
    ',', '\n', '\006', 's', 'e', 'c', 'r', 'e', 't', '\030', '\003', ' ',
    '\001', '(', '\013', '2', '\024', '.', 'g', 'o', 'o', 'g', 'l', 'e',
    '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'A', 'n',
    'y', 'R', '\006', 's', 'e', 'c', 'r', 'e', 't', ':', '9', '\232',
    '\305', '\210', '\036', '4', '\n', '2', 'e', 'n', 'v', 'o', 'y', '.',
    'a', 'd', 'm', 'i', 'n', '.', 'v', '2', 'a', 'l', 'p', 'h',
    'a', '.', 'S', 'e', 'c', 'r', 'e', 't', 's', 'C', 'o', 'n',
    'f', 'i', 'g', 'D', 'u', 'm', 'p', '.', 'S', 't', 'a', 't',
    'i', 'c', 'S', 'e', 'c', 'r', 'e', 't', ':', ',', '\232', '\305',
    '\210', '\036', '\'', '\n', '%', 'e', 'n', 'v', 'o', 'y', '.', 'a',
    'd', 'm', 'i', 'n', '.', 'v', '2', 'a', 'l', 'p', 'h', 'a',
    '.', 'S', 'e', 'c', 'r', 'e', 't', 's', 'C', 'o', 'n', 'f',
    'i', 'g', 'D', 'u', 'm', 'p', 'B', 'x', '\n', '\034', 'i', 'o',
    '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'a', 'd', 'm', 'i', 'n', '.',
    'v', '3', 'B', '\017', 'C', 'o', 'n', 'f', 'i', 'g', 'D', 'u',
    'm', 'p', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', '=', 'g',
    'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n',
    'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-',
    'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n',
    'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 'a', 'd', 'm', 'i',
    'n', '/', 'v', '3', ';', 'a', 'd', 'm', 'i', 'n', 'v', '3',
    '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r',
    'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[7] = {
    &envoy_admin_v3_config_dump_shared_proto_upbdefinit,
    &envoy_config_bootstrap_v3_bootstrap_proto_upbdefinit,
    &google_protobuf_any_proto_upbdefinit,
    &google_protobuf_timestamp_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_admin_v3_config_dump_proto_upbdefinit = {
    deps,
    &envoy_admin_v3_config_dump_proto_upb_file_layout,
    "envoy/admin/v3/config_dump.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
