
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

#ifndef GRPC_COMPRESSION_H
#define GRPC_COMPRESSION_H

#include <grpc/impl/compression_types.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

GRPCAPI int grpc_compression_algorithm_is_message(
    grpc_compression_algorithm algorithm);

GRPCAPI int grpc_compression_algorithm_is_stream(
    grpc_compression_algorithm algorithm);

GRPCAPI int grpc_compression_algorithm_parse(
    grpc_slice name, grpc_compression_algorithm* algorithm);

GRPCAPI int grpc_compression_algorithm_name(
    grpc_compression_algorithm algorithm, const char** name);

GRPCAPI grpc_compression_algorithm grpc_compression_algorithm_for_level(
    grpc_compression_level level, uint32_t accepted_encodings);

GRPCAPI void grpc_compression_options_init(grpc_compression_options* opts);

GRPCAPI void grpc_compression_options_enable_algorithm(
    grpc_compression_options* opts, grpc_compression_algorithm algorithm);

GRPCAPI void grpc_compression_options_disable_algorithm(
    grpc_compression_options* opts, grpc_compression_algorithm algorithm);

GRPCAPI int grpc_compression_options_is_algorithm_enabled(
    const grpc_compression_options* opts, grpc_compression_algorithm algorithm);

#ifdef __cplusplus
}
#endif

#endif
