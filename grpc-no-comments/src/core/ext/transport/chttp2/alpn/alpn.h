
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_ALPN_ALPN_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_ALPN_ALPN_H

#include <grpc/support/port_platform.h>
#include <string.h>

int grpc_chttp2_is_alpn_version_supported(const char* version, size_t size);

size_t grpc_chttp2_num_alpn_versions(void);

const char* grpc_chttp2_get_alpn_version_index(size_t i);

#endif
