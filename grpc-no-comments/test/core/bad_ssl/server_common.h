
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_BAD_SSL_SERVER_COMMON_H
#define GRPC_TEST_CORE_BAD_SSL_SERVER_COMMON_H

#include <grpc/grpc.h>

const char* bad_ssl_addr(int argc, char** argv);
void bad_ssl_run(grpc_server* server);

#endif
