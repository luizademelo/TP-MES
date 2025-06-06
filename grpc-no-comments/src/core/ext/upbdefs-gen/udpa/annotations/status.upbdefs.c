
#include "upb/reflection/def.h"
#include "udpa/annotations/status.upbdefs.h"
#include "udpa/annotations/status.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_descriptor_proto_upbdefinit;

static const char descriptor[483] = {
    '\n', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a', 't', 'u',
    's', '.', 'p', 'r', 'o', 't', 'o', '\022', '\020', 'u', 'd', 'p',
    'a', '.', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n',
    's', '\032', ' ', 'g', 'o', 'o', 'g', 'l', 'e', '/', 'p', 'r',
    'o', 't', 'o', 'b', 'u', 'f', '/', 'd', 'e', 's', 'c', 'r',
    'i', 'p', 't', 'o', 'r', '.', 'p', 'r', 'o', 't', 'o', '\"',
    '\232', '\001', '\n', '\020', 'S', 't', 'a', 't', 'u', 's', 'A', 'n',
    'n', 'o', 't', 'a', 't', 'i', 'o', 'n', '\022', '(', '\n', '\020',
    'w', 'o', 'r', 'k', '_', 'i', 'n', '_', 'p', 'r', 'o', 'g',
    'r', 'e', 's', 's', '\030', '\001', ' ', '\001', '(', '\010', 'R', '\016',
    'w', 'o', 'r', 'k', 'I', 'n', 'P', 'r', 'o', 'g', 'r', 'e',
    's', 's', '\022', '\\', '\n', '\026', 'p', 'a', 'c', 'k', 'a', 'g',
    'e', '_', 'v', 'e', 'r', 's', 'i', 'o', 'n', '_', 's', 't',
    'a', 't', 'u', 's', '\030', '\002', ' ', '\001', '(', '\016', '2', '&',
    '.', 'u', 'd', 'p', 'a', '.', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '.', 'P', 'a', 'c', 'k', 'a', 'g',
    'e', 'V', 'e', 'r', 's', 'i', 'o', 'n', 'S', 't', 'a', 't',
    'u', 's', 'R', '\024', 'p', 'a', 'c', 'k', 'a', 'g', 'e', 'V',
    'e', 'r', 's', 'i', 'o', 'n', 'S', 't', 'a', 't', 'u', 's',
    '*', ']', '\n', '\024', 'P', 'a', 'c', 'k', 'a', 'g', 'e', 'V',
    'e', 'r', 's', 'i', 'o', 'n', 'S', 't', 'a', 't', 'u', 's',
    '\022', '\013', '\n', '\007', 'U', 'N', 'K', 'N', 'O', 'W', 'N', '\020',
    '\000', '\022', '\n', '\n', '\006', 'F', 'R', 'O', 'Z', 'E', 'N', '\020',
    '\001', '\022', '\n', '\n', '\006', 'A', 'C', 'T', 'I', 'V', 'E', '\020',
    '\002', '\022', ' ', '\n', '\034', 'N', 'E', 'X', 'T', '_', 'M', 'A',
    'J', 'O', 'R', '_', 'V', 'E', 'R', 'S', 'I', 'O', 'N', '_',
    'C', 'A', 'N', 'D', 'I', 'D', 'A', 'T', 'E', '\020', '\003', ':',
    'd', '\n', '\013', 'f', 'i', 'l', 'e', '_', 's', 't', 'a', 't',
    'u', 's', '\022', '\034', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'F', 'i', 'l',
    'e', 'O', 'p', 't', 'i', 'o', 'n', 's', '\030', '\207', '\200', '\231',
    'j', ' ', '\001', '(', '\013', '2', '\"', '.', 'u', 'd', 'p', 'a',
    '.', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '.', 'S', 't', 'a', 't', 'u', 's', 'A', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 'R', '\n', 'f', 'i', 'l', 'e', 'S',
    't', 'a', 't', 'u', 's', 'B', '$', 'Z', '\"', 'g', 'i', 't',
    'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'c', 'n', 'c', 'f',
    '/', 'x', 'd', 's', '/', 'g', 'o', '/', 'a', 'n', 'n', 'o',
    't', 'a', 't', 'i', 'o', 'n', 's', 'b', '\006', 'p', 'r', 'o',
    't', 'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &google_protobuf_descriptor_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init udpa_annotations_status_proto_upbdefinit = {
    deps,
    &udpa_annotations_status_proto_upb_file_layout,
    "udpa/annotations/status.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
