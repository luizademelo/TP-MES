
// Copyright 2015-2016 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_RECONNECT_SERVER_H
#define GRPC_TEST_CORE_TEST_UTIL_RECONNECT_SERVER_H

#include <grpc/support/time.h>

#include <string>

#include "test/core/test_util/test_tcp_server.h"

typedef struct timestamp_list {
  gpr_timespec timestamp;
  struct timestamp_list* next;
} timestamp_list;

typedef struct reconnect_server {
  test_tcp_server tcp_server;
  timestamp_list* head;
  timestamp_list* tail;
  std::string* peer;
  int max_reconnect_backoff_ms;
} reconnect_server;

void reconnect_server_init(reconnect_server* server);
void reconnect_server_start(reconnect_server* server, int port);
void reconnect_server_poll(reconnect_server* server, int seconds);
void reconnect_server_destroy(reconnect_server* server);
void reconnect_server_clear_timestamps(reconnect_server* server);

#endif
