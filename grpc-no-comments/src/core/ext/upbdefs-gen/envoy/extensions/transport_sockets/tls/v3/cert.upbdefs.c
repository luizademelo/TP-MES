
#include "upb/reflection/def.h"
#include "envoy/extensions/transport_sockets/tls/v3/cert.upbdefs.h"
#include "envoy/extensions/transport_sockets/tls/v3/cert.upb_minitable.h"

extern _upb_DefPool_Init envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit;
extern _upb_DefPool_Init envoy_extensions_transport_sockets_tls_v3_secret_proto_upbdefinit;
extern _upb_DefPool_Init envoy_extensions_transport_sockets_tls_v3_tls_proto_upbdefinit;

static const char descriptor[437] = {
    '\n', '4', 'e', 'n', 'v', 'o', 'y', '/', 'e', 'x', 't', 'e',
    'n', 's', 'i', 'o', 'n', 's', '/', 't', 'r', 'a', 'n', 's',
    'p', 'o', 'r', 't', '_', 's', 'o', 'c', 'k', 'e', 't', 's',
    '/', 't', 'l', 's', '/', 'v', '3', '/', 'c', 'e', 'r', 't',
    '.', 'p', 'r', 'o', 't', 'o', '\022', ')', 'e', 'n', 'v', 'o',
    'y', '.', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 's',
    '.', 't', 'r', 'a', 'n', 's', 'p', 'o', 'r', 't', '_', 's',
    'o', 'c', 'k', 'e', 't', 's', '.', 't', 'l', 's', '.', 'v',
    '3', '\032', '6', 'e', 'n', 'v', 'o', 'y', '/', 'e', 'x', 't',
    'e', 'n', 's', 'i', 'o', 'n', 's', '/', 't', 'r', 'a', 'n',
    's', 'p', 'o', 'r', 't', '_', 's', 'o', 'c', 'k', 'e', 't',
    's', '/', 't', 'l', 's', '/', 'v', '3', '/', 'c', 'o', 'm',
    'm', 'o', 'n', '.', 'p', 'r', 'o', 't', 'o', '\032', '6', 'e',
    'n', 'v', 'o', 'y', '/', 'e', 'x', 't', 'e', 'n', 's', 'i',
    'o', 'n', 's', '/', 't', 'r', 'a', 'n', 's', 'p', 'o', 'r',
    't', '_', 's', 'o', 'c', 'k', 'e', 't', 's', '/', 't', 'l',
    's', '/', 'v', '3', '/', 's', 'e', 'c', 'r', 'e', 't', '.',
    'p', 'r', 'o', 't', 'o', '\032', '3', 'e', 'n', 'v', 'o', 'y',
    '/', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 's', '/',
    't', 'r', 'a', 'n', 's', 'p', 'o', 'r', 't', '_', 's', 'o',
    'c', 'k', 'e', 't', 's', '/', 't', 'l', 's', '/', 'v', '3',
    '/', 't', 'l', 's', '.', 'p', 'r', 'o', 't', 'o', 'B', '\236',
    '\001', '\n', '7', 'i', 'o', '.', 'e', 'n', 'v', 'o', 'y', 'p',
    'r', 'o', 'x', 'y', '.', 'e', 'n', 'v', 'o', 'y', '.', 'e',
    'x', 't', 'e', 'n', 's', 'i', 'o', 'n', 's', '.', 't', 'r',
    'a', 'n', 's', 'p', 'o', 'r', 't', '_', 's', 'o', 'c', 'k',
    'e', 't', 's', '.', 't', 'l', 's', '.', 'v', '3', 'B', '\t',
    'C', 'e', 'r', 't', 'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z',
    'V', 'g', 'i', 't', 'h', 'u', 'b', '.', 'c', 'o', 'm', '/',
    'e', 'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '/', 'g',
    'o', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', '-', 'p', 'l',
    'a', 'n', 'e', '/', 'e', 'n', 'v', 'o', 'y', '/', 'e', 'x',
    't', 'e', 'n', 's', 'i', 'o', 'n', 's', '/', 't', 'r', 'a',
    'n', 's', 'p', 'o', 'r', 't', '_', 's', 'o', 'c', 'k', 'e',
    't', 's', '/', 't', 'l', 's', '/', 'v', '3', ';', 't', 'l',
    's', 'v', '3', 'P', '\000', 'P', '\001', 'P', '\002', 'b', '\006', 'p',
    'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[4] = {
    &envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit,
    &envoy_extensions_transport_sockets_tls_v3_secret_proto_upbdefinit,
    &envoy_extensions_transport_sockets_tls_v3_tls_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_extensions_transport_sockets_tls_v3_cert_proto_upbdefinit = {
    deps,
    &envoy_extensions_transport_sockets_tls_v3_cert_proto_upb_file_layout,
    "envoy/extensions/transport_sockets/tls/v3/cert.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
