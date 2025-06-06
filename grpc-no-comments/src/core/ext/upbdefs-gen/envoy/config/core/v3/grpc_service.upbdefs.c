
#include "upb/reflection/def.h"
#include "envoy/config/core/v3/grpc_service.upbdefs.h"
#include "envoy/config/core/v3/grpc_service.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_base_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_duration_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_empty_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_struct_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_wrappers_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_sensitive_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[5030] = {
    '\n', '\'', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'g',
    'r', 'p', 'c', '_', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.',
    'p', 'r', 'o', 't', 'o', '\022', '\024', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e',
    '.', 'v', '3', '\032', '\037', 'e', 'n', 'v', 'o', 'y', '/', 'c',
    'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v',
    '3', '/', 'b', 'a', 's', 'e', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\031', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '/', 'a', 'n', 'y', '.', 'p', 'r',
    'o', 't', 'o', '\032', '\036', 'g', 'o', 'o', 'g', 'l', 'e', '/',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'd', 'u', 'r',
    'a', 't', 'i', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '\033', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't',
    'o', 'b', 'u', 'f', '/', 'e', 'm', 'p', 't', 'y', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\034', 'g', 'o', 'o', 'g', 'l', 'e',
    '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 's', 't',
    'r', 'u', 'c', 't', '.', 'p', 'r', 'o', 't', 'o', '\032', '\036',
    'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o',
    'b', 'u', 'f', '/', 'w', 'r', 'a', 'p', 'p', 'e', 'r', 's',
    '.', 'p', 'r', 'o', 't', 'o', '\032', ' ', 'u', 'd', 'p', 'a',
    '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '/', 's', 'e', 'n', 's', 'i', 't', 'i', 'v', 'e', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a',
    'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's',
    't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032',
    '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i', 'o',
    'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027',
    'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l',
    'i', 'd', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"',
    '\241', '#', '\n', '\013', 'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v',
    'i', 'c', 'e', '\022', 'L', '\n', '\n', 'e', 'n', 'v', 'o', 'y',
    '_', 'g', 'r', 'p', 'c', '\030', '\001', ' ', '\001', '(', '\013', '2',
    '+', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'G',
    'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'E',
    'n', 'v', 'o', 'y', 'G', 'r', 'p', 'c', 'H', '\000', 'R', '\t',
    'e', 'n', 'v', 'o', 'y', 'G', 'r', 'p', 'c', '\022', 'O', '\n',
    '\013', 'g', 'o', 'o', 'g', 'l', 'e', '_', 'g', 'r', 'p', 'c',
    '\030', '\002', ' ', '\001', '(', '\013', '2', ',', '.', 'e', 'n', 'v',
    'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o',
    'r', 'e', '.', 'v', '3', '.', 'G', 'r', 'p', 'c', 'S', 'e',
    'r', 'v', 'i', 'c', 'e', '.', 'G', 'o', 'o', 'g', 'l', 'e',
    'G', 'r', 'p', 'c', 'H', '\000', 'R', '\n', 'g', 'o', 'o', 'g',
    'l', 'e', 'G', 'r', 'p', 'c', '\022', '3', '\n', '\007', 't', 'i',
    'm', 'e', 'o', 'u', 't', '\030', '\003', ' ', '\001', '(', '\013', '2',
    '\031', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '.', 'D', 'u', 'r', 'a', 't', 'i',
    'o', 'n', 'R', '\007', 't', 'i', 'm', 'e', 'o', 'u', 't', '\022',
    'L', '\n', '\020', 'i', 'n', 'i', 't', 'i', 'a', 'l', '_', 'm',
    'e', 't', 'a', 'd', 'a', 't', 'a', '\030', '\005', ' ', '\003', '(',
    '\013', '2', '!', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o',
    'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3',
    '.', 'H', 'e', 'a', 'd', 'e', 'r', 'V', 'a', 'l', 'u', 'e',
    'R', '\017', 'i', 'n', 'i', 't', 'i', 'a', 'l', 'M', 'e', 't',
    'a', 'd', 'a', 't', 'a', '\022', 'D', '\n', '\014', 'r', 'e', 't',
    'r', 'y', '_', 'p', 'o', 'l', 'i', 'c', 'y', '\030', '\006', ' ',
    '\001', '(', '\013', '2', '!', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.',
    'v', '3', '.', 'R', 'e', 't', 'r', 'y', 'P', 'o', 'l', 'i',
    'c', 'y', 'R', '\013', 'r', 'e', 't', 'r', 'y', 'P', 'o', 'l',
    'i', 'c', 'y', '\032', '\347', '\002', '\n', '\t', 'E', 'n', 'v', 'o',
    'y', 'G', 'r', 'p', 'c', '\022', '*', '\n', '\014', 'c', 'l', 'u',
    's', 't', 'e', 'r', '_', 'n', 'a', 'm', 'e', '\030', '\001', ' ',
    '\001', '(', '\t', 'B', '\007', '\372', 'B', '\004', 'r', '\002', '\020', '\001',
    'R', '\013', 'c', 'l', 'u', 's', 't', 'e', 'r', 'N', 'a', 'm',
    'e', '\022', '/', '\n', '\t', 'a', 'u', 't', 'h', 'o', 'r', 'i',
    't', 'y', '\030', '\002', ' ', '\001', '(', '\t', 'B', '\021', '\372', 'B',
    '\016', 'r', '\014', '\020', '\000', '(', '\200', '\200', '\001', '\300', '\001', '\002',
    '\310', '\001', '\000', 'R', '\t', 'a', 'u', 't', 'h', 'o', 'r', 'i',
    't', 'y', '\022', 'D', '\n', '\014', 'r', 'e', 't', 'r', 'y', '_',
    'p', 'o', 'l', 'i', 'c', 'y', '\030', '\003', ' ', '\001', '(', '\013',
    '2', '!', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.',
    'R', 'e', 't', 'r', 'y', 'P', 'o', 'l', 'i', 'c', 'y', 'R',
    '\013', 'r', 'e', 't', 'r', 'y', 'P', 'o', 'l', 'i', 'c', 'y',
    '\022', 'Y', '\n', '\032', 'm', 'a', 'x', '_', 'r', 'e', 'c', 'e',
    'i', 'v', 'e', '_', 'm', 'e', 's', 's', 'a', 'g', 'e', '_',
    'l', 'e', 'n', 'g', 't', 'h', '\030', '\004', ' ', '\001', '(', '\013',
    '2', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r',
    'o', 't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '3',
    '2', 'V', 'a', 'l', 'u', 'e', 'R', '\027', 'm', 'a', 'x', 'R',
    'e', 'c', 'e', 'i', 'v', 'e', 'M', 'e', 's', 's', 'a', 'g',
    'e', 'L', 'e', 'n', 'g', 't', 'h', '\022', ',', '\n', '\022', 's',
    'k', 'i', 'p', '_', 'e', 'n', 'v', 'o', 'y', '_', 'h', 'e',
    'a', 'd', 'e', 'r', 's', '\030', '\005', ' ', '\001', '(', '\010', 'R',
    '\020', 's', 'k', 'i', 'p', 'E', 'n', 'v', 'o', 'y', 'H', 'e',
    'a', 'd', 'e', 'r', 's', ':', '.', '\232', '\305', '\210', '\036', ')',
    '\n', '\'', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.',
    'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'G', 'r', 'p', 'c',
    'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'E', 'n', 'v', 'o',
    'y', 'G', 'r', 'p', 'c', '\032', '\372', '\034', '\n', '\n', 'G', 'o',
    'o', 'g', 'l', 'e', 'G', 'r', 'p', 'c', '\022', '&', '\n', '\n',
    't', 'a', 'r', 'g', 'e', 't', '_', 'u', 'r', 'i', '\030', '\001',
    ' ', '\001', '(', '\t', 'B', '\007', '\372', 'B', '\004', 'r', '\002', '\020',
    '\001', 'R', '\t', 't', 'a', 'r', 'g', 'e', 't', 'U', 'r', 'i',
    '\022', 'p', '\n', '\023', 'c', 'h', 'a', 'n', 'n', 'e', 'l', '_',
    'c', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's', '\030',
    '\002', ' ', '\001', '(', '\013', '2', '?', '.', 'e', 'n', 'v', 'o',
    'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r',
    'e', '.', 'v', '3', '.', 'G', 'r', 'p', 'c', 'S', 'e', 'r',
    'v', 'i', 'c', 'e', '.', 'G', 'o', 'o', 'g', 'l', 'e', 'G',
    'r', 'p', 'c', '.', 'C', 'h', 'a', 'n', 'n', 'e', 'l', 'C',
    'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's', 'R', '\022',
    'c', 'h', 'a', 'n', 'n', 'e', 'l', 'C', 'r', 'e', 'd', 'e',
    'n', 't', 'i', 'a', 'l', 's', '\022', 'g', '\n', '\020', 'c', 'a',
    'l', 'l', '_', 'c', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a',
    'l', 's', '\030', '\003', ' ', '\003', '(', '\013', '2', '<', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'G', 'r', 'p', 'c',
    'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'G', 'o', 'o', 'g',
    'l', 'e', 'G', 'r', 'p', 'c', '.', 'C', 'a', 'l', 'l', 'C',
    'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's', 'R', '\017',
    'c', 'a', 'l', 'l', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i',
    'a', 'l', 's', '\022', '(', '\n', '\013', 's', 't', 'a', 't', '_',
    'p', 'r', 'e', 'f', 'i', 'x', '\030', '\004', ' ', '\001', '(', '\t',
    'B', '\007', '\372', 'B', '\004', 'r', '\002', '\020', '\001', 'R', '\n', 's',
    't', 'a', 't', 'P', 'r', 'e', 'f', 'i', 'x', '\022', '8', '\n',
    '\030', 'c', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's',
    '_', 'f', 'a', 'c', 't', 'o', 'r', 'y', '_', 'n', 'a', 'm',
    'e', '\030', '\005', ' ', '\001', '(', '\t', 'R', '\026', 'c', 'r', 'e',
    'd', 'e', 'n', 't', 'i', 'a', 'l', 's', 'F', 'a', 'c', 't',
    'o', 'r', 'y', 'N', 'a', 'm', 'e', '\022', '/', '\n', '\006', 'c',
    'o', 'n', 'f', 'i', 'g', '\030', '\006', ' ', '\001', '(', '\013', '2',
    '\027', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '.', 'S', 't', 'r', 'u', 'c', 't',
    'R', '\006', 'c', 'o', 'n', 'f', 'i', 'g', '\022', '^', '\n', '\035',
    'p', 'e', 'r', '_', 's', 't', 'r', 'e', 'a', 'm', '_', 'b',
    'u', 'f', 'f', 'e', 'r', '_', 'l', 'i', 'm', 'i', 't', '_',
    'b', 'y', 't', 'e', 's', '\030', '\007', ' ', '\001', '(', '\013', '2',
    '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '3', '2',
    'V', 'a', 'l', 'u', 'e', 'R', '\031', 'p', 'e', 'r', 'S', 't',
    'r', 'e', 'a', 'm', 'B', 'u', 'f', 'f', 'e', 'r', 'L', 'i',
    'm', 'i', 't', 'B', 'y', 't', 'e', 's', '\022', '[', '\n', '\014',
    'c', 'h', 'a', 'n', 'n', 'e', 'l', '_', 'a', 'r', 'g', 's',
    '\030', '\010', ' ', '\001', '(', '\013', '2', '8', '.', 'e', 'n', 'v',
    'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o',
    'r', 'e', '.', 'v', '3', '.', 'G', 'r', 'p', 'c', 'S', 'e',
    'r', 'v', 'i', 'c', 'e', '.', 'G', 'o', 'o', 'g', 'l', 'e',
    'G', 'r', 'p', 'c', '.', 'C', 'h', 'a', 'n', 'n', 'e', 'l',
    'A', 'r', 'g', 's', 'R', '\013', 'c', 'h', 'a', 'n', 'n', 'e',
    'l', 'A', 'r', 'g', 's', '\032', '\235', '\002', '\n', '\016', 'S', 's',
    'l', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's',
    '\022', '?', '\n', '\n', 'r', 'o', 'o', 't', '_', 'c', 'e', 'r',
    't', 's', '\030', '\001', ' ', '\001', '(', '\013', '2', ' ', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'D', 'a', 't', 'a',
    'S', 'o', 'u', 'r', 'c', 'e', 'R', '\t', 'r', 'o', 'o', 't',
    'C', 'e', 'r', 't', 's', '\022', 'I', '\n', '\013', 'p', 'r', 'i',
    'v', 'a', 't', 'e', '_', 'k', 'e', 'y', '\030', '\002', ' ', '\001',
    '(', '\013', '2', ' ', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v',
    '3', '.', 'D', 'a', 't', 'a', 'S', 'o', 'u', 'r', 'c', 'e',
    'B', '\006', '\270', '\267', '\213', '\244', '\002', '\001', 'R', '\n', 'p', 'r',
    'i', 'v', 'a', 't', 'e', 'K', 'e', 'y', '\022', '?', '\n', '\n',
    'c', 'e', 'r', 't', '_', 'c', 'h', 'a', 'i', 'n', '\030', '\003',
    ' ', '\001', '(', '\013', '2', ' ', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e',
    '.', 'v', '3', '.', 'D', 'a', 't', 'a', 'S', 'o', 'u', 'r',
    'c', 'e', 'R', '\t', 'c', 'e', 'r', 't', 'C', 'h', 'a', 'i',
    'n', ':', '>', '\232', '\305', '\210', '\036', '9', '\n', '7', 'e', 'n',
    'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.', 'c',
    'o', 'r', 'e', '.', 'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v',
    'i', 'c', 'e', '.', 'G', 'o', 'o', 'g', 'l', 'e', 'G', 'r',
    'p', 'c', '.', 'S', 's', 'l', 'C', 'r', 'e', 'd', 'e', 'n',
    't', 'i', 'a', 'l', 's', '\032', '`', '\n', '\026', 'G', 'o', 'o',
    'g', 'l', 'e', 'L', 'o', 'c', 'a', 'l', 'C', 'r', 'e', 'd',
    'e', 'n', 't', 'i', 'a', 'l', 's', ':', 'F', '\232', '\305', '\210',
    '\036', 'A', '\n', '?', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p',
    'i', '.', 'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'G', 'r',
    'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'G', 'o',
    'o', 'g', 'l', 'e', 'G', 'r', 'p', 'c', '.', 'G', 'o', 'o',
    'g', 'l', 'e', 'L', 'o', 'c', 'a', 'l', 'C', 'r', 'e', 'd',
    'e', 'n', 't', 'i', 'a', 'l', 's', '\032', '\222', '\003', '\n', '\022',
    'C', 'h', 'a', 'n', 'n', 'e', 'l', 'C', 'r', 'e', 'd', 'e',
    'n', 't', 'i', 'a', 'l', 's', '\022', 'f', '\n', '\017', 's', 's',
    'l', '_', 'c', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l',
    's', '\030', '\001', ' ', '\001', '(', '\013', '2', ';', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c',
    'o', 'r', 'e', '.', 'v', '3', '.', 'G', 'r', 'p', 'c', 'S',
    'e', 'r', 'v', 'i', 'c', 'e', '.', 'G', 'o', 'o', 'g', 'l',
    'e', 'G', 'r', 'p', 'c', '.', 'S', 's', 'l', 'C', 'r', 'e',
    'd', 'e', 'n', 't', 'i', 'a', 'l', 's', 'H', '\000', 'R', '\016',
    's', 's', 'l', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a',
    'l', 's', '\022', '?', '\n', '\016', 'g', 'o', 'o', 'g', 'l', 'e',
    '_', 'd', 'e', 'f', 'a', 'u', 'l', 't', '\030', '\002', ' ', '\001',
    '(', '\013', '2', '\026', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'E', 'm', 'p',
    't', 'y', 'H', '\000', 'R', '\r', 'g', 'o', 'o', 'g', 'l', 'e',
    'D', 'e', 'f', 'a', 'u', 'l', 't', '\022', 'r', '\n', '\021', 'l',
    'o', 'c', 'a', 'l', '_', 'c', 'r', 'e', 'd', 'e', 'n', 't',
    'i', 'a', 'l', 's', '\030', '\003', ' ', '\001', '(', '\013', '2', 'C',
    '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i',
    'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'G', 'r',
    'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'G', 'o',
    'o', 'g', 'l', 'e', 'G', 'r', 'p', 'c', '.', 'G', 'o', 'o',
    'g', 'l', 'e', 'L', 'o', 'c', 'a', 'l', 'C', 'r', 'e', 'd',
    'e', 'n', 't', 'i', 'a', 'l', 's', 'H', '\000', 'R', '\020', 'l',
    'o', 'c', 'a', 'l', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i',
    'a', 'l', 's', ':', 'B', '\232', '\305', '\210', '\036', '=', '\n', ';',
    'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2',
    '.', 'c', 'o', 'r', 'e', '.', 'G', 'r', 'p', 'c', 'S', 'e',
    'r', 'v', 'i', 'c', 'e', '.', 'G', 'o', 'o', 'g', 'l', 'e',
    'G', 'r', 'p', 'c', '.', 'C', 'h', 'a', 'n', 'n', 'e', 'l',
    'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's', 'B',
    '\033', '\n', '\024', 'c', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a',
    'l', '_', 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'r', '\022',
    '\003', '\370', 'B', '\001', '\032', '\210', '\017', '\n', '\017', 'C', 'a', 'l',
    'l', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's',
    '\022', '#', '\n', '\014', 'a', 'c', 'c', 'e', 's', 's', '_', 't',
    'o', 'k', 'e', 'n', '\030', '\001', ' ', '\001', '(', '\t', 'H', '\000',
    'R', '\013', 'a', 'c', 'c', 'e', 's', 's', 'T', 'o', 'k', 'e',
    'n', '\022', 'L', '\n', '\025', 'g', 'o', 'o', 'g', 'l', 'e', '_',
    'c', 'o', 'm', 'p', 'u', 't', 'e', '_', 'e', 'n', 'g', 'i',
    'n', 'e', '\030', '\002', ' ', '\001', '(', '\013', '2', '\026', '.', 'g',
    'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b',
    'u', 'f', '.', 'E', 'm', 'p', 't', 'y', 'H', '\000', 'R', '\023',
    'g', 'o', 'o', 'g', 'l', 'e', 'C', 'o', 'm', 'p', 'u', 't',
    'e', 'E', 'n', 'g', 'i', 'n', 'e', '\022', '2', '\n', '\024', 'g',
    'o', 'o', 'g', 'l', 'e', '_', 'r', 'e', 'f', 'r', 'e', 's',
    'h', '_', 't', 'o', 'k', 'e', 'n', '\030', '\003', ' ', '\001', '(',
    '\t', 'H', '\000', 'R', '\022', 'g', 'o', 'o', 'g', 'l', 'e', 'R',
    'e', 'f', 'r', 'e', 's', 'h', 'T', 'o', 'k', 'e', 'n', '\022',
    '\236', '\001', '\n', '\032', 's', 'e', 'r', 'v', 'i', 'c', 'e', '_',
    'a', 'c', 'c', 'o', 'u', 'n', 't', '_', 'j', 'w', 't', '_',
    'a', 'c', 'c', 'e', 's', 's', '\030', '\004', ' ', '\001', '(', '\013',
    '2', '_', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.',
    'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '.',
    'G', 'o', 'o', 'g', 'l', 'e', 'G', 'r', 'p', 'c', '.', 'C',
    'a', 'l', 'l', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a',
    'l', 's', '.', 'S', 'e', 'r', 'v', 'i', 'c', 'e', 'A', 'c',
    'c', 'o', 'u', 'n', 't', 'J', 'W', 'T', 'A', 'c', 'c', 'e',
    's', 's', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l',
    's', 'H', '\000', 'R', '\027', 's', 'e', 'r', 'v', 'i', 'c', 'e',
    'A', 'c', 'c', 'o', 'u', 'n', 't', 'J', 'w', 't', 'A', 'c',
    'c', 'e', 's', 's', '\022', 'r', '\n', '\n', 'g', 'o', 'o', 'g',
    'l', 'e', '_', 'i', 'a', 'm', '\030', '\005', ' ', '\001', '(', '\013',
    '2', 'Q', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.',
    'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '.',
    'G', 'o', 'o', 'g', 'l', 'e', 'G', 'r', 'p', 'c', '.', 'C',
    'a', 'l', 'l', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a',
    'l', 's', '.', 'G', 'o', 'o', 'g', 'l', 'e', 'I', 'A', 'M',
    'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's', 'H',
    '\000', 'R', '\t', 'g', 'o', 'o', 'g', 'l', 'e', 'I', 'a', 'm',
    '\022', '}', '\n', '\013', 'f', 'r', 'o', 'm', '_', 'p', 'l', 'u',
    'g', 'i', 'n', '\030', '\006', ' ', '\001', '(', '\013', '2', 'Z', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g',
    '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'G', 'r', 'p',
    'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'G', 'o', 'o',
    'g', 'l', 'e', 'G', 'r', 'p', 'c', '.', 'C', 'a', 'l', 'l',
    'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's', '.',
    'M', 'e', 't', 'a', 'd', 'a', 't', 'a', 'C', 'r', 'e', 'd',
    'e', 'n', 't', 'i', 'a', 'l', 's', 'F', 'r', 'o', 'm', 'P',
    'l', 'u', 'g', 'i', 'n', 'H', '\000', 'R', '\n', 'f', 'r', 'o',
    'm', 'P', 'l', 'u', 'g', 'i', 'n', '\022', 'j', '\n', '\013', 's',
    't', 's', '_', 's', 'e', 'r', 'v', 'i', 'c', 'e', '\030', '\007',
    ' ', '\001', '(', '\013', '2', 'G', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e',
    '.', 'v', '3', '.', 'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v',
    'i', 'c', 'e', '.', 'G', 'o', 'o', 'g', 'l', 'e', 'G', 'r',
    'p', 'c', '.', 'C', 'a', 'l', 'l', 'C', 'r', 'e', 'd', 'e',
    'n', 't', 'i', 'a', 'l', 's', '.', 'S', 't', 's', 'S', 'e',
    'r', 'v', 'i', 'c', 'e', 'H', '\000', 'R', '\n', 's', 't', 's',
    'S', 'e', 'r', 'v', 'i', 'c', 'e', '\032', '\331', '\001', '\n', '\"',
    'S', 'e', 'r', 'v', 'i', 'c', 'e', 'A', 'c', 'c', 'o', 'u',
    'n', 't', 'J', 'W', 'T', 'A', 'c', 'c', 'e', 's', 's', 'C',
    'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's', '\022', '\031',
    '\n', '\010', 'j', 's', 'o', 'n', '_', 'k', 'e', 'y', '\030', '\001',
    ' ', '\001', '(', '\t', 'R', '\007', 'j', 's', 'o', 'n', 'K', 'e',
    'y', '\022', '4', '\n', '\026', 't', 'o', 'k', 'e', 'n', '_', 'l',
    'i', 'f', 'e', 't', 'i', 'm', 'e', '_', 's', 'e', 'c', 'o',
    'n', 'd', 's', '\030', '\002', ' ', '\001', '(', '\004', 'R', '\024', 't',
    'o', 'k', 'e', 'n', 'L', 'i', 'f', 'e', 't', 'i', 'm', 'e',
    'S', 'e', 'c', 'o', 'n', 'd', 's', ':', 'b', '\232', '\305', '\210',
    '\036', ']', '\n', '[', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p',
    'i', '.', 'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'G', 'r',
    'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'G', 'o',
    'o', 'g', 'l', 'e', 'G', 'r', 'p', 'c', '.', 'C', 'a', 'l',
    'l', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's',
    '.', 'S', 'e', 'r', 'v', 'i', 'c', 'e', 'A', 'c', 'c', 'o',
    'u', 'n', 't', 'J', 'W', 'T', 'A', 'c', 'c', 'e', 's', 's',
    'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's', '\032',
    '\314', '\001', '\n', '\024', 'G', 'o', 'o', 'g', 'l', 'e', 'I', 'A',
    'M', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's',
    '\022', '/', '\n', '\023', 'a', 'u', 't', 'h', 'o', 'r', 'i', 'z',
    'a', 't', 'i', 'o', 'n', '_', 't', 'o', 'k', 'e', 'n', '\030',
    '\001', ' ', '\001', '(', '\t', 'R', '\022', 'a', 'u', 't', 'h', 'o',
    'r', 'i', 'z', 'a', 't', 'i', 'o', 'n', 'T', 'o', 'k', 'e',
    'n', '\022', '-', '\n', '\022', 'a', 'u', 't', 'h', 'o', 'r', 'i',
    't', 'y', '_', 's', 'e', 'l', 'e', 'c', 't', 'o', 'r', '\030',
    '\002', ' ', '\001', '(', '\t', 'R', '\021', 'a', 'u', 't', 'h', 'o',
    'r', 'i', 't', 'y', 'S', 'e', 'l', 'e', 'c', 't', 'o', 'r',
    ':', 'T', '\232', '\305', '\210', '\036', 'O', '\n', 'M', 'e', 'n', 'v',
    'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.', 'c', 'o',
    'r', 'e', '.', 'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i',
    'c', 'e', '.', 'G', 'o', 'o', 'g', 'l', 'e', 'G', 'r', 'p',
    'c', '.', 'C', 'a', 'l', 'l', 'C', 'r', 'e', 'd', 'e', 'n',
    't', 'i', 'a', 'l', 's', '.', 'G', 'o', 'o', 'g', 'l', 'e',
    'I', 'A', 'M', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a',
    'l', 's', '\032', '\352', '\001', '\n', '\035', 'M', 'e', 't', 'a', 'd',
    'a', 't', 'a', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a',
    'l', 's', 'F', 'r', 'o', 'm', 'P', 'l', 'u', 'g', 'i', 'n',
    '\022', '\022', '\n', '\004', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001',
    '(', '\t', 'R', '\004', 'n', 'a', 'm', 'e', '\022', '9', '\n', '\014',
    't', 'y', 'p', 'e', 'd', '_', 'c', 'o', 'n', 'f', 'i', 'g',
    '\030', '\003', ' ', '\001', '(', '\013', '2', '\024', '.', 'g', 'o', 'o',
    'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f',
    '.', 'A', 'n', 'y', 'H', '\000', 'R', '\013', 't', 'y', 'p', 'e',
    'd', 'C', 'o', 'n', 'f', 'i', 'g', ':', ']', '\232', '\305', '\210',
    '\036', 'X', '\n', 'V', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p',
    'i', '.', 'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'G', 'r',
    'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'G', 'o',
    'o', 'g', 'l', 'e', 'G', 'r', 'p', 'c', '.', 'C', 'a', 'l',
    'l', 'C', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's',
    '.', 'M', 'e', 't', 'a', 'd', 'a', 't', 'a', 'C', 'r', 'e',
    'd', 'e', 'n', 't', 'i', 'a', 'l', 's', 'F', 'r', 'o', 'm',
    'P', 'l', 'u', 'g', 'i', 'n', 'B', '\r', '\n', '\013', 'c', 'o',
    'n', 'f', 'i', 'g', '_', 't', 'y', 'p', 'e', 'J', '\004', '\010',
    '\002', '\020', '\003', 'R', '\006', 'c', 'o', 'n', 'f', 'i', 'g', '\032',
    '\327', '\003', '\n', '\n', 'S', 't', 's', 'S', 'e', 'r', 'v', 'i',
    'c', 'e', '\022', ';', '\n', '\032', 't', 'o', 'k', 'e', 'n', '_',
    'e', 'x', 'c', 'h', 'a', 'n', 'g', 'e', '_', 's', 'e', 'r',
    'v', 'i', 'c', 'e', '_', 'u', 'r', 'i', '\030', '\001', ' ', '\001',
    '(', '\t', 'R', '\027', 't', 'o', 'k', 'e', 'n', 'E', 'x', 'c',
    'h', 'a', 'n', 'g', 'e', 'S', 'e', 'r', 'v', 'i', 'c', 'e',
    'U', 'r', 'i', '\022', '\032', '\n', '\010', 'r', 'e', 's', 'o', 'u',
    'r', 'c', 'e', '\030', '\002', ' ', '\001', '(', '\t', 'R', '\010', 'r',
    'e', 's', 'o', 'u', 'r', 'c', 'e', '\022', '\032', '\n', '\010', 'a',
    'u', 'd', 'i', 'e', 'n', 'c', 'e', '\030', '\003', ' ', '\001', '(',
    '\t', 'R', '\010', 'a', 'u', 'd', 'i', 'e', 'n', 'c', 'e', '\022',
    '\024', '\n', '\005', 's', 'c', 'o', 'p', 'e', '\030', '\004', ' ', '\001',
    '(', '\t', 'R', '\005', 's', 'c', 'o', 'p', 'e', '\022', '0', '\n',
    '\024', 'r', 'e', 'q', 'u', 'e', 's', 't', 'e', 'd', '_', 't',
    'o', 'k', 'e', 'n', '_', 't', 'y', 'p', 'e', '\030', '\005', ' ',
    '\001', '(', '\t', 'R', '\022', 'r', 'e', 'q', 'u', 'e', 's', 't',
    'e', 'd', 'T', 'o', 'k', 'e', 'n', 'T', 'y', 'p', 'e', '\022',
    '5', '\n', '\022', 's', 'u', 'b', 'j', 'e', 'c', 't', '_', 't',
    'o', 'k', 'e', 'n', '_', 'p', 'a', 't', 'h', '\030', '\006', ' ',
    '\001', '(', '\t', 'B', '\007', '\372', 'B', '\004', 'r', '\002', '\020', '\001',
    'R', '\020', 's', 'u', 'b', 'j', 'e', 'c', 't', 'T', 'o', 'k',
    'e', 'n', 'P', 'a', 't', 'h', '\022', '5', '\n', '\022', 's', 'u',
    'b', 'j', 'e', 'c', 't', '_', 't', 'o', 'k', 'e', 'n', '_',
    't', 'y', 'p', 'e', '\030', '\007', ' ', '\001', '(', '\t', 'B', '\007',
    '\372', 'B', '\004', 'r', '\002', '\020', '\001', 'R', '\020', 's', 'u', 'b',
    'j', 'e', 'c', 't', 'T', 'o', 'k', 'e', 'n', 'T', 'y', 'p',
    'e', '\022', '(', '\n', '\020', 'a', 'c', 't', 'o', 'r', '_', 't',
    'o', 'k', 'e', 'n', '_', 'p', 'a', 't', 'h', '\030', '\010', ' ',
    '\001', '(', '\t', 'R', '\016', 'a', 'c', 't', 'o', 'r', 'T', 'o',
    'k', 'e', 'n', 'P', 'a', 't', 'h', '\022', '(', '\n', '\020', 'a',
    'c', 't', 'o', 'r', '_', 't', 'o', 'k', 'e', 'n', '_', 't',
    'y', 'p', 'e', '\030', '\t', ' ', '\001', '(', '\t', 'R', '\016', 'a',
    'c', 't', 'o', 'r', 'T', 'o', 'k', 'e', 'n', 'T', 'y', 'p',
    'e', ':', 'J', '\232', '\305', '\210', '\036', 'E', '\n', 'C', 'e', 'n',
    'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.', 'c',
    'o', 'r', 'e', '.', 'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v',
    'i', 'c', 'e', '.', 'G', 'o', 'o', 'g', 'l', 'e', 'G', 'r',
    'p', 'c', '.', 'C', 'a', 'l', 'l', 'C', 'r', 'e', 'd', 'e',
    'n', 't', 'i', 'a', 'l', 's', '.', 'S', 't', 's', 'S', 'e',
    'r', 'v', 'i', 'c', 'e', ':', '?', '\232', '\305', '\210', '\036', ':',
    '\n', '8', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.',
    'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'G', 'r', 'p', 'c',
    'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'G', 'o', 'o', 'g',
    'l', 'e', 'G', 'r', 'p', 'c', '.', 'C', 'a', 'l', 'l', 'C',
    'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l', 's', 'B', '\033',
    '\n', '\024', 'c', 'r', 'e', 'd', 'e', 'n', 't', 'i', 'a', 'l',
    '_', 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'r', '\022', '\003',
    '\370', 'B', '\001', '\032', '\303', '\002', '\n', '\013', 'C', 'h', 'a', 'n',
    'n', 'e', 'l', 'A', 'r', 'g', 's', '\022', 'V', '\n', '\004', 'a',
    'r', 'g', 's', '\030', '\001', ' ', '\003', '(', '\013', '2', 'B', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g',
    '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'G', 'r', 'p',
    'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'G', 'o', 'o',
    'g', 'l', 'e', 'G', 'r', 'p', 'c', '.', 'C', 'h', 'a', 'n',
    'n', 'e', 'l', 'A', 'r', 'g', 's', '.', 'A', 'r', 'g', 's',
    'E', 'n', 't', 'r', 'y', 'R', '\004', 'a', 'r', 'g', 's', '\032',
    'c', '\n', '\005', 'V', 'a', 'l', 'u', 'e', '\022', '#', '\n', '\014',
    's', 't', 'r', 'i', 'n', 'g', '_', 'v', 'a', 'l', 'u', 'e',
    '\030', '\001', ' ', '\001', '(', '\t', 'H', '\000', 'R', '\013', 's', 't',
    'r', 'i', 'n', 'g', 'V', 'a', 'l', 'u', 'e', '\022', '\035', '\n',
    '\t', 'i', 'n', 't', '_', 'v', 'a', 'l', 'u', 'e', '\030', '\002',
    ' ', '\001', '(', '\003', 'H', '\000', 'R', '\010', 'i', 'n', 't', 'V',
    'a', 'l', 'u', 'e', 'B', '\026', '\n', '\017', 'v', 'a', 'l', 'u',
    'e', '_', 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'r', '\022',
    '\003', '\370', 'B', '\001', '\032', 'w', '\n', '\t', 'A', 'r', 'g', 's',
    'E', 'n', 't', 'r', 'y', '\022', '\020', '\n', '\003', 'k', 'e', 'y',
    '\030', '\001', ' ', '\001', '(', '\t', 'R', '\003', 'k', 'e', 'y', '\022',
    'T', '\n', '\005', 'v', 'a', 'l', 'u', 'e', '\030', '\002', ' ', '\001',
    '(', '\013', '2', '>', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v',
    '3', '.', 'G', 'r', 'p', 'c', 'S', 'e', 'r', 'v', 'i', 'c',
    'e', '.', 'G', 'o', 'o', 'g', 'l', 'e', 'G', 'r', 'p', 'c',
    '.', 'C', 'h', 'a', 'n', 'n', 'e', 'l', 'A', 'r', 'g', 's',
    '.', 'V', 'a', 'l', 'u', 'e', 'R', '\005', 'v', 'a', 'l', 'u',
    'e', ':', '\002', '8', '\001', ':', '/', '\232', '\305', '\210', '\036', '*',
    '\n', '(', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.',
    'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'G', 'r', 'p', 'c',
    'S', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'G', 'o', 'o', 'g',
    'l', 'e', 'G', 'r', 'p', 'c', ':', '$', '\232', '\305', '\210', '\036',
    '\037', '\n', '\035', 'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i',
    '.', 'v', '2', '.', 'c', 'o', 'r', 'e', '.', 'G', 'r', 'p',
    'c', 'S', 'e', 'r', 'v', 'i', 'c', 'e', 'B', '\027', '\n', '\020',
    't', 'a', 'r', 'g', 'e', 't', '_', 's', 'p', 'e', 'c', 'i',
    'f', 'i', 'e', 'r', '\022', '\003', '\370', 'B', '\001', 'J', '\004', '\010',
    '\004', '\020', '\005', 'B', '\204', '\001', '\n', '\"', 'i', 'o', '.', 'e',
    'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c',
    'o', 'r', 'e', '.', 'v', '3', 'B', '\020', 'G', 'r', 'p', 'c',
    'S', 'e', 'r', 'v', 'i', 'c', 'e', 'P', 'r', 'o', 't', 'o',
    'P', '\001', 'Z', 'B', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c',
    'o', 'm', '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x',
    'y', '/', 'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l',
    '-', 'p', 'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y',
    '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e',
    '/', 'v', '3', ';', 'c', 'o', 'r', 'e', 'v', '3', '\272', '\200',
    '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't',
    'o', '3',
};

static _upb_DefPool_Init *deps[11] = {
    &envoy_config_core_v3_base_proto_upbdefinit,
    &google_protobuf_any_proto_upbdefinit,
    &google_protobuf_duration_proto_upbdefinit,
    &google_protobuf_empty_proto_upbdefinit,
    &google_protobuf_struct_proto_upbdefinit,
    &google_protobuf_wrappers_proto_upbdefinit,
    &udpa_annotations_sensitive_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_core_v3_grpc_service_proto_upbdefinit = {
    deps,
    &envoy_config_core_v3_grpc_service_proto_upb_file_layout,
    "envoy/config/core/v3/grpc_service.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
