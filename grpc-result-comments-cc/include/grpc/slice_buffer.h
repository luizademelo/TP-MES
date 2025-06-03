Here's the commented version of the code:

```c++
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

/* Initialize a slice buffer */
GPRAPI void grpc_slice_buffer_init(grpc_slice_buffer* sb);

/* Destroy and deallocate a slice buffer */
GPRAPI void grpc_slice_buffer_destroy(grpc_slice_buffer* sb);

/* Add a single slice to the end of a slice buffer */
GPRAPI void grpc_slice_buffer_add(grpc_slice_buffer* sb, grpc_slice slice);

/* Add a single slice to the slice buffer and return its index */
GPRAPI size_t grpc_slice_buffer_add_indexed(grpc_slice_buffer* sb,
                                            grpc_slice slice);

/* Add 'n' slices to the end of a slice buffer */
GPRAPI void grpc_slice_buffer_addn(grpc_slice_buffer* sb, grpc_slice* slices,
                                   size_t n);

/* Add a small amount of raw data (of length 'len') to the slice buffer.
   Returns a pointer to the beginning of the data for immediate writing. */
GPRAPI uint8_t* grpc_slice_buffer_tiny_add(grpc_slice_buffer* sb, size_t len);

/* Remove and unref the last slice in the buffer */
GPRAPI void grpc_slice_buffer_pop(grpc_slice_buffer* sb);

/* Reset the slice buffer, unref all slices */
GPRAPI void grpc_slice_buffer_reset_and_unref(grpc_slice_buffer* sb);

/* Swap the contents of two slice buffers */
GPRAPI void grpc_slice_buffer_swap(grpc_slice_buffer* a, grpc_slice_buffer* b);

/* Move all slices from src to dst, leaving src empty */
GPRAPI void grpc_slice_buffer_move_into(grpc_slice_buffer* src,
                                        grpc_slice_buffer* dst);

/* Remove the last 'n' bytes from the slice buffer, placing them in 'garbage' */
GPRAPI void grpc_slice_buffer_trim_end(grpc_slice_buffer* sb, size_t n,
                                       grpc_slice_buffer* garbage);

/* Move the first 'n' slices from src to dst */
GPRAPI void grpc_slice_buffer_move_first(grpc_slice_buffer* src, size_t n,
                                         grpc_slice_buffer* dst);

/* Move the first 'n' slices from src to dst without adding refcounts */
GPRAPI void grpc_slice_buffer_move_first_no_ref(grpc_slice_buffer* src,
                                                size_t n,
                                                grpc_slice_buffer* dst);

/* Copy the first 'n' bytes from src to dst buffer */
GPRAPI void grpc_slice_buffer_move_first_into_buffer(grpc_slice_buffer* src,
                                                     size_t n, void* dst);

/* Remove and return the first slice from the buffer (transferring ownership) */
GPRAPI grpc_slice grpc_slice_buffer_take_first(grpc_slice_buffer* sb);

/* Undo the effect of take_first, putting the slice back at the front */
GPRAPI void grpc_slice_buffer_undo_take_first(grpc_slice_buffer* sb,
                                              grpc_slice slice);

#ifdef __cplusplus
}
#endif

#endif
```

The comments added explain:
1. The purpose of each function
2. What parameters are used for
3. The ownership/refcounting behavior where relevant
4. The effect on the buffer contents
5. Return values where applicable

The comments are concise but provide enough information for a developer to understand what each function does without needing to examine the implementation. I've maintained the original formatting and structure while adding these explanations.