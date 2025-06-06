
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

#ifndef GRPC_IMPL_CONNECTIVITY_STATE_H
#define GRPC_IMPL_CONNECTIVITY_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {

  GRPC_CHANNEL_IDLE,

  GRPC_CHANNEL_CONNECTING,

  GRPC_CHANNEL_READY,

  GRPC_CHANNEL_TRANSIENT_FAILURE,

  GRPC_CHANNEL_SHUTDOWN
} grpc_connectivity_state;

#ifdef __cplusplus
}
#endif

#endif
