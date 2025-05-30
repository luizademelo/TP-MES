
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CORE_END2END_FIXTURES_HTTP_PROXY_FIXTURE_H
#define GRPC_TEST_CORE_END2END_FIXTURES_HTTP_PROXY_FIXTURE_H

#include <grpc/grpc.h>

#define GRPC_TEST_HTTP_PROXY_AUTH_CREDS "aladdin:opensesame"

#define GRPC_ARG_HTTP_PROXY_AUTH_CREDS "grpc.test.proxy_auth"

typedef struct grpc_end2end_http_proxy grpc_end2end_http_proxy;

grpc_end2end_http_proxy* grpc_end2end_http_proxy_create(
    const grpc_channel_args* args);

void grpc_end2end_http_proxy_destroy(grpc_end2end_http_proxy* proxy);

const char* grpc_end2end_http_proxy_get_proxy_name(
    grpc_end2end_http_proxy* proxy);

int grpc_end2end_http_proxy_get_proxy_port(grpc_end2end_http_proxy* proxy);
size_t grpc_end2end_http_proxy_num_connections(grpc_end2end_http_proxy* proxy);

#endif
