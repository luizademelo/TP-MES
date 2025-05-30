
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

#ifndef GRPC_SLICE_BUFFER_H
#define GRPC_SLICE_BUFFER_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

GPRAPI void grpc_slice_buffer_init(grpc_slice_buffer* sb);

GPRAPI void grpc_slice_buffer_destroy(grpc_slice_buffer* sb);

GPRAPI void grpc_slice_buffer_add(grpc_slice_buffer* sb, grpc_slice slice);

GPRAPI size_t grpc_slice_buffer_add_indexed(grpc_slice_buffer* sb,
                                            grpc_slice slice);
GPRAPI void grpc_slice_buffer_addn(grpc_slice_buffer* sb, grpc_slice* slices,
                                   size_t n);

GPRAPI uint8_t* grpc_slice_buffer_tiny_add(grpc_slice_buffer* sb, size_t len);

GPRAPI void grpc_slice_buffer_pop(grpc_slice_buffer* sb);

GPRAPI void grpc_slice_buffer_reset_and_unref(grpc_slice_buffer* sb);

GPRAPI void grpc_slice_buffer_swap(grpc_slice_buffer* a, grpc_slice_buffer* b);

GPRAPI void grpc_slice_buffer_move_into(grpc_slice_buffer* src,
                                        grpc_slice_buffer* dst);

GPRAPI void grpc_slice_buffer_trim_end(grpc_slice_buffer* sb, size_t n,
                                       grpc_slice_buffer* garbage);

GPRAPI void grpc_slice_buffer_move_first(grpc_slice_buffer* src, size_t n,
                                         grpc_slice_buffer* dst);

GPRAPI void grpc_slice_buffer_move_first_no_ref(grpc_slice_buffer* src,
                                                size_t n,
                                                grpc_slice_buffer* dst);

GPRAPI void grpc_slice_buffer_move_first_into_buffer(grpc_slice_buffer* src,
                                                     size_t n, void* dst);

GPRAPI grpc_slice grpc_slice_buffer_take_first(grpc_slice_buffer* sb);

GPRAPI void grpc_slice_buffer_undo_take_first(grpc_slice_buffer* sb,
                                              grpc_slice slice);

#ifdef __cplusplus
}
#endif

#endif
