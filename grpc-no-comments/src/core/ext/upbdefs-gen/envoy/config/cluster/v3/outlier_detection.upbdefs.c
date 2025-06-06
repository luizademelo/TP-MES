
#include "upb/reflection/def.h"
#include "envoy/config/cluster/v3/outlier_detection.upbdefs.h"
#include "envoy/config/cluster/v3/outlier_detection.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_extension_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_duration_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_wrappers_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[2892] = {
    '\n', '/', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'l', 'u', 's', 't', 'e', 'r', '/', 'v',
    '3', '/', 'o', 'u', 't', 'l', 'i', 'e', 'r', '_', 'd', 'e',
    't', 'e', 'c', 't', 'i', 'o', 'n', '.', 'p', 'r', 'o', 't',
    'o', '\022', '\027', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'c', 'l', 'u', 's', 't', 'e', 'r', '.',
    'v', '3', '\032', '$', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o',
    'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3',
    '/', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', '.', 'p',
    'r', 'o', 't', 'o', '\032', '\036', 'g', 'o', 'o', 'g', 'l', 'e',
    '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'd', 'u',
    'r', 'a', 't', 'i', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\036', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '/', 'w', 'r', 'a', 'p', 'p', 'e',
    'r', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '\035', 'u', 'd',
    'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o',
    'n', 's', '/', 's', 't', 'a', 't', 'u', 's', '.', 'p', 'r',
    'o', 't', 'o', '\032', '!', 'u', 'd', 'p', 'a', '/', 'a', 'n',
    'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 'v', 'e',
    'r', 's', 'i', 'o', 'n', 'i', 'n', 'g', '.', 'p', 'r', 'o',
    't', 'o', '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e',
    '/', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p', 'r',
    'o', 't', 'o', '\"', '\241', '\023', '\n', '\020', 'O', 'u', 't', 'l',
    'i', 'e', 'r', 'D', 'e', 't', 'e', 'c', 't', 'i', 'o', 'n',
    '\022', 'E', '\n', '\017', 'c', 'o', 'n', 's', 'e', 'c', 'u', 't',
    'i', 'v', 'e', '_', '5', 'x', 'x', '\030', '\001', ' ', '\001', '(',
    '\013', '2', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p',
    'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't',
    '3', '2', 'V', 'a', 'l', 'u', 'e', 'R', '\016', 'c', 'o', 'n',
    's', 'e', 'c', 'u', 't', 'i', 'v', 'e', '5', 'x', 'x', '\022',
    '?', '\n', '\010', 'i', 'n', 't', 'e', 'r', 'v', 'a', 'l', '\030',
    '\002', ' ', '\001', '(', '\013', '2', '\031', '.', 'g', 'o', 'o', 'g',
    'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.',
    'D', 'u', 'r', 'a', 't', 'i', 'o', 'n', 'B', '\010', '\372', 'B',
    '\005', '\252', '\001', '\002', '*', '\000', 'R', '\010', 'i', 'n', 't', 'e',
    'r', 'v', 'a', 'l', '\022', 'Q', '\n', '\022', 'b', 'a', 's', 'e',
    '_', 'e', 'j', 'e', 'c', 't', 'i', 'o', 'n', '_', 't', 'i',
    'm', 'e', '\030', '\003', ' ', '\001', '(', '\013', '2', '\031', '.', 'g',
    'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b',
    'u', 'f', '.', 'D', 'u', 'r', 'a', 't', 'i', 'o', 'n', 'B',
    '\010', '\372', 'B', '\005', '\252', '\001', '\002', '*', '\000', 'R', '\020', 'b',
    'a', 's', 'e', 'E', 'j', 'e', 'c', 't', 'i', 'o', 'n', 'T',
    'i', 'm', 'e', '\022', 'W', '\n', '\024', 'm', 'a', 'x', '_', 'e',
    'j', 'e', 'c', 't', 'i', 'o', 'n', '_', 'p', 'e', 'r', 'c',
    'e', 'n', 't', '\030', '\004', ' ', '\001', '(', '\013', '2', '\034', '.',
    'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o',
    'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '3', '2', 'V', 'a',
    'l', 'u', 'e', 'B', '\007', '\372', 'B', '\004', '*', '\002', '\030', 'd',
    'R', '\022', 'm', 'a', 'x', 'E', 'j', 'e', 'c', 't', 'i', 'o',
    'n', 'P', 'e', 'r', 'c', 'e', 'n', 't', '\022', 'a', '\n', '\031',
    'e', 'n', 'f', 'o', 'r', 'c', 'i', 'n', 'g', '_', 'c', 'o',
    'n', 's', 'e', 'c', 'u', 't', 'i', 'v', 'e', '_', '5', 'x',
    'x', '\030', '\005', ' ', '\001', '(', '\013', '2', '\034', '.', 'g', 'o',
    'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u',
    'f', '.', 'U', 'I', 'n', 't', '3', '2', 'V', 'a', 'l', 'u',
    'e', 'B', '\007', '\372', 'B', '\004', '*', '\002', '\030', 'd', 'R', '\027',
    'e', 'n', 'f', 'o', 'r', 'c', 'i', 'n', 'g', 'C', 'o', 'n',
    's', 'e', 'c', 'u', 't', 'i', 'v', 'e', '5', 'x', 'x', '\022',
    '[', '\n', '\026', 'e', 'n', 'f', 'o', 'r', 'c', 'i', 'n', 'g',
    '_', 's', 'u', 'c', 'c', 'e', 's', 's', '_', 'r', 'a', 't',
    'e', '\030', '\006', ' ', '\001', '(', '\013', '2', '\034', '.', 'g', 'o',
    'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u',
    'f', '.', 'U', 'I', 'n', 't', '3', '2', 'V', 'a', 'l', 'u',
    'e', 'B', '\007', '\372', 'B', '\004', '*', '\002', '\030', 'd', 'R', '\024',
    'e', 'n', 'f', 'o', 'r', 'c', 'i', 'n', 'g', 'S', 'u', 'c',
    'c', 'e', 's', 's', 'R', 'a', 't', 'e', '\022', 'Y', '\n', '\032',
    's', 'u', 'c', 'c', 'e', 's', 's', '_', 'r', 'a', 't', 'e',
    '_', 'm', 'i', 'n', 'i', 'm', 'u', 'm', '_', 'h', 'o', 's',
    't', 's', '\030', '\007', ' ', '\001', '(', '\013', '2', '\034', '.', 'g',
    'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b',
    'u', 'f', '.', 'U', 'I', 'n', 't', '3', '2', 'V', 'a', 'l',
    'u', 'e', 'R', '\027', 's', 'u', 'c', 'c', 'e', 's', 's', 'R',
    'a', 't', 'e', 'M', 'i', 'n', 'i', 'm', 'u', 'm', 'H', 'o',
    's', 't', 's', '\022', '[', '\n', '\033', 's', 'u', 'c', 'c', 'e',
    's', 's', '_', 'r', 'a', 't', 'e', '_', 'r', 'e', 'q', 'u',
    'e', 's', 't', '_', 'v', 'o', 'l', 'u', 'm', 'e', '\030', '\010',
    ' ', '\001', '(', '\013', '2', '\034', '.', 'g', 'o', 'o', 'g', 'l',
    'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'U',
    'I', 'n', 't', '3', '2', 'V', 'a', 'l', 'u', 'e', 'R', '\030',
    's', 'u', 'c', 'c', 'e', 's', 's', 'R', 'a', 't', 'e', 'R',
    'e', 'q', 'u', 'e', 's', 't', 'V', 'o', 'l', 'u', 'm', 'e',
    '\022', 'W', '\n', '\031', 's', 'u', 'c', 'c', 'e', 's', 's', '_',
    'r', 'a', 't', 'e', '_', 's', 't', 'd', 'e', 'v', '_', 'f',
    'a', 'c', 't', 'o', 'r', '\030', '\t', ' ', '\001', '(', '\013', '2',
    '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '3', '2',
    'V', 'a', 'l', 'u', 'e', 'R', '\026', 's', 'u', 'c', 'c', 'e',
    's', 's', 'R', 'a', 't', 'e', 'S', 't', 'd', 'e', 'v', 'F',
    'a', 'c', 't', 'o', 'r', '\022', '\\', '\n', '\033', 'c', 'o', 'n',
    's', 'e', 'c', 'u', 't', 'i', 'v', 'e', '_', 'g', 'a', 't',
    'e', 'w', 'a', 'y', '_', 'f', 'a', 'i', 'l', 'u', 'r', 'e',
    '\030', '\n', ' ', '\001', '(', '\013', '2', '\034', '.', 'g', 'o', 'o',
    'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f',
    '.', 'U', 'I', 'n', 't', '3', '2', 'V', 'a', 'l', 'u', 'e',
    'R', '\031', 'c', 'o', 'n', 's', 'e', 'c', 'u', 't', 'i', 'v',
    'e', 'G', 'a', 't', 'e', 'w', 'a', 'y', 'F', 'a', 'i', 'l',
    'u', 'r', 'e', '\022', 'x', '\n', '%', 'e', 'n', 'f', 'o', 'r',
    'c', 'i', 'n', 'g', '_', 'c', 'o', 'n', 's', 'e', 'c', 'u',
    't', 'i', 'v', 'e', '_', 'g', 'a', 't', 'e', 'w', 'a', 'y',
    '_', 'f', 'a', 'i', 'l', 'u', 'r', 'e', '\030', '\013', ' ', '\001',
    '(', '\013', '2', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n',
    't', '3', '2', 'V', 'a', 'l', 'u', 'e', 'B', '\007', '\372', 'B',
    '\004', '*', '\002', '\030', 'd', 'R', '\"', 'e', 'n', 'f', 'o', 'r',
    'c', 'i', 'n', 'g', 'C', 'o', 'n', 's', 'e', 'c', 'u', 't',
    'i', 'v', 'e', 'G', 'a', 't', 'e', 'w', 'a', 'y', 'F', 'a',
    'i', 'l', 'u', 'r', 'e', '\022', 'J', '\n', '\"', 's', 'p', 'l',
    'i', 't', '_', 'e', 'x', 't', 'e', 'r', 'n', 'a', 'l', '_',
    'l', 'o', 'c', 'a', 'l', '_', 'o', 'r', 'i', 'g', 'i', 'n',
    '_', 'e', 'r', 'r', 'o', 'r', 's', '\030', '\014', ' ', '\001', '(',
    '\010', 'R', '\036', 's', 'p', 'l', 'i', 't', 'E', 'x', 't', 'e',
    'r', 'n', 'a', 'l', 'L', 'o', 'c', 'a', 'l', 'O', 'r', 'i',
    'g', 'i', 'n', 'E', 'r', 'r', 'o', 'r', 's', '\022', 'e', '\n',
    ' ', 'c', 'o', 'n', 's', 'e', 'c', 'u', 't', 'i', 'v', 'e',
    '_', 'l', 'o', 'c', 'a', 'l', '_', 'o', 'r', 'i', 'g', 'i',
    'n', '_', 'f', 'a', 'i', 'l', 'u', 'r', 'e', '\030', '\r', ' ',
    '\001', '(', '\013', '2', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e',
    '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'U', 'I',
    'n', 't', '3', '2', 'V', 'a', 'l', 'u', 'e', 'R', '\035', 'c',
    'o', 'n', 's', 'e', 'c', 'u', 't', 'i', 'v', 'e', 'L', 'o',
    'c', 'a', 'l', 'O', 'r', 'i', 'g', 'i', 'n', 'F', 'a', 'i',
    'l', 'u', 'r', 'e', '\022', '\201', '\001', '\n', '*', 'e', 'n', 'f',
    'o', 'r', 'c', 'i', 'n', 'g', '_', 'c', 'o', 'n', 's', 'e',
    'c', 'u', 't', 'i', 'v', 'e', '_', 'l', 'o', 'c', 'a', 'l',
    '_', 'o', 'r', 'i', 'g', 'i', 'n', '_', 'f', 'a', 'i', 'l',
    'u', 'r', 'e', '\030', '\016', ' ', '\001', '(', '\013', '2', '\034', '.',
    'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o',
    'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '3', '2', 'V', 'a',
    'l', 'u', 'e', 'B', '\007', '\372', 'B', '\004', '*', '\002', '\030', 'd',
    'R', '&', 'e', 'n', 'f', 'o', 'r', 'c', 'i', 'n', 'g', 'C',
    'o', 'n', 's', 'e', 'c', 'u', 't', 'i', 'v', 'e', 'L', 'o',
    'c', 'a', 'l', 'O', 'r', 'i', 'g', 'i', 'n', 'F', 'a', 'i',
    'l', 'u', 'r', 'e', '\022', 's', '\n', '#', 'e', 'n', 'f', 'o',
    'r', 'c', 'i', 'n', 'g', '_', 'l', 'o', 'c', 'a', 'l', '_',
    'o', 'r', 'i', 'g', 'i', 'n', '_', 's', 'u', 'c', 'c', 'e',
    's', 's', '_', 'r', 'a', 't', 'e', '\030', '\017', ' ', '\001', '(',
    '\013', '2', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p',
    'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't',
    '3', '2', 'V', 'a', 'l', 'u', 'e', 'B', '\007', '\372', 'B', '\004',
    '*', '\002', '\030', 'd', 'R', '\037', 'e', 'n', 'f', 'o', 'r', 'c',
    'i', 'n', 'g', 'L', 'o', 'c', 'a', 'l', 'O', 'r', 'i', 'g',
    'i', 'n', 'S', 'u', 'c', 'c', 'e', 's', 's', 'R', 'a', 't',
    'e', '\022', 'g', '\n', '\034', 'f', 'a', 'i', 'l', 'u', 'r', 'e',
    '_', 'p', 'e', 'r', 'c', 'e', 'n', 't', 'a', 'g', 'e', '_',
    't', 'h', 'r', 'e', 's', 'h', 'o', 'l', 'd', '\030', '\020', ' ',
    '\001', '(', '\013', '2', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e',
    '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'U', 'I',
    'n', 't', '3', '2', 'V', 'a', 'l', 'u', 'e', 'B', '\007', '\372',
    'B', '\004', '*', '\002', '\030', 'd', 'R', '\032', 'f', 'a', 'i', 'l',
    'u', 'r', 'e', 'P', 'e', 'r', 'c', 'e', 'n', 't', 'a', 'g',
    'e', 'T', 'h', 'r', 'e', 's', 'h', 'o', 'l', 'd', '\022', 'g',
    '\n', '\034', 'e', 'n', 'f', 'o', 'r', 'c', 'i', 'n', 'g', '_',
    'f', 'a', 'i', 'l', 'u', 'r', 'e', '_', 'p', 'e', 'r', 'c',
    'e', 'n', 't', 'a', 'g', 'e', '\030', '\021', ' ', '\001', '(', '\013',
    '2', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r',
    'o', 't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '3',
    '2', 'V', 'a', 'l', 'u', 'e', 'B', '\007', '\372', 'B', '\004', '*',
    '\002', '\030', 'd', 'R', '\032', 'e', 'n', 'f', 'o', 'r', 'c', 'i',
    'n', 'g', 'F', 'a', 'i', 'l', 'u', 'r', 'e', 'P', 'e', 'r',
    'c', 'e', 'n', 't', 'a', 'g', 'e', '\022', '\177', '\n', ')', 'e',
    'n', 'f', 'o', 'r', 'c', 'i', 'n', 'g', '_', 'f', 'a', 'i',
    'l', 'u', 'r', 'e', '_', 'p', 'e', 'r', 'c', 'e', 'n', 't',
    'a', 'g', 'e', '_', 'l', 'o', 'c', 'a', 'l', '_', 'o', 'r',
    'i', 'g', 'i', 'n', '\030', '\022', ' ', '\001', '(', '\013', '2', '\034',
    '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't',
    'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '3', '2', 'V',
    'a', 'l', 'u', 'e', 'B', '\007', '\372', 'B', '\004', '*', '\002', '\030',
    'd', 'R', '%', 'e', 'n', 'f', 'o', 'r', 'c', 'i', 'n', 'g',
    'F', 'a', 'i', 'l', 'u', 'r', 'e', 'P', 'e', 'r', 'c', 'e',
    'n', 't', 'a', 'g', 'e', 'L', 'o', 'c', 'a', 'l', 'O', 'r',
    'i', 'g', 'i', 'n', '\022', 'e', '\n', ' ', 'f', 'a', 'i', 'l',
    'u', 'r', 'e', '_', 'p', 'e', 'r', 'c', 'e', 'n', 't', 'a',
    'g', 'e', '_', 'm', 'i', 'n', 'i', 'm', 'u', 'm', '_', 'h',
    'o', 's', 't', 's', '\030', '\023', ' ', '\001', '(', '\013', '2', '\034',
    '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't',
    'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '3', '2', 'V',
    'a', 'l', 'u', 'e', 'R', '\035', 'f', 'a', 'i', 'l', 'u', 'r',
    'e', 'P', 'e', 'r', 'c', 'e', 'n', 't', 'a', 'g', 'e', 'M',
    'i', 'n', 'i', 'm', 'u', 'm', 'H', 'o', 's', 't', 's', '\022',
    'g', '\n', '!', 'f', 'a', 'i', 'l', 'u', 'r', 'e', '_', 'p',
    'e', 'r', 'c', 'e', 'n', 't', 'a', 'g', 'e', '_', 'r', 'e',
    'q', 'u', 'e', 's', 't', '_', 'v', 'o', 'l', 'u', 'm', 'e',
    '\030', '\024', ' ', '\001', '(', '\013', '2', '\034', '.', 'g', 'o', 'o',
    'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f',
    '.', 'U', 'I', 'n', 't', '3', '2', 'V', 'a', 'l', 'u', 'e',
    'R', '\036', 'f', 'a', 'i', 'l', 'u', 'r', 'e', 'P', 'e', 'r',
    'c', 'e', 'n', 't', 'a', 'g', 'e', 'R', 'e', 'q', 'u', 'e',
    's', 't', 'V', 'o', 'l', 'u', 'm', 'e', '\022', 'O', '\n', '\021',
    'm', 'a', 'x', '_', 'e', 'j', 'e', 'c', 't', 'i', 'o', 'n',
    '_', 't', 'i', 'm', 'e', '\030', '\025', ' ', '\001', '(', '\013', '2',
    '\031', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '.', 'D', 'u', 'r', 'a', 't', 'i',
    'o', 'n', 'B', '\010', '\372', 'B', '\005', '\252', '\001', '\002', '*', '\000',
    'R', '\017', 'm', 'a', 'x', 'E', 'j', 'e', 'c', 't', 'i', 'o',
    'n', 'T', 'i', 'm', 'e', '\022', 'R', '\n', '\030', 'm', 'a', 'x',
    '_', 'e', 'j', 'e', 'c', 't', 'i', 'o', 'n', '_', 't', 'i',
    'm', 'e', '_', 'j', 'i', 't', 't', 'e', 'r', '\030', '\026', ' ',
    '\001', '(', '\013', '2', '\031', '.', 'g', 'o', 'o', 'g', 'l', 'e',
    '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'D', 'u',
    'r', 'a', 't', 'i', 'o', 'n', 'R', '\025', 'm', 'a', 'x', 'E',
    'j', 'e', 'c', 't', 'i', 'o', 'n', 'T', 'i', 'm', 'e', 'J',
    'i', 't', 't', 'e', 'r', '\022', 'w', '\n', '+', 's', 'u', 'c',
    'c', 'e', 's', 's', 'f', 'u', 'l', '_', 'a', 'c', 't', 'i',
    'v', 'e', '_', 'h', 'e', 'a', 'l', 't', 'h', '_', 'c', 'h',
    'e', 'c', 'k', '_', 'u', 'n', 'e', 'j', 'e', 'c', 't', '_',
    'h', 'o', 's', 't', '\030', '\027', ' ', '\001', '(', '\013', '2', '\032',
    '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't',
    'o', 'b', 'u', 'f', '.', 'B', 'o', 'o', 'l', 'V', 'a', 'l',
    'u', 'e', 'R', '&', 's', 'u', 'c', 'c', 'e', 's', 's', 'f',
    'u', 'l', 'A', 'c', 't', 'i', 'v', 'e', 'H', 'e', 'a', 'l',
    't', 'h', 'C', 'h', 'e', 'c', 'k', 'U', 'n', 'e', 'j', 'e',
    'c', 't', 'H', 'o', 's', 't', '\022', 'F', '\n', '\010', 'm', 'o',
    'n', 'i', 't', 'o', 'r', 's', '\030', '\030', ' ', '\003', '(', '\013',
    '2', '*', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.',
    'T', 'y', 'p', 'e', 'd', 'E', 'x', 't', 'e', 'n', 's', 'i',
    'o', 'n', 'C', 'o', 'n', 'f', 'i', 'g', 'R', '\010', 'm', 'o',
    'n', 'i', 't', 'o', 'r', 's', '\022', 'M', '\n', '\025', 'a', 'l',
    'w', 'a', 'y', 's', '_', 'e', 'j', 'e', 'c', 't', '_', 'o',
    'n', 'e', '_', 'h', 'o', 's', 't', '\030', '\031', ' ', '\001', '(',
    '\013', '2', '\032', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p',
    'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'B', 'o', 'o', 'l',
    'V', 'a', 'l', 'u', 'e', 'R', '\022', 'a', 'l', 'w', 'a', 'y',
    's', 'E', 'j', 'e', 'c', 't', 'O', 'n', 'e', 'H', 'o', 's',
    't', ':', ',', '\232', '\305', '\210', '\036', '\'', '\n', '%', 'e', 'n',
    'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.', 'c',
    'l', 'u', 's', 't', 'e', 'r', '.', 'O', 'u', 't', 'l', 'i',
    'e', 'r', 'D', 'e', 't', 'e', 'c', 't', 'i', 'o', 'n', 'B',
    '\222', '\001', '\n', '%', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.',
    'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'l', 'u', 's', 't',
    'e', 'r', '.', 'v', '3', 'B', '\025', 'O', 'u', 't', 'l', 'i',
    'e', 'r', 'D', 'e', 't', 'e', 'c', 't', 'i', 'o', 'n', 'P',
    'r', 'o', 't', 'o', 'P', '\001', 'Z', 'H', 'g', 'i', 't', 'h',
    'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o', 'y',
    'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o', 'n',
    't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/', 'e',
    'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f', 'i', 'g', '/',
    'c', 'l', 'u', 's', 't', 'e', 'r', '/', 'v', '3', ';', 'c',
    'l', 'u', 's', 't', 'e', 'r', 'v', '3', '\272', '\200', '\310', '\321',
    '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[7] = {
    &envoy_config_core_v3_extension_proto_upbdefinit,
    &google_protobuf_duration_proto_upbdefinit,
    &google_protobuf_wrappers_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_cluster_v3_outlier_detection_proto_upbdefinit = {
    deps,
    &envoy_config_cluster_v3_outlier_detection_proto_upb_file_layout,
    "envoy/config/cluster/v3/outlier_detection.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
