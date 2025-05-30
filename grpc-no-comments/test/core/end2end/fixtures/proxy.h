
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_END2END_FIXTURES_PROXY_H
#define GRPC_TEST_CORE_END2END_FIXTURES_PROXY_H

#include <grpc/grpc.h>

typedef struct grpc_end2end_proxy grpc_end2end_proxy;

typedef struct grpc_end2end_proxy_def {
  grpc_server* (*create_server)(const char* port,
                                const grpc_channel_args* server_args);
  grpc_channel* (*create_client)(const char* target,
                                 const grpc_channel_args* client_args);
} grpc_end2end_proxy_def;

grpc_end2end_proxy* grpc_end2end_proxy_create(
    const grpc_end2end_proxy_def* def, const grpc_channel_args* client_args,
    const grpc_channel_args* server_args);
void grpc_end2end_proxy_destroy(grpc_end2end_proxy* proxy);

const char* grpc_end2end_proxy_get_client_target(grpc_end2end_proxy* proxy);
const char* grpc_end2end_proxy_get_server_port(grpc_end2end_proxy* proxy);

#endif
