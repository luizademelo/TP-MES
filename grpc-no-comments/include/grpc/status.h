
/*
 *
 * Copyright 2015 gRPC authors.
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

#ifndef GRPC_STATUS_H
#define GRPC_STATUS_H

#include <grpc/support/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {

  GRPC_STATUS_OK = 0,

  GRPC_STATUS_CANCELLED = 1,

  GRPC_STATUS_UNKNOWN = 2,

  GRPC_STATUS_INVALID_ARGUMENT = 3,

  GRPC_STATUS_DEADLINE_EXCEEDED = 4,

  GRPC_STATUS_NOT_FOUND = 5,

  GRPC_STATUS_ALREADY_EXISTS = 6,

  GRPC_STATUS_PERMISSION_DENIED = 7,

  GRPC_STATUS_UNAUTHENTICATED = 16,

  GRPC_STATUS_RESOURCE_EXHAUSTED = 8,

  GRPC_STATUS_FAILED_PRECONDITION = 9,

  GRPC_STATUS_ABORTED = 10,

  GRPC_STATUS_OUT_OF_RANGE = 11,

  GRPC_STATUS_UNIMPLEMENTED = 12,

  GRPC_STATUS_INTERNAL = 13,

  GRPC_STATUS_UNAVAILABLE = 14,

  GRPC_STATUS_DATA_LOSS = 15,

  GRPC_STATUS__DO_NOT_USE = 0x7fffffffu,
} grpc_status_code;

#ifdef __cplusplus
}
#endif

#endif
