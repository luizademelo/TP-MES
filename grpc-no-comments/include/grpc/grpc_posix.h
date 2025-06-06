
/*
 *
 * Copyright 2016 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPC_GRPC_POSIX_H
#define GRPC_GRPC_POSIX_H

#include <grpc/grpc.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

GRPCAPI grpc_channel* grpc_channel_create_from_fd(
    const char* target, int fd, grpc_channel_credentials* creds,
    const grpc_channel_args* args);

GRPCAPI void grpc_server_add_channel_from_fd(grpc_server* server, int fd,
                                             grpc_server_credentials* creds);

#ifdef __cplusplus
}
#endif

#endif
