
#include "upb/reflection/def.h"
#include "envoy/config/metrics/v3/stats.upbdefs.h"
#include "envoy/config/metrics/v3/stats.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_address_proto_upbdefinit;
extern _upb_DefPool_Init envoy_type_matcher_v3_string_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_any_proto_upbdefinit;
extern _upb_DefPool_Init google_protobuf_wrappers_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;
extern _upb_DefPool_Init validate_validate_proto_upbdefinit;

static const char descriptor[2166] = {
    '\n', '#', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o', 'n', 'f',
    'i', 'g', '/', 'm', 'e', 't', 'r', 'i', 'c', 's', '/', 'v',
    '3', '/', 's', 't', 'a', 't', 's', '.', 'p', 'r', 'o', 't',
    'o', '\022', '\027', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'm', 'e', 't', 'r', 'i', 'c', 's', '.',
    'v', '3', '\032', '\"', 'e', 'n', 'v', 'o', 'y', '/', 'c', 'o',
    'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e', '/', 'v', '3',
    '/', 'a', 'd', 'd', 'r', 'e', 's', 's', '.', 'p', 'r', 'o',
    't', 'o', '\032', '\"', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y',
    'p', 'e', '/', 'm', 'a', 't', 'c', 'h', 'e', 'r', '/', 'v',
    '3', '/', 's', 't', 'r', 'i', 'n', 'g', '.', 'p', 'r', 'o',
    't', 'o', '\032', '\031', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p',
    'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'a', 'n', 'y', '.',
    'p', 'r', 'o', 't', 'o', '\032', '\036', 'g', 'o', 'o', 'g', 'l',
    'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/', 'w',
    'r', 'a', 'p', 'p', 'e', 'r', 's', '.', 'p', 'r', 'o', 't',
    'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o',
    't', 'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't',
    'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\032', '!', 'u', 'd',
    'p', 'a', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o',
    'n', 's', '/', 'v', 'e', 'r', 's', 'i', 'o', 'n', 'i', 'n',
    'g', '.', 'p', 'r', 'o', 't', 'o', '\032', '\027', 'v', 'a', 'l',
    'i', 'd', 'a', 't', 'e', '/', 'v', 'a', 'l', 'i', 'd', 'a',
    't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\"', '\241', '\001', '\n',
    '\t', 'S', 't', 'a', 't', 's', 'S', 'i', 'n', 'k', '\022', '\022',
    '\n', '\004', 'n', 'a', 'm', 'e', '\030', '\001', ' ', '\001', '(', '\t',
    'R', '\004', 'n', 'a', 'm', 'e', '\022', '9', '\n', '\014', 't', 'y',
    'p', 'e', 'd', '_', 'c', 'o', 'n', 'f', 'i', 'g', '\030', '\003',
    ' ', '\001', '(', '\013', '2', '\024', '.', 'g', 'o', 'o', 'g', 'l',
    'e', '.', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'A',
    'n', 'y', 'H', '\000', 'R', '\013', 't', 'y', 'p', 'e', 'd', 'C',
    'o', 'n', 'f', 'i', 'g', ':', '(', '\232', '\305', '\210', '\036', '#',
    '\n', '!', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 'm', 'e', 't', 'r', 'i', 'c', 's', '.', 'v',
    '2', '.', 'S', 't', 'a', 't', 's', 'S', 'i', 'n', 'k', 'B',
    '\r', '\n', '\013', 'c', 'o', 'n', 'f', 'i', 'g', '_', 't', 'y',
    'p', 'e', 'J', '\004', '\010', '\002', '\020', '\003', 'R', '\006', 'c', 'o',
    'n', 'f', 'i', 'g', '\"', '\206', '\003', '\n', '\013', 'S', 't', 'a',
    't', 's', 'C', 'o', 'n', 'f', 'i', 'g', '\022', 'D', '\n', '\n',
    's', 't', 'a', 't', 's', '_', 't', 'a', 'g', 's', '\030', '\001',
    ' ', '\003', '(', '\013', '2', '%', '.', 'e', 'n', 'v', 'o', 'y',
    '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'm', 'e', 't', 'r',
    'i', 'c', 's', '.', 'v', '3', '.', 'T', 'a', 'g', 'S', 'p',
    'e', 'c', 'i', 'f', 'i', 'e', 'r', 'R', '\t', 's', 't', 'a',
    't', 's', 'T', 'a', 'g', 's', '\022', 'K', '\n', '\024', 'u', 's',
    'e', '_', 'a', 'l', 'l', '_', 'd', 'e', 'f', 'a', 'u', 'l',
    't', '_', 't', 'a', 'g', 's', '\030', '\002', ' ', '\001', '(', '\013',
    '2', '\032', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r',
    'o', 't', 'o', 'b', 'u', 'f', '.', 'B', 'o', 'o', 'l', 'V',
    'a', 'l', 'u', 'e', 'R', '\021', 'u', 's', 'e', 'A', 'l', 'l',
    'D', 'e', 'f', 'a', 'u', 'l', 't', 'T', 'a', 'g', 's', '\022',
    'J', '\n', '\r', 's', 't', 'a', 't', 's', '_', 'm', 'a', 't',
    'c', 'h', 'e', 'r', '\030', '\003', ' ', '\001', '(', '\013', '2', '%',
    '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i',
    'g', '.', 'm', 'e', 't', 'r', 'i', 'c', 's', '.', 'v', '3',
    '.', 'S', 't', 'a', 't', 's', 'M', 'a', 't', 'c', 'h', 'e',
    'r', 'R', '\014', 's', 't', 'a', 't', 's', 'M', 'a', 't', 'c',
    'h', 'e', 'r', '\022', 'l', '\n', '\031', 'h', 'i', 's', 't', 'o',
    'g', 'r', 'a', 'm', '_', 'b', 'u', 'c', 'k', 'e', 't', '_',
    's', 'e', 't', 't', 'i', 'n', 'g', 's', '\030', '\004', ' ', '\003',
    '(', '\013', '2', '0', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'm', 'e', 't', 'r', 'i', 'c',
    's', '.', 'v', '3', '.', 'H', 'i', 's', 't', 'o', 'g', 'r',
    'a', 'm', 'B', 'u', 'c', 'k', 'e', 't', 'S', 'e', 't', 't',
    'i', 'n', 'g', 's', 'R', '\027', 'h', 'i', 's', 't', 'o', 'g',
    'r', 'a', 'm', 'B', 'u', 'c', 'k', 'e', 't', 'S', 'e', 't',
    't', 'i', 'n', 'g', 's', ':', '*', '\232', '\305', '\210', '\036', '%',
    '\n', '#', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f',
    'i', 'g', '.', 'm', 'e', 't', 'r', 'i', 'c', 's', '.', 'v',
    '2', '.', 'S', 't', 'a', 't', 's', 'C', 'o', 'n', 'f', 'i',
    'g', '\"', '\230', '\002', '\n', '\014', 'S', 't', 'a', 't', 's', 'M',
    'a', 't', 'c', 'h', 'e', 'r', '\022', '\037', '\n', '\n', 'r', 'e',
    'j', 'e', 'c', 't', '_', 'a', 'l', 'l', '\030', '\001', ' ', '\001',
    '(', '\010', 'H', '\000', 'R', '\t', 'r', 'e', 'j', 'e', 'c', 't',
    'A', 'l', 'l', '\022', 'Q', '\n', '\016', 'e', 'x', 'c', 'l', 'u',
    's', 'i', 'o', 'n', '_', 'l', 'i', 's', 't', '\030', '\002', ' ',
    '\001', '(', '\013', '2', '(', '.', 'e', 'n', 'v', 'o', 'y', '.',
    't', 'y', 'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r',
    '.', 'v', '3', '.', 'L', 'i', 's', 't', 'S', 't', 'r', 'i',
    'n', 'g', 'M', 'a', 't', 'c', 'h', 'e', 'r', 'H', '\000', 'R',
    '\r', 'e', 'x', 'c', 'l', 'u', 's', 'i', 'o', 'n', 'L', 'i',
    's', 't', '\022', 'Q', '\n', '\016', 'i', 'n', 'c', 'l', 'u', 's',
    'i', 'o', 'n', '_', 'l', 'i', 's', 't', '\030', '\003', ' ', '\001',
    '(', '\013', '2', '(', '.', 'e', 'n', 'v', 'o', 'y', '.', 't',
    'y', 'p', 'e', '.', 'm', 'a', 't', 'c', 'h', 'e', 'r', '.',
    'v', '3', '.', 'L', 'i', 's', 't', 'S', 't', 'r', 'i', 'n',
    'g', 'M', 'a', 't', 'c', 'h', 'e', 'r', 'H', '\000', 'R', '\r',
    'i', 'n', 'c', 'l', 'u', 's', 'i', 'o', 'n', 'L', 'i', 's',
    't', ':', '+', '\232', '\305', '\210', '\036', '&', '\n', '$', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'm',
    'e', 't', 'r', 'i', 'c', 's', '.', 'v', '2', '.', 'S', 't',
    'a', 't', 's', 'M', 'a', 't', 'c', 'h', 'e', 'r', 'B', '\024',
    '\n', '\r', 's', 't', 'a', 't', 's', '_', 'm', 'a', 't', 'c',
    'h', 'e', 'r', '\022', '\003', '\370', 'B', '\001', '\"', '\250', '\001', '\n',
    '\014', 'T', 'a', 'g', 'S', 'p', 'e', 'c', 'i', 'f', 'i', 'e',
    'r', '\022', '\031', '\n', '\010', 't', 'a', 'g', '_', 'n', 'a', 'm',
    'e', '\030', '\001', ' ', '\001', '(', '\t', 'R', '\007', 't', 'a', 'g',
    'N', 'a', 'm', 'e', '\022', ' ', '\n', '\005', 'r', 'e', 'g', 'e',
    'x', '\030', '\002', ' ', '\001', '(', '\t', 'B', '\010', '\372', 'B', '\005',
    'r', '\003', '(', '\200', '\010', 'H', '\000', 'R', '\005', 'r', 'e', 'g',
    'e', 'x', '\022', '!', '\n', '\013', 'f', 'i', 'x', 'e', 'd', '_',
    'v', 'a', 'l', 'u', 'e', '\030', '\003', ' ', '\001', '(', '\t', 'H',
    '\000', 'R', '\n', 'f', 'i', 'x', 'e', 'd', 'V', 'a', 'l', 'u',
    'e', ':', '+', '\232', '\305', '\210', '\036', '&', '\n', '$', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'm',
    'e', 't', 'r', 'i', 'c', 's', '.', 'v', '2', '.', 'T', 'a',
    'g', 'S', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'r', 'B', '\013',
    '\n', '\t', 't', 'a', 'g', '_', 'v', 'a', 'l', 'u', 'e', '\"',
    '\222', '\001', '\n', '\027', 'H', 'i', 's', 't', 'o', 'g', 'r', 'a',
    'm', 'B', 'u', 'c', 'k', 'e', 't', 'S', 'e', 't', 't', 'i',
    'n', 'g', 's', '\022', 'D', '\n', '\005', 'm', 'a', 't', 'c', 'h',
    '\030', '\001', ' ', '\001', '(', '\013', '2', '$', '.', 'e', 'n', 'v',
    'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'm', 'a', 't', 'c',
    'h', 'e', 'r', '.', 'v', '3', '.', 'S', 't', 'r', 'i', 'n',
    'g', 'M', 'a', 't', 'c', 'h', 'e', 'r', 'B', '\010', '\372', 'B',
    '\005', '\212', '\001', '\002', '\020', '\001', 'R', '\005', 'm', 'a', 't', 'c',
    'h', '\022', '1', '\n', '\007', 'b', 'u', 'c', 'k', 'e', 't', 's',
    '\030', '\002', ' ', '\003', '(', '\001', 'B', '\027', '\372', 'B', '\024', '\222',
    '\001', '\021', '\010', '\001', '\030', '\001', '\"', '\013', '\022', '\t', '!', '\000',
    '\000', '\000', '\000', '\000', '\000', '\000', '\000', 'R', '\007', 'b', 'u', 'c',
    'k', 'e', 't', 's', '\"', '\317', '\001', '\n', '\n', 'S', 't', 'a',
    't', 's', 'd', 'S', 'i', 'n', 'k', '\022', '9', '\n', '\007', 'a',
    'd', 'd', 'r', 'e', 's', 's', '\030', '\001', ' ', '\001', '(', '\013',
    '2', '\035', '.', 'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n',
    'f', 'i', 'g', '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.',
    'A', 'd', 'd', 'r', 'e', 's', 's', 'H', '\000', 'R', '\007', 'a',
    'd', 'd', 'r', 'e', 's', 's', '\022', '*', '\n', '\020', 't', 'c',
    'p', '_', 'c', 'l', 'u', 's', 't', 'e', 'r', '_', 'n', 'a',
    'm', 'e', '\030', '\002', ' ', '\001', '(', '\t', 'H', '\000', 'R', '\016',
    't', 'c', 'p', 'C', 'l', 'u', 's', 't', 'e', 'r', 'N', 'a',
    'm', 'e', '\022', '\026', '\n', '\006', 'p', 'r', 'e', 'f', 'i', 'x',
    '\030', '\003', ' ', '\001', '(', '\t', 'R', '\006', 'p', 'r', 'e', 'f',
    'i', 'x', ':', ')', '\232', '\305', '\210', '\036', '$', '\n', '\"', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'm', 'e', 't', 'r', 'i', 'c', 's', '.', 'v', '2', '.', 'S',
    't', 'a', 't', 's', 'd', 'S', 'i', 'n', 'k', 'B', '\027', '\n',
    '\020', 's', 't', 'a', 't', 's', 'd', '_', 's', 'p', 'e', 'c',
    'i', 'f', 'i', 'e', 'r', '\022', '\003', '\370', 'B', '\001', '\"', '\217',
    '\002', '\n', '\r', 'D', 'o', 'g', 'S', 't', 'a', 't', 's', 'd',
    'S', 'i', 'n', 'k', '\022', '9', '\n', '\007', 'a', 'd', 'd', 'r',
    'e', 's', 's', '\030', '\001', ' ', '\001', '(', '\013', '2', '\035', '.',
    'e', 'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g',
    '.', 'c', 'o', 'r', 'e', '.', 'v', '3', '.', 'A', 'd', 'd',
    'r', 'e', 's', 's', 'H', '\000', 'R', '\007', 'a', 'd', 'd', 'r',
    'e', 's', 's', '\022', '\026', '\n', '\006', 'p', 'r', 'e', 'f', 'i',
    'x', '\030', '\003', ' ', '\001', '(', '\t', 'R', '\006', 'p', 'r', 'e',
    'f', 'i', 'x', '\022', 'Z', '\n', '\026', 'm', 'a', 'x', '_', 'b',
    'y', 't', 'e', 's', '_', 'p', 'e', 'r', '_', 'd', 'a', 't',
    'a', 'g', 'r', 'a', 'm', '\030', '\004', ' ', '\001', '(', '\013', '2',
    '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o',
    't', 'o', 'b', 'u', 'f', '.', 'U', 'I', 'n', 't', '6', '4',
    'V', 'a', 'l', 'u', 'e', 'B', '\007', '\372', 'B', '\004', '2', '\002',
    ' ', '\000', 'R', '\023', 'm', 'a', 'x', 'B', 'y', 't', 'e', 's',
    'P', 'e', 'r', 'D', 'a', 't', 'a', 'g', 'r', 'a', 'm', ':',
    ',', '\232', '\305', '\210', '\036', '\'', '\n', '%', 'e', 'n', 'v', 'o',
    'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'm', 'e', 't',
    'r', 'i', 'c', 's', '.', 'v', '2', '.', 'D', 'o', 'g', 'S',
    't', 'a', 't', 's', 'd', 'S', 'i', 'n', 'k', 'B', '\033', '\n',
    '\024', 'd', 'o', 'g', '_', 's', 't', 'a', 't', 's', 'd', '_',
    's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'r', '\022', '\003', '\370',
    'B', '\001', 'J', '\004', '\010', '\002', '\020', '\003', '\"', 'Z', '\n', '\013',
    'H', 'y', 's', 't', 'r', 'i', 'x', 'S', 'i', 'n', 'k', '\022',
    '\037', '\n', '\013', 'n', 'u', 'm', '_', 'b', 'u', 'c', 'k', 'e',
    't', 's', '\030', '\001', ' ', '\001', '(', '\003', 'R', '\n', 'n', 'u',
    'm', 'B', 'u', 'c', 'k', 'e', 't', 's', ':', '*', '\232', '\305',
    '\210', '\036', '%', '\n', '#', 'e', 'n', 'v', 'o', 'y', '.', 'c',
    'o', 'n', 'f', 'i', 'g', '.', 'm', 'e', 't', 'r', 'i', 'c',
    's', '.', 'v', '2', '.', 'H', 'y', 's', 't', 'r', 'i', 'x',
    'S', 'i', 'n', 'k', 'B', '\207', '\001', '\n', '%', 'i', 'o', '.',
    'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e',
    'n', 'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.',
    'm', 'e', 't', 'r', 'i', 'c', 's', '.', 'v', '3', 'B', '\n',
    'S', 't', 'a', 't', 's', 'P', 'r', 'o', 't', 'o', 'P', '\001',
    'Z', 'H', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm',
    '/', 'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/',
    'g', 'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p',
    'l', 'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 'c',
    'o', 'n', 'f', 'i', 'g', '/', 'm', 'e', 't', 'r', 'i', 'c',
    's', '/', 'v', '3', ';', 'm', 'e', 't', 'r', 'i', 'c', 's',
    'v', '3', '\272', '\200', '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006',
    'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[8] = {
    &envoy_config_core_v3_address_proto_upbdefinit,
    &envoy_type_matcher_v3_string_proto_upbdefinit,
    &google_protobuf_any_proto_upbdefinit,
    &google_protobuf_wrappers_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    &validate_validate_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_config_metrics_v3_stats_proto_upbdefinit = {
    deps,
    &envoy_config_metrics_v3_stats_proto_upb_file_layout,
    "envoy/config/metrics/v3/stats.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
