
#include "upb/reflection/def.h"
#include "envoy/config/tap/v3/common.upbdefs.h"
#include "envoy/config/tap/v3/common.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_common_matcher_v3_matcher_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_core_v3_base_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_core_v3_extension_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_core_v3_grpc_service_proto_upbdefinit;
extern _upb_DefPool_Init envoy_config_route_v3_route_components_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_duration_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_wrappers_proto_upbdefinit;
extern _upb_DefPool_Init envoy_annotations_deprecation_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[3990] = {
    '\n', ' ', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 't', 'a', 'p', '/', 'v', '3', '/', 'c', 'o',
    'm', 'm', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\022', '\023',
    'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g',
    '.', 't', 'a', 'p', '.', 'v', '3', '\032', ',', 'e', 'n', 'v',
    'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o',
    'm', 'm', 'o', 'n', '/', 'm', 'a', 't', 'c', 'h', 'e', 'r',
    '/', 'v', '3', '/', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.',
    'p', 'r', 'o', 't', 'o', '\032', '\037', 'e', 'n', 'v', 'o', 'y',
    '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e',
    '/', 'v', '3', '/', 'b', 'a', 's', 'e', '.', 'p', 'r', 'o',
    't', 'o', '\032', '$', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o',
    'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3',
    '/', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\'', 'e', 'n', 'v', 'o', 'y', '/',
    'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/',
    'v', '3', '/', 'g', 'r', 'p', 'c', '_', 's', 'e', 'r', 'v',
    'i', 'c', 'e', '.', 'p', 'r', 'o', 't', 'o', '\032', ',', 'e',
    'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/',
    'r', 'o', 'u', 't', 'e', '/', 'v', '3', '/', 'r', 'o', 'u',
    't', 'e', '_', 'c', 'o', 'm', 'p', 'o', 'n', 'e', 'n', 't',
    's', '.', 'p', 'r', 'o', 't', 'o', '\032', '\036', 'g', 'o', 'o',
    'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f',
    '/', 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '.', 'p', 'r',
    'o', 't', 'o', '\032', '\036', 'g', 'o', 'o', 'g', 'l', 'e', '/',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'w', 'r', 'a',
    'p', 'p', 'e', 'r', 's', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '#', 'e', 'n', 'v', 'o', 'y', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 'd', 'e', 'p', 'r', 'e',
    'c', 'a', 't', 'i', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u',
    's', '.', 'p', 'r', 'o', 't', 'o', '\032', '!', 'u', 'd', 'p',
    'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n',
    's', '/', 'v', 'e', 'r', 's', 'i', 'o', 'n', 'i', 'n', 'g',
    '.', 'p', 'r', 'o', 't', 'o', '\032', '\027', 'v', 'a', 'l', 'i',
    'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't',
    'e', '.', 'p', 'r', 'o', 't', 'o', '\"', '\365', '\002', '\n', '\t',
    'T', 'a', 'p', 'C', 'o', 'n', 'f', 'i', 'g', '\022', 'S', '\n',
    '\014', 'm', 'a', 't', 'c', 'h', '_', 'c', 'o', 'n', 'f', 'i',
    'g', '\030', '\001', ' ', '\001', '(', '\013', '2', '#', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 't',
    'a', 'p', '.', 'v', '3', '.', 'M', 'a', 't', 'c', 'h', 'P',
    'r', 'e', 'd', 'i', 'c', 'a', 't', 'e', 'B', '\013', '\030', '\001',
    '\222', '\307', '\206', '\330', '\004', '\003', '3', '.', '0', 'R', '\013', 'm',
    'a', 't', 'c', 'h', 'C', 'o', 'n', 'f', 'i', 'g', '\022', 'D',
    '\n', '\005', 'm', 'a', 't', 'c', 'h', '\030', '\004', ' ', '\001', '(',
    '\013', '2', '.', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o',
    'n', 'f', 'i', 'g', '.', 'c', 'o', 'm', 'm', 'o', 'n', '.',
    'm', 'a', 't', 'c', 'h', 'e', 'r', '.', 'v', '3', '.', 'M',
    'a', 't', 'c', 'h', 'P', 'r', 'e', 'd', 'i', 'c', 'a', 't',
    'e', 'R', '\005', 'm', 'a', 't', 'c', 'h', '\022', 'P', '\n', '\r',
    'o', 'u', 't', 'p', 'u', 't', '_', 'c', 'o', 'n', 'f', 'i',
    'g', '\030', '\002', ' ', '\001', '(', '\013', '2', '!', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 't',
    'a', 'p', '.', 'v', '3', '.', 'O', 'u', 't', 'p', 'u', 't',
    'C', 'o', 'n', 'f', 'i', 'g', 'B', '\010', '\372', 'B', '\005', '\212',
    '\001', '\002', '\020', '\001', 'R', '\014', 'o', 'u', 't', 'p', 'u', 't',
    'C', 'o', 'n', 'f', 'i', 'g', '\022', 'O', '\n', '\013', 't', 'a',
    'p', '_', 'e', 'n', 'a', 'b', 'l', 'e', 'd', '\030', '\003', ' ',
    '\001', '(', '\013', '2', '.', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.',
    'v', '3', '.', 'R', 'u', 'n', 't', 'i', 'm', 'e', 'F', 'r',
    'a', 'c', 't', 'i', 'o', 'n', 'a', 'l', 'P', 'e', 'r', 'c',
    'e', 'n', 't', 'R', '\n', 't', 'a', 'p', 'E', 'n', 'a', 'b',
    'l', 'e', 'd', ':', '*', '\232', '\305', '\210', '\036', '%', '\n', '#',
    'e', 'n', 'v', 'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c',
    'e', '.', 't', 'a', 'p', '.', 'v', '2', 'a', 'l', 'p', 'h',
    'a', '.', 'T', 'a', 'p', 'C', 'o', 'n', 'f', 'i', 'g', '\"',
    '\346', '\010', '\n', '\016', 'M', 'a', 't', 'c', 'h', 'P', 'r', 'e',
    'd', 'i', 'c', 'a', 't', 'e', '\022', 'I', '\n', '\010', 'o', 'r',
    '_', 'm', 'a', 't', 'c', 'h', '\030', '\001', ' ', '\001', '(', '\013',
    '2', ',', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 't', 'a', 'p', '.', 'v', '3', '.', 'M',
    'a', 't', 'c', 'h', 'P', 'r', 'e', 'd', 'i', 'c', 'a', 't',
    'e', '.', 'M', 'a', 't', 'c', 'h', 'S', 'e', 't', 'H', '\000',
    'R', '\007', 'o', 'r', 'M', 'a', 't', 'c', 'h', '\022', 'K', '\n',
    '\t', 'a', 'n', 'd', '_', 'm', 'a', 't', 'c', 'h', '\030', '\002',
    ' ', '\001', '(', '\013', '2', ',', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'a', 'p', '.',
    'v', '3', '.', 'M', 'a', 't', 'c', 'h', 'P', 'r', 'e', 'd',
    'i', 'c', 'a', 't', 'e', '.', 'M', 'a', 't', 'c', 'h', 'S',
    'e', 't', 'H', '\000', 'R', '\010', 'a', 'n', 'd', 'M', 'a', 't',
    'c', 'h', '\022', 'B', '\n', '\t', 'n', 'o', 't', '_', 'm', 'a',
    't', 'c', 'h', '\030', '\003', ' ', '\001', '(', '\013', '2', '#', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g',
    '.', 't', 'a', 'p', '.', 'v', '3', '.', 'M', 'a', 't', 'c',
    'h', 'P', 'r', 'e', 'd', 'i', 'c', 'a', 't', 'e', 'H', '\000',
    'R', '\010', 'n', 'o', 't', 'M', 'a', 't', 'c', 'h', '\022', '&',
    '\n', '\t', 'a', 'n', 'y', '_', 'm', 'a', 't', 'c', 'h', '\030',
    '\004', ' ', '\001', '(', '\010', 'B', '\007', '\372', 'B', '\004', 'j', '\002',
    '\010', '\001', 'H', '\000', 'R', '\010', 'a', 'n', 'y', 'M', 'a', 't',
    'c', 'h', '\022', 'd', '\n', '\032', 'h', 't', 't', 'p', '_', 'r',
    'e', 'q', 'u', 'e', 's', 't', '_', 'h', 'e', 'a', 'd', 'e',
    'r', 's', '_', 'm', 'a', 't', 'c', 'h', '\030', '\005', ' ', '\001',
    '(', '\013', '2', '%', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 't', 'a', 'p', '.', 'v', '3',
    '.', 'H', 't', 't', 'p', 'H', 'e', 'a', 'd', 'e', 'r', 's',
    'M', 'a', 't', 'c', 'h', 'H', '\000', 'R', '\027', 'h', 't', 't',
    'p', 'R', 'e', 'q', 'u', 'e', 's', 't', 'H', 'e', 'a', 'd',
    'e', 'r', 's', 'M', 'a', 't', 'c', 'h', '\022', 'f', '\n', '\033',
    'h', 't', 't', 'p', '_', 'r', 'e', 'q', 'u', 'e', 's', 't',
    '_', 't', 'r', 'a', 'i', 'l', 'e', 'r', 's', '_', 'm', 'a',
    't', 'c', 'h', '\030', '\006', ' ', '\001', '(', '\013', '2', '%', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g',
    '.', 't', 'a', 'p', '.', 'v', '3', '.', 'H', 't', 't', 'p',
    'H', 'e', 'a', 'd', 'e', 'r', 's', 'M', 'a', 't', 'c', 'h',
    'H', '\000', 'R', '\030', 'h', 't', 't', 'p', 'R', 'e', 'q', 'u',
    'e', 's', 't', 'T', 'r', 'a', 'i', 'l', 'e', 'r', 's', 'M',
    'a', 't', 'c', 'h', '\022', 'f', '\n', '\033', 'h', 't', 't', 'p',
    '_', 'r', 'e', 's', 'p', 'o', 'n', 's', 'e', '_', 'h', 'e',
    'a', 'd', 'e', 'r', 's', '_', 'm', 'a', 't', 'c', 'h', '\030',
    '\007', ' ', '\001', '(', '\013', '2', '%', '.', 'e', 'n', 'v', 'o',
    'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'a', 'p',
    '.', 'v', '3', '.', 'H', 't', 't', 'p', 'H', 'e', 'a', 'd',
    'e', 'r', 's', 'M', 'a', 't', 'c', 'h', 'H', '\000', 'R', '\030',
    'h', 't', 't', 'p', 'R', 'e', 's', 'p', 'o', 'n', 's', 'e',
    'H', 'e', 'a', 'd', 'e', 'r', 's', 'M', 'a', 't', 'c', 'h',
    '\022', 'h', '\n', '\034', 'h', 't', 't', 'p', '_', 'r', 'e', 's',
    'p', 'o', 'n', 's', 'e', '_', 't', 'r', 'a', 'i', 'l', 'e',
    'r', 's', '_', 'm', 'a', 't', 'c', 'h', '\030', '\010', ' ', '\001',
    '(', '\013', '2', '%', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 't', 'a', 'p', '.', 'v', '3',
    '.', 'H', 't', 't', 'p', 'H', 'e', 'a', 'd', 'e', 'r', 's',
    'M', 'a', 't', 'c', 'h', 'H', '\000', 'R', '\031', 'h', 't', 't',
    'p', 'R', 'e', 's', 'p', 'o', 'n', 's', 'e', 'T', 'r', 'a',
    'i', 'l', 'e', 'r', 's', 'M', 'a', 't', 'c', 'h', '\022', 'q',
    '\n', '\037', 'h', 't', 't', 'p', '_', 'r', 'e', 'q', 'u', 'e',
    's', 't', '_', 'g', 'e', 'n', 'e', 'r', 'i', 'c', '_', 'b',
    'o', 'd', 'y', '_', 'm', 'a', 't', 'c', 'h', '\030', '\t', ' ',
    '\001', '(', '\013', '2', ')', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'a', 'p', '.', 'v',
    '3', '.', 'H', 't', 't', 'p', 'G', 'e', 'n', 'e', 'r', 'i',
    'c', 'B', 'o', 'd', 'y', 'M', 'a', 't', 'c', 'h', 'H', '\000',
    'R', '\033', 'h', 't', 't', 'p', 'R', 'e', 'q', 'u', 'e', 's',
    't', 'G', 'e', 'n', 'e', 'r', 'i', 'c', 'B', 'o', 'd', 'y',
    'M', 'a', 't', 'c', 'h', '\022', 's', '\n', ' ', 'h', 't', 't',
    'p', '_', 'r', 'e', 's', 'p', 'o', 'n', 's', 'e', '_', 'g',
    'e', 'n', 'e', 'r', 'i', 'c', '_', 'b', 'o', 'd', 'y', '_',
    'm', 'a', 't', 'c', 'h', '\030', '\n', ' ', '\001', '(', '\013', '2',
    ')', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 't', 'a', 'p', '.', 'v', '3', '.', 'H', 't',
    't', 'p', 'G', 'e', 'n', 'e', 'r', 'i', 'c', 'B', 'o', 'd',
    'y', 'M', 'a', 't', 'c', 'h', 'H', '\000', 'R', '\034', 'h', 't',
    't', 'p', 'R', 'e', 's', 'p', 'o', 'n', 's', 'e', 'G', 'e',
    'n', 'e', 'r', 'i', 'c', 'B', 'o', 'd', 'y', 'M', 'a', 't',
    'c', 'h', '\032', '\211', '\001', '\n', '\010', 'M', 'a', 't', 'c', 'h',
    'S', 'e', 't', '\022', 'C', '\n', '\005', 'r', 'u', 'l', 'e', 's',
    '\030', '\001', ' ', '\003', '(', '\013', '2', '#', '.', 'e', 'n', 'v',
    'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'a',
    'p', '.', 'v', '3', '.', 'M', 'a', 't', 'c', 'h', 'P', 'r',
    'e', 'd', 'i', 'c', 'a', 't', 'e', 'B', '\010', '\372', 'B', '\005',
    '\222', '\001', '\002', '\010', '\002', 'R', '\005', 'r', 'u', 'l', 'e', 's',
    ':', '8', '\232', '\305', '\210', '\036', '3', '\n', '1', 'e', 'n', 'v',
    'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 't',
    'a', 'p', '.', 'v', '2', 'a', 'l', 'p', 'h', 'a', '.', 'M',
    'a', 't', 'c', 'h', 'P', 'r', 'e', 'd', 'i', 'c', 'a', 't',
    'e', '.', 'M', 'a', 't', 'c', 'h', 'S', 'e', 't', ':', '/',
    '\232', '\305', '\210', '\036', '*', '\n', '(', 'e', 'n', 'v', 'o', 'y',
    '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 't', 'a', 'p',
    '.', 'v', '2', 'a', 'l', 'p', 'h', 'a', '.', 'M', 'a', 't',
    'c', 'h', 'P', 'r', 'e', 'd', 'i', 'c', 'a', 't', 'e', 'B',
    '\013', '\n', '\004', 'r', 'u', 'l', 'e', '\022', '\003', '\370', 'B', '\001',
    '\"', '\205', '\001', '\n', '\020', 'H', 't', 't', 'p', 'H', 'e', 'a',
    'd', 'e', 'r', 's', 'M', 'a', 't', 'c', 'h', '\022', '>', '\n',
    '\007', 'h', 'e', 'a', 'd', 'e', 'r', 's', '\030', '\001', ' ', '\003',
    '(', '\013', '2', '$', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'r', 'o', 'u', 't', 'e', '.',
    'v', '3', '.', 'H', 'e', 'a', 'd', 'e', 'r', 'M', 'a', 't',
    'c', 'h', 'e', 'r', 'R', '\007', 'h', 'e', 'a', 'd', 'e', 'r',
    's', ':', '1', '\232', '\305', '\210', '\036', ',', '\n', '*', 'e', 'n',
    'v', 'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.',
    't', 'a', 'p', '.', 'v', '2', 'a', 'l', 'p', 'h', 'a', '.',
    'H', 't', 't', 'p', 'H', 'e', 'a', 'd', 'e', 'r', 's', 'M',
    'a', 't', 'c', 'h', '\"', '\226', '\002', '\n', '\024', 'H', 't', 't',
    'p', 'G', 'e', 'n', 'e', 'r', 'i', 'c', 'B', 'o', 'd', 'y',
    'M', 'a', 't', 'c', 'h', '\022', '\037', '\n', '\013', 'b', 'y', 't',
    'e', 's', '_', 'l', 'i', 'm', 'i', 't', '\030', '\001', ' ', '\001',
    '(', '\r', 'R', '\n', 'b', 'y', 't', 'e', 's', 'L', 'i', 'm',
    'i', 't', '\022', '`', '\n', '\010', 'p', 'a', 't', 't', 'e', 'r',
    'n', 's', '\030', '\002', ' ', '\003', '(', '\013', '2', ':', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    't', 'a', 'p', '.', 'v', '3', '.', 'H', 't', 't', 'p', 'G',
    'e', 'n', 'e', 'r', 'i', 'c', 'B', 'o', 'd', 'y', 'M', 'a',
    't', 'c', 'h', '.', 'G', 'e', 'n', 'e', 'r', 'i', 'c', 'T',
    'e', 'x', 't', 'M', 'a', 't', 'c', 'h', 'B', '\010', '\372', 'B',
    '\005', '\222', '\001', '\002', '\010', '\001', 'R', '\010', 'p', 'a', 't', 't',
    'e', 'r', 'n', 's', '\032', '{', '\n', '\020', 'G', 'e', 'n', 'e',
    'r', 'i', 'c', 'T', 'e', 'x', 't', 'M', 'a', 't', 'c', 'h',
    '\022', ',', '\n', '\014', 's', 't', 'r', 'i', 'n', 'g', '_', 'm',
    'a', 't', 'c', 'h', '\030', '\001', ' ', '\001', '(', '\t', 'B', '\007',
    '\372', 'B', '\004', 'r', '\002', '\020', '\001', 'H', '\000', 'R', '\013', 's',
    't', 'r', 'i', 'n', 'g', 'M', 'a', 't', 'c', 'h', '\022', ',',
    '\n', '\014', 'b', 'i', 'n', 'a', 'r', 'y', '_', 'm', 'a', 't',
    'c', 'h', '\030', '\002', ' ', '\001', '(', '\014', 'B', '\007', '\372', 'B',
    '\004', 'z', '\002', '\020', '\001', 'H', '\000', 'R', '\013', 'b', 'i', 'n',
    'a', 'r', 'y', 'M', 'a', 't', 'c', 'h', 'B', '\013', '\n', '\004',
    'r', 'u', 'l', 'e', '\022', '\003', '\370', 'B', '\001', '\"', '\300', '\002',
    '\n', '\014', 'O', 'u', 't', 'p', 'u', 't', 'C', 'o', 'n', 'f',
    'i', 'g', '\022', 'A', '\n', '\005', 's', 'i', 'n', 'k', 's', '\030',
    '\001', ' ', '\003', '(', '\013', '2', '\037', '.', 'e', 'n', 'v', 'o',
    'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'a', 'p',
    '.', 'v', '3', '.', 'O', 'u', 't', 'p', 'u', 't', 'S', 'i',
    'n', 'k', 'B', '\n', '\372', 'B', '\007', '\222', '\001', '\004', '\010', '\001',
    '\020', '\001', 'R', '\005', 's', 'i', 'n', 'k', 's', '\022', 'O', '\n',
    '\025', 'm', 'a', 'x', '_', 'b', 'u', 'f', 'f', 'e', 'r', 'e',
    'd', '_', 'r', 'x', '_', 'b', 'y', 't', 'e', 's', '\030', '\002',
    ' ', '\001', '(', '\013', '2', '\034', '.', 'g', 'o', 'o', 'g', 'l',
    'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'U',
    'I', 'n', 't', '3', '2', 'V', 'a', 'l', 'u', 'e', 'R', '\022',
    'm', 'a', 'x', 'B', 'u', 'f', 'f', 'e', 'r', 'e', 'd', 'R',
    'x', 'B', 'y', 't', 'e', 's', '\022', 'O', '\n', '\025', 'm', 'a',
    'x', '_', 'b', 'u', 'f', 'f', 'e', 'r', 'e', 'd', '_', 't',
    'x', '_', 'b', 'y', 't', 'e', 's', '\030', '\003', ' ', '\001', '(',
    '\013', '2', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p',
    'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't',
    '3', '2', 'V', 'a', 'l', 'u', 'e', 'R', '\022', 'm', 'a', 'x',
    'B', 'u', 'f', 'f', 'e', 'r', 'e', 'd', 'T', 'x', 'B', 'y',
    't', 'e', 's', '\022', '\034', '\n', '\t', 's', 't', 'r', 'e', 'a',
    'm', 'i', 'n', 'g', '\030', '\004', ' ', '\001', '(', '\010', 'R', '\t',
    's', 't', 'r', 'e', 'a', 'm', 'i', 'n', 'g', ':', '-', '\232',
    '\305', '\210', '\036', '(', '\n', '&', 'e', 'n', 'v', 'o', 'y', '.',
    's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 't', 'a', 'p', '.',
    'v', '2', 'a', 'l', 'p', 'h', 'a', '.', 'O', 'u', 't', 'p',
    'u', 't', 'C', 'o', 'n', 'f', 'i', 'g', '\"', '\252', '\005', '\n',
    '\n', 'O', 'u', 't', 'p', 'u', 't', 'S', 'i', 'n', 'k', '\022',
    'H', '\n', '\006', 'f', 'o', 'r', 'm', 'a', 't', '\030', '\001', ' ',
    '\001', '(', '\016', '2', '&', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 't', 'a', 'p', '.', 'v',
    '3', '.', 'O', 'u', 't', 'p', 'u', 't', 'S', 'i', 'n', 'k',
    '.', 'F', 'o', 'r', 'm', 'a', 't', 'B', '\010', '\372', 'B', '\005',
    '\202', '\001', '\002', '\020', '\001', 'R', '\006', 'f', 'o', 'r', 'm', 'a',
    't', '\022', 'R', '\n', '\017', 's', 't', 'r', 'e', 'a', 'm', 'i',
    'n', 'g', '_', 'a', 'd', 'm', 'i', 'n', '\030', '\002', ' ', '\001',
    '(', '\013', '2', '\'', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 't', 'a', 'p', '.', 'v', '3',
    '.', 'S', 't', 'r', 'e', 'a', 'm', 'i', 'n', 'g', 'A', 'd',
    'm', 'i', 'n', 'S', 'i', 'n', 'k', 'H', '\000', 'R', '\016', 's',
    't', 'r', 'e', 'a', 'm', 'i', 'n', 'g', 'A', 'd', 'm', 'i',
    'n', '\022', 'G', '\n', '\014', 'f', 'i', 'l', 'e', '_', 'p', 'e',
    'r', '_', 't', 'a', 'p', '\030', '\003', ' ', '\001', '(', '\013', '2',
    '#', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 't', 'a', 'p', '.', 'v', '3', '.', 'F', 'i',
    'l', 'e', 'P', 'e', 'r', 'T', 'a', 'p', 'S', 'i', 'n', 'k',
    'H', '\000', 'R', '\n', 'f', 'i', 'l', 'e', 'P', 'e', 'r', 'T',
    'a', 'p', '\022', 'O', '\n', '\016', 's', 't', 'r', 'e', 'a', 'm',
    'i', 'n', 'g', '_', 'g', 'r', 'p', 'c', '\030', '\004', ' ', '\001',
    '(', '\013', '2', '&', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 't', 'a', 'p', '.', 'v', '3',
    '.', 'S', 't', 'r', 'e', 'a', 'm', 'i', 'n', 'g', 'G', 'r',
    'p', 'c', 'S', 'i', 'n', 'k', 'H', '\000', 'R', '\r', 's', 't',
    'r', 'e', 'a', 'm', 'i', 'n', 'g', 'G', 'r', 'p', 'c', '\022',
    'O', '\n', '\016', 'b', 'u', 'f', 'f', 'e', 'r', 'e', 'd', '_',
    'a', 'd', 'm', 'i', 'n', '\030', '\005', ' ', '\001', '(', '\013', '2',
    '&', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 't', 'a', 'p', '.', 'v', '3', '.', 'B', 'u',
    'f', 'f', 'e', 'r', 'e', 'd', 'A', 'd', 'm', 'i', 'n', 'S',
    'i', 'n', 'k', 'H', '\000', 'R', '\r', 'b', 'u', 'f', 'f', 'e',
    'r', 'e', 'd', 'A', 'd', 'm', 'i', 'n', '\022', 'M', '\n', '\013',
    'c', 'u', 's', 't', 'o', 'm', '_', 's', 'i', 'n', 'k', '\030',
    '\006', ' ', '\001', '(', '\013', '2', '*', '.', 'e', 'n', 'v', 'o',
    'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r',
    'e', '.', 'v', '3', '.', 'T', 'y', 'p', 'e', 'd', 'E', 'x',
    't', 'e', 'n', 's', 'i', 'o', 'n', 'C', 'o', 'n', 'f', 'i',
    'g', 'H', '\000', 'R', '\n', 'c', 'u', 's', 't', 'o', 'm', 'S',
    'i', 'n', 'k', '\"', '~', '\n', '\006', 'F', 'o', 'r', 'm', 'a',
    't', '\022', '\026', '\n', '\022', 'J', 'S', 'O', 'N', '_', 'B', 'O',
    'D', 'Y', '_', 'A', 'S', '_', 'B', 'Y', 'T', 'E', 'S', '\020',
    '\000', '\022', '\027', '\n', '\023', 'J', 'S', 'O', 'N', '_', 'B', 'O',
    'D', 'Y', '_', 'A', 'S', '_', 'S', 'T', 'R', 'I', 'N', 'G',
    '\020', '\001', '\022', '\020', '\n', '\014', 'P', 'R', 'O', 'T', 'O', '_',
    'B', 'I', 'N', 'A', 'R', 'Y', '\020', '\002', '\022', '!', '\n', '\035',
    'P', 'R', 'O', 'T', 'O', '_', 'B', 'I', 'N', 'A', 'R', 'Y',
    '_', 'L', 'E', 'N', 'G', 'T', 'H', '_', 'D', 'E', 'L', 'I',
    'M', 'I', 'T', 'E', 'D', '\020', '\003', '\022', '\016', '\n', '\n', 'P',
    'R', 'O', 'T', 'O', '_', 'T', 'E', 'X', 'T', '\020', '\004', ':',
    '+', '\232', '\305', '\210', '\036', '&', '\n', '$', 'e', 'n', 'v', 'o',
    'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 't', 'a',
    'p', '.', 'v', '2', 'a', 'l', 'p', 'h', 'a', '.', 'O', 'u',
    't', 'p', 'u', 't', 'S', 'i', 'n', 'k', 'B', '\027', '\n', '\020',
    'o', 'u', 't', 'p', 'u', 't', '_', 's', 'i', 'n', 'k', '_',
    't', 'y', 'p', 'e', '\022', '\003', '\370', 'B', '\001', '\"', 'I', '\n',
    '\022', 'S', 't', 'r', 'e', 'a', 'm', 'i', 'n', 'g', 'A', 'd',
    'm', 'i', 'n', 'S', 'i', 'n', 'k', ':', '3', '\232', '\305', '\210',
    '\036', '.', '\n', ',', 'e', 'n', 'v', 'o', 'y', '.', 's', 'e',
    'r', 'v', 'i', 'c', 'e', '.', 't', 'a', 'p', '.', 'v', '2',
    'a', 'l', 'p', 'h', 'a', '.', 'S', 't', 'r', 'e', 'a', 'm',
    'i', 'n', 'g', 'A', 'd', 'm', 'i', 'n', 'S', 'i', 'n', 'k',
    '\"', 'p', '\n', '\021', 'B', 'u', 'f', 'f', 'e', 'r', 'e', 'd',
    'A', 'd', 'm', 'i', 'n', 'S', 'i', 'n', 'k', '\022', '&', '\n',
    '\n', 'm', 'a', 'x', '_', 't', 'r', 'a', 'c', 'e', 's', '\030',
    '\001', ' ', '\001', '(', '\004', 'B', '\007', '\372', 'B', '\004', '2', '\002',
    ' ', '\000', 'R', '\t', 'm', 'a', 'x', 'T', 'r', 'a', 'c', 'e',
    's', '\022', '3', '\n', '\007', 't', 'i', 'm', 'e', 'o', 'u', 't',
    '\030', '\002', ' ', '\001', '(', '\013', '2', '\031', '.', 'g', 'o', 'o',
    'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f',
    '.', 'D', 'u', 'r', 'a', 't', 'i', 'o', 'n', 'R', '\007', 't',
    'i', 'm', 'e', 'o', 'u', 't', '\"', 'k', '\n', '\016', 'F', 'i',
    'l', 'e', 'P', 'e', 'r', 'T', 'a', 'p', 'S', 'i', 'n', 'k',
    '\022', '(', '\n', '\013', 'p', 'a', 't', 'h', '_', 'p', 'r', 'e',
    'f', 'i', 'x', '\030', '\001', ' ', '\001', '(', '\t', 'B', '\007', '\372',
    'B', '\004', 'r', '\002', '\020', '\001', 'R', '\n', 'p', 'a', 't', 'h',
    'P', 'r', 'e', 'f', 'i', 'x', ':', '/', '\232', '\305', '\210', '\036',
    '*', '\n', '(', 'e', 'n', 'v', 'o', 'y', '.', 's', 'e', 'r',
    'v', 'i', 'c', 'e', '.', 't', 'a', 'p', '.', 'v', '2', 'a',
    'l', 'p', 'h', 'a', '.', 'F', 'i', 'l', 'e', 'P', 'e', 'r',
    'T', 'a', 'p', 'S', 'i', 'n', 'k', '\"', '\256', '\001', '\n', '\021',
    'S', 't', 'r', 'e', 'a', 'm', 'i', 'n', 'g', 'G', 'r', 'p',
    'c', 'S', 'i', 'n', 'k', '\022', '\025', '\n', '\006', 't', 'a', 'p',
    '_', 'i', 'd', '\030', '\001', ' ', '\001', '(', '\t', 'R', '\005', 't',
    'a', 'p', 'I', 'd', '\022', 'N', '\n', '\014', 'g', 'r', 'p', 'c',
    '_', 's', 'e', 'r', 'v', 'i', 'c', 'e', '\030', '\002', ' ', '\001',
    '(', '\013', '2', '!', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v',
    '3', '.', 'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c',
    'e', 'B', '\010', '\372', 'B', '\005', '\212', '\001', '\002', '\020', '\001', 'R',
    '\013', 'g', 'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e',
    ':', '2', '\232', '\305', '\210', '\036', '-', '\n', '+', 'e', 'n', 'v',
    'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 't',
    'a', 'p', '.', 'v', '2', 'a', 'l', 'p', 'h', 'a', '.', 'S',
    't', 'r', 'e', 'a', 'm', 'i', 'n', 'g', 'G', 'r', 'p', 'c',
    'S', 'i', 'n', 'k', 'B', '|', '\n', '!', 'i', 'o', '.', 'e',
    'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 't',
    'a', 'p', '.', 'v', '3', 'B', '\013', 'C', 'o', 'm', 'm', 'o',
    'n', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', '@', 'g', 'i',
    't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v',
    'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c',
    'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e',
    '/', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i',
    'g', '/', 't', 'a', 'p', '/', 'v', '3', ';', 't', 'a', 'p',
    'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006',
    'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[12] = {
    &envoy_config_common_matcher_v3_matcher_proto_upbdefinit,
    &envoy_config_core_v3_base_proto_upbdefinit,
    &envoy_config_core_v3_extension_proto_upbdefinit,
    &envoy_config_core_v3_grpc_service_proto_upbdefinit,
    &envoy_config_route_v3_route_components_proto_upbdefinit,
    &google_protobuf_duration_proto_upbdefinit,
    &google_protobuf_wrappers_proto_upbdefinit,
    &envoy_annotations_deprecation_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_tap_v3_common_proto_upbdefinit = {
    deps,
    &envoy_config_tap_v3_common_proto_upb_file_layout,
    "envoy/config/tap/v3/common.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
