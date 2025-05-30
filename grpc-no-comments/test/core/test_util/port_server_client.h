
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_PORT_SERVER_CLIENT_H
#define GRPC_TEST_CORE_TEST_UTIL_PORT_SERVER_CLIENT_H

#include <memory>

int grpc_pick_port_using_server(void);
void grpc_free_port_using_server(int port);

#endif
