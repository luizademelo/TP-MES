
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_HTTP_CLIENT_HTTPCLI_SSL_CREDENTIALS_H
#define GRPC_SRC_CORE_UTIL_HTTP_CLIENT_HTTPCLI_SSL_CREDENTIALS_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

RefCountedPtr<grpc_channel_credentials> CreateHttpRequestSSLCredentials();

}

#endif
