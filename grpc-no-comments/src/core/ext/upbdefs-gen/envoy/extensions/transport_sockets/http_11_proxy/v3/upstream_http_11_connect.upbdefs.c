
#include "upb/reflection/def.h"
#include "envoy/extensions/transport_sockets/http_11_proxy/v3/upstream_http_11_connect.upbdefs.h"
#include "envoy/extensions/transport_sockets/http_11_proxy/v3/upstream_http_11_connect.upb_minitable.h"

extern _upb_DefPool_Init envoy_config_core_v3_base_proto_upbdefinit;
extern _upb_DefPool_Init udpa_annotations_status_proto_upbdefinit;

static const char descriptor[539] = {
    '\n', 'R', 'e', 'n', 'v', 'o', 'y', '/', 'e', 'x', 't', 'e',
    'n', 's', 'i', 'o', 'n', 's', '/', 't', 'r', 'a', 'n', 's',
    'p', 'o', 'r', 't', '_', 's', 'o', 'c', 'k', 'e', 't', 's',
    '/', 'h', 't', 't', 'p', '_', '1', '1', '_', 'p', 'r', 'o',
    'x', 'y', '/', 'v', '3', '/', 'u', 'p', 's', 't', 'r', 'e',
    'a', 'm', '_', 'h', 't', 't', 'p', '_', '1', '1', '_', 'c',
    'o', 'n', 'n', 'e', 'c', 't', '.', 'p', 'r', 'o', 't', 'o',
    '\022', '3', 'e', 'n', 'v', 'o', 'y', '.', 'e', 'x', 't', 'e',
    'n', 's', 'i', 'o', 'n', 's', '.', 't', 'r', 'a', 'n', 's',
    'p', 'o', 'r', 't', '_', 's', 'o', 'c', 'k', 'e', 't', 's',
    '.', 'h', 't', 't', 'p', '_', '1', '1', '_', 'p', 'r', 'o',
    'x', 'y', '.', 'v', '3', '\032', '\037', 'e', 'n', 'v', 'o', 'y',
    '/', 'c', 'o', 'n', 'f', 'i', 'g', '/', 'c', 'o', 'r', 'e',
    '/', 'v', '3', '/', 'b', 'a', 's', 'e', '.', 'p', 'r', 'o',
    't', 'o', '\032', '\035', 'u', 'd', 'p', 'a', '/', 'a', 'n', 'n',
    'o', 't', 'a', 't', 'i', 'o', 'n', 's', '/', 's', 't', 'a',
    't', 'u', 's', '.', 'p', 'r', 'o', 't', 'o', '\"', 'p', '\n',
    '\034', 'H', 't', 't', 'p', '1', '1', 'P', 'r', 'o', 'x', 'y',
    'U', 'p', 's', 't', 'r', 'e', 'a', 'm', 'T', 'r', 'a', 'n',
    's', 'p', 'o', 'r', 't', '\022', 'P', '\n', '\020', 't', 'r', 'a',
    'n', 's', 'p', 'o', 'r', 't', '_', 's', 'o', 'c', 'k', 'e',
    't', '\030', '\001', ' ', '\001', '(', '\013', '2', '%', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'c', 'o', 'n', 'f', 'i', 'g', '.', 'c',
    'o', 'r', 'e', '.', 'v', '3', '.', 'T', 'r', 'a', 'n', 's',
    'p', 'o', 'r', 't', 'S', 'o', 'c', 'k', 'e', 't', 'R', '\017',
    't', 'r', 'a', 'n', 's', 'p', 'o', 'r', 't', 'S', 'o', 'c',
    'k', 'e', 't', 'B', '\325', '\001', '\n', 'A', 'i', 'o', '.', 'e',
    'n', 'v', 'o', 'y', 'p', 'r', 'o', 'x', 'y', '.', 'e', 'n',
    'v', 'o', 'y', '.', 'e', 'x', 't', 'e', 'n', 's', 'i', 'o',
    'n', 's', '.', 't', 'r', 'a', 'n', 's', 'p', 'o', 'r', 't',
    '_', 's', 'o', 'c', 'k', 'e', 't', 's', '.', 'h', 't', 't',
    'p', '_', '1', '1', '_', 'p', 'r', 'o', 'x', 'y', '.', 'v',
    '3', 'B', '\032', 'U', 'p', 's', 't', 'r', 'e', 'a', 'm', 'H',
    't', 't', 'p', '1', '1', 'C', 'o', 'n', 'n', 'e', 'c', 't',
    'P', 'r', 'o', 't', 'o', 'P', '\001', 'Z', 'j', 'g', 'i', 't',
    'h', 'u', 'b', '.', 'c', 'o', 'm', '/', 'e', 'n', 'v', 'o',
    'y', 'p', 'r', 'o', 'x', 'y', '/', 'g', 'o', '-', 'c', 'o',
    'n', 't', 'r', 'o', 'l', '-', 'p', 'l', 'a', 'n', 'e', '/',
    'e', 'n', 'v', 'o', 'y', '/', 'e', 'x', 't', 'e', 'n', 's',
    'i', 'o', 'n', 's', '/', 't', 'r', 'a', 'n', 's', 'p', 'o',
    'r', 't', '_', 's', 'o', 'c', 'k', 'e', 't', 's', '/', 'h',
    't', 't', 'p', '_', '1', '1', '_', 'p', 'r', 'o', 'x', 'y',
    '/', 'v', '3', ';', 'h', 't', 't', 'p', '_', '1', '1', '_',
    'p', 'r', 'o', 'x', 'y', 'v', '3', '\272', '\200', '\310', '\321', '\006',
    '\002', '\020', '\002', 'b', '\006', 'p', 'r', 'o', 't', 'o', '3',
};

static _upb_DefPool_Init *deps[3] = {
    &envoy_config_core_v3_base_proto_upbdefinit,
    &udpa_annotations_status_proto_upbdefinit,
    NULL,
};

_upb_DefPool_Init envoy_extensions_transport_sockets_http_11_proxy_v3_upstream_http_11_connect_proto_upbdefinit = {
    deps,
    &envoy_extensions_transport_sockets_http_11_proxy_v3_upstream_http_11_connect_proto_upb_file_layout,
    "envoy/extensions/transport_sockets/http_11_proxy/v3/upstream_http_11_connect.proto",
    UPB_STRINGVIEW_INIT(descriptor, sizeof(descriptor)),
};
