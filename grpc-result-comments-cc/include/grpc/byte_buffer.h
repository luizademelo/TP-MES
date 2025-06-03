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

#ifndef GRPC_BYTE_BUFFER_H
#define GRPC_BYTE_BUFFER_H

#include <grpc/impl/grpc_types.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Creates a new byte buffer from an array of slices.
 * Parameters:
 *   slices - Array of grpc_slice objects containing the data
 *   nslices - Number of slices in the array
 * Returns: Newly allocated grpc_byte_buffer containing the slice data */
GRPCAPI grpc_byte_buffer* grpc_raw_byte_buffer_create(grpc_slice* slices,
                                                      size_t nslices);

/* Creates a new compressed byte buffer from an array of slices.
 * Parameters:
 *   slices - Array of grpc_slice objects containing the data
 *   nslices - Number of slices in the array
 *   compression - Compression algorithm used on the data
 * Returns: Newly allocated compressed grpc_byte_buffer */
GRPCAPI grpc_byte_buffer* grpc_raw_compressed_byte_buffer_create(
    grpc_slice* slices, size_t nslices, grpc_compression_algorithm compression);

/* Creates a deep copy of a byte buffer.
 * Parameters:
 *   bb - Byte buffer to copy
 * Returns: Newly allocated copy of the input byte buffer */
GRPCAPI grpc_byte_buffer* grpc_byte_buffer_copy(grpc_byte_buffer* bb);

/* Returns the total length of all data in the byte buffer.
 * Parameters:
 *   bb - Byte buffer to measure
 * Returns: Total size in bytes of all data in the buffer */
GRPCAPI size_t grpc_byte_buffer_length(grpc_byte_buffer* bb);

/* Destroys a byte buffer and releases its resources.
 * Parameters:
 *   bb - Byte buffer to destroy */
GRPCAPI void grpc_byte_buffer_destroy(grpc_byte_buffer* bb);

/* Opaque structure for reading data from a byte buffer sequentially */
struct grpc_byte_buffer_reader;
typedef struct grpc_byte_buffer_reader grpc_byte_buffer_reader;

/* Initializes a byte buffer reader for sequential reading.
 * Parameters:
 *   reader - Reader structure to initialize
 *   buffer - Byte buffer to read from
 * Returns: 1 on success, 0 on failure */
GRPCAPI int grpc_byte_buffer_reader_init(grpc_byte_buffer_reader* reader,
                                         grpc_byte_buffer* buffer);

/* Destroys a byte buffer reader and releases its resources.
 * Parameters:
 *   reader - Reader to destroy */
GRPCAPI void grpc_byte_buffer_reader_destroy(grpc_byte_buffer_reader* reader);

/* Reads the next slice from the byte buffer.
 * Parameters:
 *   reader - Initialized reader object
 *   slice - Output parameter for the next slice
 * Returns: 1 if a slice was read, 0 if no more slices are available */
GRPCAPI int grpc_byte_buffer_reader_next(grpc_byte_buffer_reader* reader,
                                         grpc_slice* slice);

/* Peeks at the next slice without consuming it.
 * Parameters:
 *   reader - Initialized reader object
 *   slice - Output parameter for the next slice pointer
 * Returns: 1 if a slice was available, 0 if no more slices are available */
GRPCAPI int grpc_byte_buffer_reader_peek(grpc_byte_buffer_reader* reader,
                                         grpc_slice** slice);

/* Reads all remaining data from the byte buffer as a single slice.
 * Parameters:
 *   reader - Initialized reader object
 * Returns: A new slice containing all remaining data */
GRPCAPI grpc_slice
grpc_byte_buffer_reader_readall(grpc_byte_buffer_reader* reader);

/* Creates a new byte buffer from the remaining data in a reader.
 * Parameters:
 *   reader - Initialized reader object
 * Returns: New byte buffer containing remaining data */
GRPCAPI grpc_byte_buffer* grpc_raw_byte_buffer_from_reader(
    grpc_byte_buffer_reader* reader);

#ifdef __cplusplus
}
#endif

#endif /* GRPC_BYTE_BUFFER_H */
```

The comments added explain:
1. The purpose of each function
2. The parameters and their meanings
3. The return values and their significance
4. The general behavior of each function
5. Any important notes about memory management or ownership

The comments maintain a consistent style and provide enough information for developers to understand how to use each function without needing to examine the implementation details.