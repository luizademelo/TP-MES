
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_UTIL_HTTP_CLIENT_HTTPCLI_TEST_UTIL_H
#define GRPC_TEST_CORE_UTIL_HTTP_CLIENT_HTTPCLI_TEST_UTIL_H

#include <grpc/support/port_platform.h>

#include "src/core/util/subprocess.h"

namespace grpc_core {
namespace testing {

struct HttpRequestTestServer {
  gpr_subprocess* server;
  int port;
};

HttpRequestTestServer StartHttpRequestTestServer(int argc, char** argv,
                                                 bool use_ssl);

}
}

#endif
