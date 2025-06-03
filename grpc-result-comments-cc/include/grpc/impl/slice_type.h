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

#ifndef GRPC_IMPL_SLICE_TYPE_H
#define GRPC_IMPL_SLICE_TYPE_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

// Forward declaration of grpc_slice structure
typedef struct grpc_slice grpc_slice;

// Extra size needed for inline slices to store additional metadata (typically a pointer)
#define GRPC_SLICE_INLINE_EXTRA_SIZE sizeof(void*)

// Total size of an inlined slice, accounting for:
// - size_t (length)
// - uint8_t* (pointer to bytes)
// - Extra space for inline metadata
#define GRPC_SLICE_INLINED_SIZE \
  (sizeof(size_t) + sizeof(uint8_t*) - 1 + GRPC_SLICE_INLINE_EXTRA_SIZE)

// Forward declaration of reference counter structure
struct grpc_slice_refcount;

// Main slice structure that can represent either:
// 1. A reference-counted slice (large data)
// 2. An inlined slice (small data)
struct grpc_slice {
  struct grpc_slice_refcount* refcount;  // Pointer to reference counter (NULL for inlined slices)
  union grpc_slice_data {               // Union of both slice types
    struct grpc_slice_refcounted {       // Reference-counted slice variant
      size_t length;                     // Length of the data
      uint8_t* bytes;                    // Pointer to the actual data
    } refcounted;
    struct grpc_slice_inlined {          // Inlined slice variant
      uint8_t length;                    // Length of the data (smaller size since it's inlined)
      uint8_t bytes[GRPC_SLICE_INLINED_SIZE];  // Inlined data storage
    } inlined;
  } data;
};

// Number of slices that can be stored inline in a slice buffer
#define GRPC_SLICE_BUFFER_INLINE_ELEMENTS 3

// Slice buffer structure that can store multiple slices
typedef struct grpc_slice_buffer {
  grpc_slice* base_slices;  // Pointer to the base of allocated slices (when not using inlined storage)
  grpc_slice* slices;       // Pointer to current slices (may point to inlined or allocated storage)
  size_t count;             // Number of slices currently in the buffer
  size_t capacity;          // Total capacity of the buffer
  size_t length;            // Total length of all slices in bytes
  grpc_slice inlined[GRPC_SLICE_BUFFER_INLINE_ELEMENTS];  // Inline storage for small buffers
} grpc_slice_buffer;

// Macro to get the start pointer of a slice's data
#define GRPC_SLICE_START_PTR(slice)                 \
  ((slice).refcount ? (slice).data.refcounted.bytes \
                    : (slice).data.inlined.bytes)

// Macro to get the length of a slice
#define GRPC_SLICE_LENGTH(slice)                     \
  ((slice).refcount ? (slice).data.refcounted.length \
                    : (slice).data.inlined.length)

// Macro to set the length of a slice (handles both refcounted and inlined cases)
#define GRPC_SLICE_SET_LENGTH(slice, newlen)                              \
  ((slice).refcount ? ((slice).data.refcounted.length = (size_t)(newlen)) \
                    : ((slice).data.inlined.length = (uint8_t)(newlen))

// Macro to get the end pointer of a slice's data
#define GRPC_SLICE_END_PTR(slice) \
  GRPC_SLICE_START_PTR(slice) + GRPC_SLICE_LENGTH(slice)

// Macro to check if a slice is empty
#define GRPC_SLICE_IS_EMPTY(slice) (GRPC_SLICE_LENGTH(slice) == 0)

#endif
```

The comments explain:
1. The purpose of each structure and field
2. The two different slice representations (reference-counted and inlined)
3. The slice buffer implementation and its inline optimization
4. The purpose of each macro and how it handles both slice types
5. The memory layout considerations for the inlined slice variant

The comments maintain the original license header and include guards while adding clear explanations of the implementation details.