
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_TEST_TCP_SERVER_H
#define GRPC_TEST_CORE_TEST_UTIL_TEST_TCP_SERVER_H

#include <grpc/support/sync.h>

#include <vector>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/tcp_server.h"

struct test_tcp_server {
  grpc_tcp_server* tcp_server = nullptr;
  grpc_closure shutdown_complete;
  bool shutdown = false;

  gpr_mu* mu;
  std::vector<grpc_pollset*> pollset;
  grpc_tcp_server_cb on_connect;
  void* cb_data;
};

void test_tcp_server_init(test_tcp_server* server,
                          grpc_tcp_server_cb on_connect, void* user_data);
void test_tcp_server_start(test_tcp_server* server, int port);
void test_tcp_server_poll(test_tcp_server* server, int milliseconds);
void test_tcp_server_destroy(test_tcp_server* server);

#endif
