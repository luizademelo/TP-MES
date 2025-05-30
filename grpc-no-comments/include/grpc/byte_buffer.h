
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

#ifndef GRPC_BYTE_BUFFER_H
#define GRPC_BYTE_BUFFER_H

#include <grpc/impl/grpc_types.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

GRPCAPI grpc_byte_buffer* grpc_raw_byte_buffer_create(grpc_slice* slices,
                                                      size_t nslices);

GRPCAPI grpc_byte_buffer* grpc_raw_compressed_byte_buffer_create(
    grpc_slice* slices, size_t nslices, grpc_compression_algorithm compression);

GRPCAPI grpc_byte_buffer* grpc_byte_buffer_copy(grpc_byte_buffer* bb);

GRPCAPI size_t grpc_byte_buffer_length(grpc_byte_buffer* bb);

GRPCAPI void grpc_byte_buffer_destroy(grpc_byte_buffer* bb);

struct grpc_byte_buffer_reader;
typedef struct grpc_byte_buffer_reader grpc_byte_buffer_reader;

GRPCAPI int grpc_byte_buffer_reader_init(grpc_byte_buffer_reader* reader,
                                         grpc_byte_buffer* buffer);

GRPCAPI void grpc_byte_buffer_reader_destroy(grpc_byte_buffer_reader* reader);

GRPCAPI int grpc_byte_buffer_reader_next(grpc_byte_buffer_reader* reader,
                                         grpc_slice* slice);

GRPCAPI int grpc_byte_buffer_reader_peek(grpc_byte_buffer_reader* reader,
                                         grpc_slice** slice);

GRPCAPI grpc_slice
grpc_byte_buffer_reader_readall(grpc_byte_buffer_reader* reader);

GRPCAPI grpc_byte_buffer* grpc_raw_byte_buffer_from_reader(
    grpc_byte_buffer_reader* reader);

#ifdef __cplusplus
}
#endif

#endif
