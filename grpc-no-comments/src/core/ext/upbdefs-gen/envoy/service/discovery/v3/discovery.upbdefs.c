
#include "upb/reflection/def.h"
#include "envoy/service/discovery/v3/discovery.upbdefs.h"
#include "envoy/service/discovery/v3/discovery.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_base_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_duration_proto_upbdefinit;
extern _upb_DefPool_Init google_rpc_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[4354] = {
    '\n', '*', 'e', 'n', 'v', 'o', 'y', '/', 's', 'e', 'r', 'v',
    'i', 'c', 'e', '/', 'd', 'i', 's', 'c', 'o', 'v', 'e', 'r',
    'y', '/', 'v', '3', '/', 'd', 'i', 's', 'c', 'o', 'v', 'e',
    'r', 'y', '.', 'p', 'r', 'o', 't', 'o', '\022', '\032', 'e', 'n',
    'v', 'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.',
    'd', 'i', 's', 'c', 'o', 'v', 'e', 'r', 'y', '.', 'v', '3',
    '\032', '\037', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3', '/', 'b',
    'a', 's', 'e', '.', 'p', 'r', 'o', 't', 'o', '\032', '\031', 'g',
    'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b',
    'u', 'f', '/', 'a', 'n', 'y', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '\036', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '/', 'd', 'u', 'r', 'a', 't', 'i',
    'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027', 'g', 'o',
    'o', 'g', 'l', 'e', '/', 'r', 'p', 'c', '/', 's', 't', 'a',
    't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '\035', 'u',
    'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 's', '/', 's', 't', 'a', 't', 'u', 's', '.', 'p',
    'r', 'o', 't', 'o', '\032', '!', 'u', 'd', 'p', 'a', '/', 'a',
    'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 'v',
    'e', 'r', 's', 'i', 'o', 'n', 'i', 'n', 'g', '.', 'p', 'r',
    'o', 't', 'o', '\032', '\027', 'v', 'a', 'l', 'i', 'd', 'a', 't',
    'e', '/', 'v', 'a', 'l', 'i', 'd', 'a', 't', 'e', '.', 'p',
    'r', 'o', 't', 'o', '\"', '\336', '\001', '\n', '\017', 'R', 'e', 's',
    'o', 'u', 'r', 'c', 'e', 'L', 'o', 'c', 'a', 't', 'o', 'r',
    '\022', '\022', '\n', '\004', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001',
    '(', '\t', 'R', '\004', 'n', 'a', 'm', 'e', '\022', 'q', '\n', '\022',
    'd', 'y', 'n', 'a', 'm', 'i', 'c', '_', 'p', 'a', 'r', 'a',
    'm', 'e', 't', 'e', 'r', 's', '\030', '\002', ' ', '\003', '(', '\013',
    '2', 'B', '.', 'e', 'n', 'v', 'o', 'y', '.', 's', 'e', 'r',
    'v', 'i', 'c', 'e', '.', 'd', 'i', 's', 'c', 'o', 'v', 'e',
    'r', 'y', '.', 'v', '3', '.', 'R', 'e', 's', 'o', 'u', 'r',
    'c', 'e', 'L', 'o', 'c', 'a', 't', 'o', 'r', '.', 'D', 'y',
    'n', 'a', 'm', 'i', 'c', 'P', 'a', 'r', 'a', 'm', 'e', 't',
    'e', 'r', 's', 'E', 'n', 't', 'r', 'y', 'R', '\021', 'd', 'y',
    'n', 'a', 'm', 'i', 'c', 'P', 'a', 'r', 'a', 'm', 'e', 't',
    'e', 'r', 's', '\032', 'D', '\n', '\026', 'D', 'y', 'n', 'a', 'm',
    'i', 'c', 'P', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r', 's',
    'E', 'n', 't', 'r', 'y', '\022', '\020', '\n', '\003', 'k', 'e', 'y',
    '\030', '\001', ' ', '\001', '(', '\t', 'R', '\003', 'k', 'e', 'y', '\022',
    '\024', '\n', '\005', 'v', 'a', 'l', 'u', 'e', '\030', '\002', ' ', '\001',
    '(', '\t', 'R', '\005', 'v', 'a', 'l', 'u', 'e', ':', '\002', '8',
    '\001', '\"', '\237', '\001', '\n', '\014', 'R', 'e', 's', 'o', 'u', 'r',
    'c', 'e', 'N', 'a', 'm', 'e', '\022', '\022', '\n', '\004', 'n', 'a',
    'm', 'e', '\030', '\001', ' ', '\001', '(', '\t', 'R', '\004', 'n', 'a',
    'm', 'e', '\022', '{', '\n', '\035', 'd', 'y', 'n', 'a', 'm', 'i',
    'c', '_', 'p', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r', '_',
    'c', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't', 's', '\030',
    '\002', ' ', '\001', '(', '\013', '2', '7', '.', 'e', 'n', 'v', 'o',
    'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'd', 'i',
    's', 'c', 'o', 'v', 'e', 'r', 'y', '.', 'v', '3', '.', 'D',
    'y', 'n', 'a', 'm', 'i', 'c', 'P', 'a', 'r', 'a', 'm', 'e',
    't', 'e', 'r', 'C', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n',
    't', 's', 'R', '\033', 'd', 'y', 'n', 'a', 'm', 'i', 'c', 'P',
    'a', 'r', 'a', 'm', 'e', 't', 'e', 'r', 'C', 'o', 'n', 's',
    't', 'r', 'a', 'i', 'n', 't', 's', '\"', '\225', '\001', '\n', '\r',
    'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'E', 'r', 'r', 'o',
    'r', '\022', 'M', '\n', '\r', 'r', 'e', 's', 'o', 'u', 'r', 'c',
    'e', '_', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001', '(', '\013',
    '2', '(', '.', 'e', 'n', 'v', 'o', 'y', '.', 's', 'e', 'r',
    'v', 'i', 'c', 'e', '.', 'd', 'i', 's', 'c', 'o', 'v', 'e',
    'r', 'y', '.', 'v', '3', '.', 'R', 'e', 's', 'o', 'u', 'r',
    'c', 'e', 'N', 'a', 'm', 'e', 'R', '\014', 'r', 'e', 's', 'o',
    'u', 'r', 'c', 'e', 'N', 'a', 'm', 'e', '\022', '5', '\n', '\014',
    'e', 'r', 'r', 'o', 'r', '_', 'd', 'e', 't', 'a', 'i', 'l',
    '\030', '\002', ' ', '\001', '(', '\013', '2', '\022', '.', 'g', 'o', 'o',
    'g', 'l', 'e', '.', 'r', 'p', 'c', '.', 'S', 't', 'a', 't',
    'u', 's', 'R', '\013', 'e', 'r', 'r', 'o', 'r', 'D', 'e', 't',
    'a', 'i', 'l', '\"', '\205', '\003', '\n', '\020', 'D', 'i', 's', 'c',
    'o', 'v', 'e', 'r', 'y', 'R', 'e', 'q', 'u', 'e', 's', 't',
    '\022', '!', '\n', '\014', 'v', 'e', 'r', 's', 'i', 'o', 'n', '_',
    'i', 'n', 'f', 'o', '\030', '\001', ' ', '\001', '(', '\t', 'R', '\013',
    'v', 'e', 'r', 's', 'i', 'o', 'n', 'I', 'n', 'f', 'o', '\022',
    '.', '\n', '\004', 'n', 'o', 'd', 'e', '\030', '\002', ' ', '\001', '(',
    '\013', '2', '\032', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o',
    'n', 'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3',
    '.', 'N', 'o', 'd', 'e', 'R', '\004', 'n', 'o', 'd', 'e', '\022',
    '%', '\n', '\016', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_',
    'n', 'a', 'm', 'e', 's', '\030', '\003', ' ', '\003', '(', '\t', 'R',
    '\r', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'N', 'a', 'm',
    'e', 's', '\022', 'X', '\n', '\021', 'r', 'e', 's', 'o', 'u', 'r',
    'c', 'e', '_', 'l', 'o', 'c', 'a', 't', 'o', 'r', 's', '\030',
    '\007', ' ', '\003', '(', '\013', '2', '+', '.', 'e', 'n', 'v', 'o',
    'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'd', 'i',
    's', 'c', 'o', 'v', 'e', 'r', 'y', '.', 'v', '3', '.', 'R',
    'e', 's', 'o', 'u', 'r', 'c', 'e', 'L', 'o', 'c', 'a', 't',
    'o', 'r', 'R', '\020', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e',
    'L', 'o', 'c', 'a', 't', 'o', 'r', 's', '\022', '\031', '\n', '\010',
    't', 'y', 'p', 'e', '_', 'u', 'r', 'l', '\030', '\004', ' ', '\001',
    '(', '\t', 'R', '\007', 't', 'y', 'p', 'e', 'U', 'r', 'l', '\022',
    '%', '\n', '\016', 'r', 'e', 's', 'p', 'o', 'n', 's', 'e', '_',
    'n', 'o', 'n', 'c', 'e', '\030', '\005', ' ', '\001', '(', '\t', 'R',
    '\r', 'r', 'e', 's', 'p', 'o', 'n', 's', 'e', 'N', 'o', 'n',
    'c', 'e', '\022', '5', '\n', '\014', 'e', 'r', 'r', 'o', 'r', '_',
    'd', 'e', 't', 'a', 'i', 'l', '\030', '\006', ' ', '\001', '(', '\013',
    '2', '\022', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'r', 'p',
    'c', '.', 'S', 't', 'a', 't', 'u', 's', 'R', '\013', 'e', 'r',
    'r', 'o', 'r', 'D', 'e', 't', 'a', 'i', 'l', ':', '$', '\232',
    '\305', '\210', '\036', '\037', '\n', '\035', 'e', 'n', 'v', 'o', 'y', '.',
    'a', 'p', 'i', '.', 'v', '2', '.', 'D', 'i', 's', 'c', 'o',
    'v', 'e', 'r', 'y', 'R', 'e', 'q', 'u', 'e', 's', 't', '\"',
    '\367', '\002', '\n', '\021', 'D', 'i', 's', 'c', 'o', 'v', 'e', 'r',
    'y', 'R', 'e', 's', 'p', 'o', 'n', 's', 'e', '\022', '!', '\n',
    '\014', 'v', 'e', 'r', 's', 'i', 'o', 'n', '_', 'i', 'n', 'f',
    'o', '\030', '\001', ' ', '\001', '(', '\t', 'R', '\013', 'v', 'e', 'r',
    's', 'i', 'o', 'n', 'I', 'n', 'f', 'o', '\022', '2', '\n', '\t',
    'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', 's', '\030', '\002', ' ',
    '\003', '(', '\013', '2', '\024', '.', 'g', 'o', 'o', 'g', 'l', 'e',
    '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'A', 'n',
    'y', 'R', '\t', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', 's',
    '\022', '\026', '\n', '\006', 'c', 'a', 'n', 'a', 'r', 'y', '\030', '\003',
    ' ', '\001', '(', '\010', 'R', '\006', 'c', 'a', 'n', 'a', 'r', 'y',
    '\022', '\031', '\n', '\010', 't', 'y', 'p', 'e', '_', 'u', 'r', 'l',
    '\030', '\004', ' ', '\001', '(', '\t', 'R', '\007', 't', 'y', 'p', 'e',
    'U', 'r', 'l', '\022', '\024', '\n', '\005', 'n', 'o', 'n', 'c', 'e',
    '\030', '\005', ' ', '\001', '(', '\t', 'R', '\005', 'n', 'o', 'n', 'c',
    'e', '\022', 'G', '\n', '\r', 'c', 'o', 'n', 't', 'r', 'o', 'l',
    '_', 'p', 'l', 'a', 'n', 'e', '\030', '\006', ' ', '\001', '(', '\013',
    '2', '\"', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.',
    'C', 'o', 'n', 't', 'r', 'o', 'l', 'P', 'l', 'a', 'n', 'e',
    'R', '\014', 'c', 'o', 'n', 't', 'r', 'o', 'l', 'P', 'l', 'a',
    'n', 'e', '\022', 'R', '\n', '\017', 'r', 'e', 's', 'o', 'u', 'r',
    'c', 'e', '_', 'e', 'r', 'r', 'o', 'r', 's', '\030', '\007', ' ',
    '\003', '(', '\013', '2', ')', '.', 'e', 'n', 'v', 'o', 'y', '.',
    's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'd', 'i', 's', 'c',
    'o', 'v', 'e', 'r', 'y', '.', 'v', '3', '.', 'R', 'e', 's',
    'o', 'u', 'r', 'c', 'e', 'E', 'r', 'r', 'o', 'r', 'R', '\016',
    'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'E', 'r', 'r', 'o',
    'r', 's', ':', '%', '\232', '\305', '\210', '\036', ' ', '\n', '\036', 'e',
    'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.',
    'D', 'i', 's', 'c', 'o', 'v', 'e', 'r', 'y', 'R', 'e', 's',
    'p', 'o', 'n', 's', 'e', '\"', '\232', '\006', '\n', '\025', 'D', 'e',
    'l', 't', 'a', 'D', 'i', 's', 'c', 'o', 'v', 'e', 'r', 'y',
    'R', 'e', 'q', 'u', 'e', 's', 't', '\022', '.', '\n', '\004', 'n',
    'o', 'd', 'e', '\030', '\001', ' ', '\001', '(', '\013', '2', '\032', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g',
    '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'N', 'o', 'd',
    'e', 'R', '\004', 'n', 'o', 'd', 'e', '\022', '\031', '\n', '\010', 't',
    'y', 'p', 'e', '_', 'u', 'r', 'l', '\030', '\002', ' ', '\001', '(',
    '\t', 'R', '\007', 't', 'y', 'p', 'e', 'U', 'r', 'l', '\022', '8',
    '\n', '\030', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_', 'n',
    'a', 'm', 'e', 's', '_', 's', 'u', 'b', 's', 'c', 'r', 'i',
    'b', 'e', '\030', '\003', ' ', '\003', '(', '\t', 'R', '\026', 'r', 'e',
    's', 'o', 'u', 'r', 'c', 'e', 'N', 'a', 'm', 'e', 's', 'S',
    'u', 'b', 's', 'c', 'r', 'i', 'b', 'e', '\022', '<', '\n', '\032',
    'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_', 'n', 'a', 'm',
    'e', 's', '_', 'u', 'n', 's', 'u', 'b', 's', 'c', 'r', 'i',
    'b', 'e', '\030', '\004', ' ', '\003', '(', '\t', 'R', '\030', 'r', 'e',
    's', 'o', 'u', 'r', 'c', 'e', 'N', 'a', 'm', 'e', 's', 'U',
    'n', 's', 'u', 'b', 's', 'c', 'r', 'i', 'b', 'e', '\022', 'k',
    '\n', '\033', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_', 'l',
    'o', 'c', 'a', 't', 'o', 'r', 's', '_', 's', 'u', 'b', 's',
    'c', 'r', 'i', 'b', 'e', '\030', '\010', ' ', '\003', '(', '\013', '2',
    '+', '.', 'e', 'n', 'v', 'o', 'y', '.', 's', 'e', 'r', 'v',
    'i', 'c', 'e', '.', 'd', 'i', 's', 'c', 'o', 'v', 'e', 'r',
    'y', '.', 'v', '3', '.', 'R', 'e', 's', 'o', 'u', 'r', 'c',
    'e', 'L', 'o', 'c', 'a', 't', 'o', 'r', 'R', '\031', 'r', 'e',
    's', 'o', 'u', 'r', 'c', 'e', 'L', 'o', 'c', 'a', 't', 'o',
    'r', 's', 'S', 'u', 'b', 's', 'c', 'r', 'i', 'b', 'e', '\022',
    'o', '\n', '\035', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_',
    'l', 'o', 'c', 'a', 't', 'o', 'r', 's', '_', 'u', 'n', 's',
    'u', 'b', 's', 'c', 'r', 'i', 'b', 'e', '\030', '\t', ' ', '\003',
    '(', '\013', '2', '+', '.', 'e', 'n', 'v', 'o', 'y', '.', 's',
    'e', 'r', 'v', 'i', 'c', 'e', '.', 'd', 'i', 's', 'c', 'o',
    'v', 'e', 'r', 'y', '.', 'v', '3', '.', 'R', 'e', 's', 'o',
    'u', 'r', 'c', 'e', 'L', 'o', 'c', 'a', 't', 'o', 'r', 'R',
    '\033', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'L', 'o', 'c',
    'a', 't', 'o', 'r', 's', 'U', 'n', 's', 'u', 'b', 's', 'c',
    'r', 'i', 'b', 'e', '\022', '\212', '\001', '\n', '\031', 'i', 'n', 'i',
    't', 'i', 'a', 'l', '_', 'r', 'e', 's', 'o', 'u', 'r', 'c',
    'e', '_', 'v', 'e', 'r', 's', 'i', 'o', 'n', 's', '\030', '\005',
    ' ', '\003', '(', '\013', '2', 'N', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'd', 'i', 's',
    'c', 'o', 'v', 'e', 'r', 'y', '.', 'v', '3', '.', 'D', 'e',
    'l', 't', 'a', 'D', 'i', 's', 'c', 'o', 'v', 'e', 'r', 'y',
    'R', 'e', 'q', 'u', 'e', 's', 't', '.', 'I', 'n', 'i', 't',
    'i', 'a', 'l', 'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'V',
    'e', 'r', 's', 'i', 'o', 'n', 's', 'E', 'n', 't', 'r', 'y',
    'R', '\027', 'i', 'n', 'i', 't', 'i', 'a', 'l', 'R', 'e', 's',
    'o', 'u', 'r', 'c', 'e', 'V', 'e', 'r', 's', 'i', 'o', 'n',
    's', '\022', '%', '\n', '\016', 'r', 'e', 's', 'p', 'o', 'n', 's',
    'e', '_', 'n', 'o', 'n', 'c', 'e', '\030', '\006', ' ', '\001', '(',
    '\t', 'R', '\r', 'r', 'e', 's', 'p', 'o', 'n', 's', 'e', 'N',
    'o', 'n', 'c', 'e', '\022', '5', '\n', '\014', 'e', 'r', 'r', 'o',
    'r', '_', 'd', 'e', 't', 'a', 'i', 'l', '\030', '\007', ' ', '\001',
    '(', '\013', '2', '\022', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.',
    'r', 'p', 'c', '.', 'S', 't', 'a', 't', 'u', 's', 'R', '\013',
    'e', 'r', 'r', 'o', 'r', 'D', 'e', 't', 'a', 'i', 'l', '\032',
    'J', '\n', '\034', 'I', 'n', 'i', 't', 'i', 'a', 'l', 'R', 'e',
    's', 'o', 'u', 'r', 'c', 'e', 'V', 'e', 'r', 's', 'i', 'o',
    'n', 's', 'E', 'n', 't', 'r', 'y', '\022', '\020', '\n', '\003', 'k',
    'e', 'y', '\030', '\001', ' ', '\001', '(', '\t', 'R', '\003', 'k', 'e',
    'y', '\022', '\024', '\n', '\005', 'v', 'a', 'l', 'u', 'e', '\030', '\002',
    ' ', '\001', '(', '\t', 'R', '\005', 'v', 'a', 'l', 'u', 'e', ':',
    '\002', '8', '\001', ':', ')', '\232', '\305', '\210', '\036', '$', '\n', '\"',
    'e', 'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2',
    '.', 'D', 'e', 'l', 't', 'a', 'D', 'i', 's', 'c', 'o', 'v',
    'e', 'r', 'y', 'R', 'e', 'q', 'u', 'e', 's', 't', '\"', '\223',
    '\004', '\n', '\026', 'D', 'e', 'l', 't', 'a', 'D', 'i', 's', 'c',
    'o', 'v', 'e', 'r', 'y', 'R', 'e', 's', 'p', 'o', 'n', 's',
    'e', '\022', '.', '\n', '\023', 's', 'y', 's', 't', 'e', 'm', '_',
    'v', 'e', 'r', 's', 'i', 'o', 'n', '_', 'i', 'n', 'f', 'o',
    '\030', '\001', ' ', '\001', '(', '\t', 'R', '\021', 's', 'y', 's', 't',
    'e', 'm', 'V', 'e', 'r', 's', 'i', 'o', 'n', 'I', 'n', 'f',
    'o', '\022', 'B', '\n', '\t', 'r', 'e', 's', 'o', 'u', 'r', 'c',
    'e', 's', '\030', '\002', ' ', '\003', '(', '\013', '2', '$', '.', 'e',
    'n', 'v', 'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e',
    '.', 'd', 'i', 's', 'c', 'o', 'v', 'e', 'r', 'y', '.', 'v',
    '3', '.', 'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'R', '\t',
    'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', 's', '\022', '\031', '\n',
    '\010', 't', 'y', 'p', 'e', '_', 'u', 'r', 'l', '\030', '\004', ' ',
    '\001', '(', '\t', 'R', '\007', 't', 'y', 'p', 'e', 'U', 'r', 'l',
    '\022', '+', '\n', '\021', 'r', 'e', 'm', 'o', 'v', 'e', 'd', '_',
    'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', 's', '\030', '\006', ' ',
    '\003', '(', '\t', 'R', '\020', 'r', 'e', 'm', 'o', 'v', 'e', 'd',
    'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', 's', '\022', '^', '\n',
    '\026', 'r', 'e', 'm', 'o', 'v', 'e', 'd', '_', 'r', 'e', 's',
    'o', 'u', 'r', 'c', 'e', '_', 'n', 'a', 'm', 'e', 's', '\030',
    '\010', ' ', '\003', '(', '\013', '2', '(', '.', 'e', 'n', 'v', 'o',
    'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'd', 'i',
    's', 'c', 'o', 'v', 'e', 'r', 'y', '.', 'v', '3', '.', 'R',
    'e', 's', 'o', 'u', 'r', 'c', 'e', 'N', 'a', 'm', 'e', 'R',
    '\024', 'r', 'e', 'm', 'o', 'v', 'e', 'd', 'R', 'e', 's', 'o',
    'u', 'r', 'c', 'e', 'N', 'a', 'm', 'e', 's', '\022', '\024', '\n',
    '\005', 'n', 'o', 'n', 'c', 'e', '\030', '\005', ' ', '\001', '(', '\t',
    'R', '\005', 'n', 'o', 'n', 'c', 'e', '\022', 'G', '\n', '\r', 'c',
    'o', 'n', 't', 'r', 'o', 'l', '_', 'p', 'l', 'a', 'n', 'e',
    '\030', '\007', ' ', '\001', '(', '\013', '2', '\"', '.', 'e', 'n', 'v',
    'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o',
    'r', 'e', '.', 'v', '3', '.', 'C', 'o', 'n', 't', 'r', 'o',
    'l', 'P', 'l', 'a', 'n', 'e', 'R', '\014', 'c', 'o', 'n', 't',
    'r', 'o', 'l', 'P', 'l', 'a', 'n', 'e', '\022', 'R', '\n', '\017',
    'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_', 'e', 'r', 'r',
    'o', 'r', 's', '\030', '\t', ' ', '\003', '(', '\013', '2', ')', '.',
    'e', 'n', 'v', 'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c',
    'e', '.', 'd', 'i', 's', 'c', 'o', 'v', 'e', 'r', 'y', '.',
    'v', '3', '.', 'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'E',
    'r', 'r', 'o', 'r', 'R', '\016', 'r', 'e', 's', 'o', 'u', 'r',
    'c', 'e', 'E', 'r', 'r', 'o', 'r', 's', ':', '*', '\232', '\305',
    '\210', '\036', '%', '\n', '#', 'e', 'n', 'v', 'o', 'y', '.', 'a',
    'p', 'i', '.', 'v', '2', '.', 'D', 'e', 'l', 't', 'a', 'D',
    'i', 's', 'c', 'o', 'v', 'e', 'r', 'y', 'R', 'e', 's', 'p',
    'o', 'n', 's', 'e', '\"', '\222', '\006', '\n', '\033', 'D', 'y', 'n',
    'a', 'm', 'i', 'c', 'P', 'a', 'r', 'a', 'm', 'e', 't', 'e',
    'r', 'C', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't', 's',
    '\022', 'j', '\n', '\n', 'c', 'o', 'n', 's', 't', 'r', 'a', 'i',
    'n', 't', '\030', '\001', ' ', '\001', '(', '\013', '2', 'H', '.', 'e',
    'n', 'v', 'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e',
    '.', 'd', 'i', 's', 'c', 'o', 'v', 'e', 'r', 'y', '.', 'v',
    '3', '.', 'D', 'y', 'n', 'a', 'm', 'i', 'c', 'P', 'a', 'r',
    'a', 'm', 'e', 't', 'e', 'r', 'C', 'o', 'n', 's', 't', 'r',
    'a', 'i', 'n', 't', 's', '.', 'S', 'i', 'n', 'g', 'l', 'e',
    'C', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't', 'H', '\000',
    'R', '\n', 'c', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't',
    '\022', 'o', '\n', '\016', 'o', 'r', '_', 'c', 'o', 'n', 's', 't',
    'r', 'a', 'i', 'n', 't', 's', '\030', '\002', ' ', '\001', '(', '\013',
    '2', 'F', '.', 'e', 'n', 'v', 'o', 'y', '.', 's', 'e', 'r',
    'v', 'i', 'c', 'e', '.', 'd', 'i', 's', 'c', 'o', 'v', 'e',
    'r', 'y', '.', 'v', '3', '.', 'D', 'y', 'n', 'a', 'm', 'i',
    'c', 'P', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r', 'C', 'o',
    'n', 's', 't', 'r', 'a', 'i', 'n', 't', 's', '.', 'C', 'o',
    'n', 's', 't', 'r', 'a', 'i', 'n', 't', 'L', 'i', 's', 't',
    'H', '\000', 'R', '\r', 'o', 'r', 'C', 'o', 'n', 's', 't', 'r',
    'a', 'i', 'n', 't', 's', '\022', 'q', '\n', '\017', 'a', 'n', 'd',
    '_', 'c', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't', 's',
    '\030', '\003', ' ', '\001', '(', '\013', '2', 'F', '.', 'e', 'n', 'v',
    'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.', 'd',
    'i', 's', 'c', 'o', 'v', 'e', 'r', 'y', '.', 'v', '3', '.',
    'D', 'y', 'n', 'a', 'm', 'i', 'c', 'P', 'a', 'r', 'a', 'm',
    'e', 't', 'e', 'r', 'C', 'o', 'n', 's', 't', 'r', 'a', 'i',
    'n', 't', 's', '.', 'C', 'o', 'n', 's', 't', 'r', 'a', 'i',
    'n', 't', 'L', 'i', 's', 't', 'H', '\000', 'R', '\016', 'a', 'n',
    'd', 'C', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't', 's',
    '\022', 'b', '\n', '\017', 'n', 'o', 't', '_', 'c', 'o', 'n', 's',
    't', 'r', 'a', 'i', 'n', 't', 's', '\030', '\004', ' ', '\001', '(',
    '\013', '2', '7', '.', 'e', 'n', 'v', 'o', 'y', '.', 's', 'e',
    'r', 'v', 'i', 'c', 'e', '.', 'd', 'i', 's', 'c', 'o', 'v',
    'e', 'r', 'y', '.', 'v', '3', '.', 'D', 'y', 'n', 'a', 'm',
    'i', 'c', 'P', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r', 'C',
    'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't', 's', 'H', '\000',
    'R', '\016', 'n', 'o', 't', 'C', 'o', 'n', 's', 't', 'r', 'a',
    'i', 'n', 't', 's', '\032', '\311', '\001', '\n', '\020', 'S', 'i', 'n',
    'g', 'l', 'e', 'C', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n',
    't', '\022', '\020', '\n', '\003', 'k', 'e', 'y', '\030', '\001', ' ', '\001',
    '(', '\t', 'R', '\003', 'k', 'e', 'y', '\022', '\026', '\n', '\005', 'v',
    'a', 'l', 'u', 'e', '\030', '\002', ' ', '\001', '(', '\t', 'H', '\000',
    'R', '\005', 'v', 'a', 'l', 'u', 'e', '\022', 'i', '\n', '\006', 'e',
    'x', 'i', 's', 't', 's', '\030', '\003', ' ', '\001', '(', '\013', '2',
    'O', '.', 'e', 'n', 'v', 'o', 'y', '.', 's', 'e', 'r', 'v',
    'i', 'c', 'e', '.', 'd', 'i', 's', 'c', 'o', 'v', 'e', 'r',
    'y', '.', 'v', '3', '.', 'D', 'y', 'n', 'a', 'm', 'i', 'c',
    'P', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r', 'C', 'o', 'n',
    's', 't', 'r', 'a', 'i', 'n', 't', 's', '.', 'S', 'i', 'n',
    'g', 'l', 'e', 'C', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n',
    't', '.', 'E', 'x', 'i', 's', 't', 's', 'H', '\000', 'R', '\006',
    'e', 'x', 'i', 's', 't', 's', '\032', '\010', '\n', '\006', 'E', 'x',
    'i', 's', 't', 's', 'B', '\026', '\n', '\017', 'c', 'o', 'n', 's',
    't', 'r', 'a', 'i', 'n', 't', '_', 't', 'y', 'p', 'e', '\022',
    '\003', '\370', 'B', '\001', '\032', 'k', '\n', '\016', 'C', 'o', 'n', 's',
    't', 'r', 'a', 'i', 'n', 't', 'L', 'i', 's', 't', '\022', 'Y',
    '\n', '\013', 'c', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't',
    's', '\030', '\001', ' ', '\003', '(', '\013', '2', '7', '.', 'e', 'n',
    'v', 'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.',
    'd', 'i', 's', 'c', 'o', 'v', 'e', 'r', 'y', '.', 'v', '3',
    '.', 'D', 'y', 'n', 'a', 'm', 'i', 'c', 'P', 'a', 'r', 'a',
    'm', 'e', 't', 'e', 'r', 'C', 'o', 'n', 's', 't', 'r', 'a',
    'i', 'n', 't', 's', 'R', '\013', 'c', 'o', 'n', 's', 't', 'r',
    'a', 'i', 'n', 't', 's', 'B', '\006', '\n', '\004', 't', 'y', 'p',
    'e', '\"', '\344', '\003', '\n', '\010', 'R', 'e', 's', 'o', 'u', 'r',
    'c', 'e', '\022', '\022', '\n', '\004', 'n', 'a', 'm', 'e', '\030', '\003',
    ' ', '\001', '(', '\t', 'R', '\004', 'n', 'a', 'm', 'e', '\022', 'M',
    '\n', '\r', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '_', 'n',
    'a', 'm', 'e', '\030', '\010', ' ', '\001', '(', '\013', '2', '(', '.',
    'e', 'n', 'v', 'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c',
    'e', '.', 'd', 'i', 's', 'c', 'o', 'v', 'e', 'r', 'y', '.',
    'v', '3', '.', 'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'N',
    'a', 'm', 'e', 'R', '\014', 'r', 'e', 's', 'o', 'u', 'r', 'c',
    'e', 'N', 'a', 'm', 'e', '\022', '\030', '\n', '\007', 'a', 'l', 'i',
    'a', 's', 'e', 's', '\030', '\004', ' ', '\003', '(', '\t', 'R', '\007',
    'a', 'l', 'i', 'a', 's', 'e', 's', '\022', '\030', '\n', '\007', 'v',
    'e', 'r', 's', 'i', 'o', 'n', '\030', '\001', ' ', '\001', '(', '\t',
    'R', '\007', 'v', 'e', 'r', 's', 'i', 'o', 'n', '\022', '0', '\n',
    '\010', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '\030', '\002', ' ',
    '\001', '(', '\013', '2', '\024', '.', 'g', 'o', 'o', 'g', 'l', 'e',
    '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'A', 'n',
    'y', 'R', '\010', 'r', 'e', 's', 'o', 'u', 'r', 'c', 'e', '\022',
    '+', '\n', '\003', 't', 't', 'l', '\030', '\006', ' ', '\001', '(', '\013',
    '2', '\031', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r',
    'o', 't', 'o', 'b', 'u', 'f', '.', 'D', 'u', 'r', 'a', 't',
    'i', 'o', 'n', 'R', '\003', 't', 't', 'l', '\022', 'V', '\n', '\r',
    'c', 'a', 'c', 'h', 'e', '_', 'c', 'o', 'n', 't', 'r', 'o',
    'l', '\030', '\007', ' ', '\001', '(', '\013', '2', '1', '.', 'e', 'n',
    'v', 'o', 'y', '.', 's', 'e', 'r', 'v', 'i', 'c', 'e', '.',
    'd', 'i', 's', 'c', 'o', 'v', 'e', 'r', 'y', '.', 'v', '3',
    '.', 'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', '.', 'C', 'a',
    'c', 'h', 'e', 'C', 'o', 'n', 't', 'r', 'o', 'l', 'R', '\014',
    'c', 'a', 'c', 'h', 'e', 'C', 'o', 'n', 't', 'r', 'o', 'l',
    '\022', ':', '\n', '\010', 'm', 'e', 't', 'a', 'd', 'a', 't', 'a',
    '\030', '\t', ' ', '\001', '(', '\013', '2', '\036', '.', 'e', 'n', 'v',
    'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c', 'o',
    'r', 'e', '.', 'v', '3', '.', 'M', 'e', 't', 'a', 'd', 'a',
    't', 'a', 'R', '\010', 'm', 'e', 't', 'a', 'd', 'a', 't', 'a',
    '\032', '0', '\n', '\014', 'C', 'a', 'c', 'h', 'e', 'C', 'o', 'n',
    't', 'r', 'o', 'l', '\022', ' ', '\n', '\014', 'd', 'o', '_', 'n',
    'o', 't', '_', 'c', 'a', 'c', 'h', 'e', '\030', '\001', ' ', '\001',
    '(', '\010', 'R', '\n', 'd', 'o', 'N', 'o', 't', 'C', 'a', 'c',
    'h', 'e', ':', '\034', '\232', '\305', '\210', '\036', '\027', '\n', '\025', 'e',
    'n', 'v', 'o', 'y', '.', 'a', 'p', 'i', '.', 'v', '2', '.',
    'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', 'B', '\223', '\001', '\n',
    '(', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o',
    'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 's', 'e', 'r',
    'v', 'i', 'c', 'e', '.', 'd', 'i', 's', 'c', 'o', 'v', 'e',
    'r', 'y', '.', 'v', '3', 'B', '\016', 'D', 'i', 's', 'c', 'o',
    'v', 'e', 'r', 'y', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z',
    'M', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/',
    'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g',
    'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l',
    'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 's', 'e',
    'r', 'v', 'i', 'c', 'e', '/', 'd', 'i', 's', 'c', 'o', 'v',
    'e', 'r', 'y', '/', 'v', '3', ';', 'd', 'i', 's', 'c', 'o',
    'v', 'e', 'r', 'y', 'v', '3', '\272', '\200', '\310', '\321', '\006', '\002',
    '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[8] = {
    &envoy_config_core_v3_base_proto_upbdefinit,
    &google_protobuf_any_proto_upbdefinit,
    &google_protobuf_duration_proto_upbdefinit,
    &google_rpc_status_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_service_discovery_v3_discovery_proto_upbdefinit = {
    deps,
    &envoy_service_discovery_v3_discovery_proto_upb_file_layout,
    "envoy/service/discovery/v3/discovery.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
