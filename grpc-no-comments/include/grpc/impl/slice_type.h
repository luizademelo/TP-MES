
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

#ifndef GRPC_IMPL_SLICE_TYPE_H
#define GRPC_IMPL_SLICE_TYPE_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

typedef struct grpc_slice grpc_slice;

#define GRPC_SLICE_INLINE_EXTRA_SIZE sizeof(void*)

#define GRPC_SLICE_INLINED_SIZE \
  (sizeof(size_t) + sizeof(uint8_t*) - 1 + GRPC_SLICE_INLINE_EXTRA_SIZE)

struct grpc_slice_refcount;

struct grpc_slice {
  struct grpc_slice_refcount* refcount;
  union grpc_slice_data {
    struct grpc_slice_refcounted {
      size_t length;
      uint8_t* bytes;
    } refcounted;
    struct grpc_slice_inlined {
      uint8_t length;
      uint8_t bytes[GRPC_SLICE_INLINED_SIZE];
    } inlined;
  } data;
};

#define GRPC_SLICE_BUFFER_INLINE_ELEMENTS 3

typedef struct grpc_slice_buffer {

  grpc_slice* base_slices;

  grpc_slice* slices;

  size_t count;

  size_t capacity;

  size_t length;

  grpc_slice inlined[GRPC_SLICE_BUFFER_INLINE_ELEMENTS];
} grpc_slice_buffer;

#define GRPC_SLICE_START_PTR(slice)                 \
  ((slice).refcount ? (slice).data.refcounted.bytes \
                    : (slice).data.inlined.bytes)
#define GRPC_SLICE_LENGTH(slice)                     \
  ((slice).refcount ? (slice).data.refcounted.length \
                    : (slice).data.inlined.length)
#define GRPC_SLICE_SET_LENGTH(slice, newlen)                              \
  ((slice).refcount ? ((slice).data.refcounted.length = (size_t)(newlen)) \
                    : ((slice).data.inlined.length = (uint8_t)(newlen)))
#define GRPC_SLICE_END_PTR(slice) \
  GRPC_SLICE_START_PTR(slice) + GRPC_SLICE_LENGTH(slice)
#define GRPC_SLICE_IS_EMPTY(slice) (GRPC_SLICE_LENGTH(slice) == 0)

#endif
