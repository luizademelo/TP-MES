
#include "upb/reflection/def.h"
#include "envoy/type/v3/semantic_version.upbdefs.h"
#include "envoy/type/v3/semantic_version.upb_minitable.h"

extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_versioning_proto_upbdefinit;

static const char descriptor[398] = {
    '\n', '$', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'v', '3', '/', 's', 'e', 'm', 'a', 'n', 't', 'i', 'c',
    '_', 'v', 'e', 'r', 's', 'i', 'o', 'n', '.', 'p', 'r', 'o',
    't', 'o', '\022', '\r', 'e', 'n', 'v', 'o', 'y', '.', 't', 'y',
    'p', 'e', '.', 'v', '3', '\032', '\035', 'u', 'd', 'p', 'a', '/',
    'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/',
    's', 't', 'a', 't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o',
    '\032', '!', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 'v', 'e', 'r', 's', 'i',
    'o', 'n', 'i', 'n', 'g', '.', 'p', 'r', 'o', 't', 'o', '\"',
    '\220', '\001', '\n', '\017', 'S', 'e', 'm', 'a', 'n', 't', 'i', 'c',
    'V', 'e', 'r', 's', 'i', 'o', 'n', '\022', '!', '\n', '\014', 'm',
    'a', 'j', 'o', 'r', '_', 'n', 'u', 'm', 'b', 'e', 'r', '\030',
    '\001', ' ', '\001', '(', '\r', 'R', '\013', 'm', 'a', 'j', 'o', 'r',
    'N', 'u', 'm', 'b', 'e', 'r', '\022', '!', '\n', '\014', 'm', 'i',
    'n', 'o', 'r', '_', 'n', 'u', 'm', 'b', 'e', 'r', '\030', '\002',
    ' ', '\001', '(', '\r', 'R', '\013', 'm', 'i', 'n', 'o', 'r', 'N',
    'u', 'm', 'b', 'e', 'r', '\022', '\024', '\n', '\005', 'p', 'a', 't',
    'c', 'h', '\030', '\003', ' ', '\001', '(', '\r', 'R', '\005', 'p', 'a',
    't', 'c', 'h', ':', '!', '\232', '\305', '\210', '\036', '\034', '\n', '\032',
    'e', 'n', 'v', 'o', 'y', '.', 't', 'y', 'p', 'e', '.', 'S',
    'e', 'm', 'a', 'n', 't', 'i', 'c', 'V', 'e', 'r', 's', 'i',
    'o', 'n', 'B', 'z', '\n', '\033', 'i', 'o', '.', 'e', 'n', 'v',
    'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o',
    'y', '.', 't', 'y', 'p', 'e', '.', 'v', '3', 'B', '\024', 'S',
    'e', 'm', 'a', 'n', 't', 'i', 'c', 'V', 'e', 'r', 's', 'i',
    'o', 'n', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', ';', 'g',
    'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n',
    'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-',
    'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n',
    'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 't', 'y', 'p', 'e',
    '/', 'v', '3', ';', 't', 'y', 'p', 'e', 'v', '3', '\272', '\200',
    '\310', '\321', '\006', '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't',
    'o', '3',
};

static _upb_DefPool_Init *deps[3] = {
    &udpa_annotations_status_proto_upbdefinit,
    &udpa_annotations_versioning_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_type_v3_semantic_version_proto_upbdefinit = {
    deps,
    &envoy_type_v3_semantic_version_proto_upb_file_layout,
    "envoy/type/v3/semantic_version.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
