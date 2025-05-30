
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_HTTP_CLIENT_FORMAT_REQUEST_H
#define GRPC_SRC_CORE_UTIL_HTTP_CLIENT_FORMAT_REQUEST_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>

#include "src/core/util/http_client/parser.h"

grpc_slice grpc_httpcli_format_get_request(const grpc_http_request* request,
                                           const char* host, const char* path);
grpc_slice grpc_httpcli_format_post_request(const grpc_http_request* request,
                                            const char* host, const char* path);
grpc_slice grpc_httpcli_format_put_request(const grpc_http_request* request,
                                           const char* host, const char* path);
grpc_slice grpc_httpcli_format_connect_request(const grpc_http_request* request,
                                               const char* host,
                                               const char* path);

#endif
