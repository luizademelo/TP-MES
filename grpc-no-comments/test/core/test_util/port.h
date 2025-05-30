
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_PORT_H
#define GRPC_TEST_CORE_TEST_UTIL_PORT_H

typedef struct grpc_pick_port_functions {
  int (*pick_unused_port_or_die_fn)(void);
  void (*recycle_unused_port_fn)(int port);
} grpc_pick_port_functions;

int grpc_pick_unused_port_or_die(void);

void grpc_recycle_unused_port(int port);

grpc_pick_port_functions grpc_set_pick_port_functions(
    grpc_pick_port_functions functions);

#endif
