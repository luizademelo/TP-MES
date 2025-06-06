
#include "upb/reflection/def.h"
#include "xds/annotations/v3/migrate.upbdefs.h"
#include "xds/annotations/v3/migrate.upb_minitable.h"

extern _upb_DefPool_Init google_protobuf_descriptor_proto_upbdefinit;

static const char descriptor[914] = {
    '\n', ' ', 'x', 'd', 's', '/', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '/', 'v', '3', '/', 'm', 'i', 'g',
    'r', 'a', 't', 'e', '.', 'p', 'r', 'o', 't', 'o', '\022', '\022',
    'x', 'd', 's', '.', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 's', '.', 'v', '3', '\032', ' ', 'g', 'o', 'o', 'g',
    'l', 'e', '/', 'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '/',
    'd', 'e', 's', 'c', 'r', 'i', 'p', 't', 'o', 'r', '.', 'p',
    'r', 'o', 't', 'o', '\"', '+', '\n', '\021', 'M', 'i', 'g', 'r',
    'a', 't', 'e', 'A', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o',
    'n', '\022', '\026', '\n', '\006', 'r', 'e', 'n', 'a', 'm', 'e', '\030',
    '\001', ' ', '\001', '(', '\t', 'R', '\006', 'r', 'e', 'n', 'a', 'm',
    'e', '\"', 'Y', '\n', '\026', 'F', 'i', 'e', 'l', 'd', 'M', 'i',
    'g', 'r', 'a', 't', 'e', 'A', 'n', 'n', 'o', 't', 'a', 't',
    'i', 'o', 'n', '\022', '\026', '\n', '\006', 'r', 'e', 'n', 'a', 'm',
    'e', '\030', '\001', ' ', '\001', '(', '\t', 'R', '\006', 'r', 'e', 'n',
    'a', 'm', 'e', '\022', '\'', '\n', '\017', 'o', 'n', 'e', 'o', 'f',
    '_', 'p', 'r', 'o', 'm', 'o', 't', 'i', 'o', 'n', '\030', '\002',
    ' ', '\001', '(', '\t', 'R', '\016', 'o', 'n', 'e', 'o', 'f', 'P',
    'r', 'o', 'm', 'o', 't', 'i', 'o', 'n', '\"', '?', '\n', '\025',
    'F', 'i', 'l', 'e', 'M', 'i', 'g', 'r', 'a', 't', 'e', 'A',
    'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', '\022', '&', '\n',
    '\017', 'm', 'o', 'v', 'e', '_', 't', 'o', '_', 'p', 'a', 'c',
    'k', 'a', 'g', 'e', '\030', '\002', ' ', '\001', '(', '\t', 'R', '\r',
    'm', 'o', 'v', 'e', 'T', 'o', 'P', 'a', 'c', 'k', 'a', 'g',
    'e', ':', 'r', '\n', '\017', 'm', 'e', 's', 's', 'a', 'g', 'e',
    '_', 'm', 'i', 'g', 'r', 'a', 't', 'e', '\022', '\037', '.', 'g',
    'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b',
    'u', 'f', '.', 'M', 'e', 's', 's', 'a', 'g', 'e', 'O', 'p',
    't', 'i', 'o', 'n', 's', '\030', '\316', '\351', '\355', '5', ' ', '\001',
    '(', '\013', '2', '%', '.', 'x', 'd', 's', '.', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', '.', 'v', '3', '.',
    'M', 'i', 'g', 'r', 'a', 't', 'e', 'A', 'n', 'n', 'o', 't',
    'a', 't', 'i', 'o', 'n', 'R', '\016', 'm', 'e', 's', 's', 'a',
    'g', 'e', 'M', 'i', 'g', 'r', 'a', 't', 'e', ':', 'q', '\n',
    '\r', 'f', 'i', 'e', 'l', 'd', '_', 'm', 'i', 'g', 'r', 'a',
    't', 'e', '\022', '\035', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.',
    'p', 'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'F', 'i', 'e',
    'l', 'd', 'O', 'p', 't', 'i', 'o', 'n', 's', '\030', '\316', '\351',
    '\355', '5', ' ', '\001', '(', '\013', '2', '*', '.', 'x', 'd', 's',
    '.', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 's',
    '.', 'v', '3', '.', 'F', 'i', 'e', 'l', 'd', 'M', 'i', 'g',
    'r', 'a', 't', 'e', 'A', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 'R', '\014', 'f', 'i', 'e', 'l', 'd', 'M', 'i', 'g',
    'r', 'a', 't', 'e', ':', 'i', '\n', '\014', 'e', 'n', 'u', 'm',
    '_', 'm', 'i', 'g', 'r', 'a', 't', 'e', '\022', '\034', '.', 'g',
    'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't', 'o', 'b',
    'u', 'f', '.', 'E', 'n', 'u', 'm', 'O', 'p', 't', 'i', 'o',
    'n', 's', '\030', '\316', '\351', '\355', '5', ' ', '\001', '(', '\013', '2',
    '%', '.', 'x', 'd', 's', '.', 'a', 'n', 'n', 'o', 't', 'a',
    't', 'i', 'o', 'n', 's', '.', 'v', '3', '.', 'M', 'i', 'g',
    'r', 'a', 't', 'e', 'A', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 'R', '\013', 'e', 'n', 'u', 'm', 'M', 'i', 'g', 'r',
    'a', 't', 'e', ':', 'y', '\n', '\022', 'e', 'n', 'u', 'm', '_',
    'v', 'a', 'l', 'u', 'e', '_', 'm', 'i', 'g', 'r', 'a', 't',
    'e', '\022', '!', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p',
    'r', 'o', 't', 'o', 'b', 'u', 'f', '.', 'E', 'n', 'u', 'm',
    'V', 'a', 'l', 'u', 'e', 'O', 'p', 't', 'i', 'o', 'n', 's',
    '\030', '\316', '\351', '\355', '5', ' ', '\001', '(', '\013', '2', '%', '.',
    'x', 'd', 's', '.', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 's', '.', 'v', '3', '.', 'M', 'i', 'g', 'r', 'a',
    't', 'e', 'A', 'n', 'n', 'o', 't', 'a', 't', 'i', 'o', 'n',
    'R', '\020', 'e', 'n', 'u', 'm', 'V', 'a', 'l', 'u', 'e', 'M',
    'i', 'g', 'r', 'a', 't', 'e', ':', 'm', '\n', '\014', 'f', 'i',
    'l', 'e', '_', 'm', 'i', 'g', 'r', 'a', 't', 'e', '\022', '\034',
    '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'p', 'r', 'o', 't',
    'o', 'b', 'u', 'f', '.', 'F', 'i', 'l', 'e', 'O', 'p', 't',
    'i', 'o', 'n', 's', '\030', '\316', '\351', '\355', '5', ' ', '\001', '(',
    '\013', '2', ')', '.', 'x', 'd', 's', '.', 'a', 'n', 'n', 'o',
    't', 'a', 't', 'i', 'o', 'n', 's', '.', 'v', '3', '.', 'F',
    'i', 'l', 'e', 'M', 'i', 'g', 'r', 'a', 't', 'e', 'A', 'n',
    'n', 'o', 't', 'a', 't', 'i', 'o', 'n', 'R', '\013', 'f', 'i',
    'l', 'e', 'M', 'i', 'g', 'r', 'a', 't', 'e', 'B', '+', 'Z',
    ')', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/',
    'c', 'n', 'c', 'f', '/', 'x', 'd', 's', '/', 'g', 'o', '/',
    'x', 'd', 's', '/', 'a', 'n', 'n', 'o', 't', 'a', 't', 'i',
    'o', 'n', 's', '/', 'v', '3', 'b', '\006', 'p', 'r', 'o', 't',
    'o', '3',
};

static _upb_DefPool_Init *deps[2] = {
    &google_protobuf_descriptor_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init xds_annotations_v3_migrate_proto_upbdefinit = {
    deps,
    &xds_annotations_v3_migrate_proto_upb_file_layout,
    "xds/annotations/v3/migrate.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
