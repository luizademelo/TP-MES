Here's the commented version of the code:

```c++
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

#ifndef GRPC_IMPL_COMPRESSION_TYPES_H
#define GRPC_IMPL_COMPRESSION_TYPES_H

#include <grpc/support/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

// Metadata key for requesting specific compression algorithm from server
#define GRPC_COMPRESSION_REQUEST_ALGORITHM_MD_KEY \
  "grpc-internal-encoding-request"

// Metadata key for channel's default compression algorithm
#define GRPC_COMPRESSION_CHANNEL_DEFAULT_ALGORITHM \
  "grpc.default_compression_algorithm"

// Metadata key for channel's default compression level
#define GRPC_COMPRESSION_CHANNEL_DEFAULT_LEVEL "grpc.default_compression_level"

// Metadata key for enabled compression algorithms bitset
#define GRPC_COMPRESSION_CHANNEL_ENABLED_ALGORITHMS_BITSET \
  "grpc.compression_enabled_algorithms_bitset"

// Enum defining available compression algorithms
typedef enum {
  GRPC_COMPRESS_NONE = 0,  // No compression
  GRPC_COMPRESS_DEFLATE,   // DEFLATE compression
  GRPC_COMPRESS_GZIP,      // GZIP compression

  GRPC_COMPRESS_ALGORITHMS_COUNT  // Total count of available algorithms
} grpc_compression_algorithm;

// Enum defining available compression levels
typedef enum {
  GRPC_COMPRESS_LEVEL_NONE = 0,  // No compression
  GRPC_COMPRESS_LEVEL_LOW,       // Low compression level
  GRPC_COMPRESS_LEVEL_MED,       // Medium compression level
  GRPC_COMPRESS_LEVEL_HIGH,      // High compression level
  GRPC_COMPRESS_LEVEL_COUNT      // Total count of available levels
} grpc_compression_level;

// Structure containing compression configuration options
typedef struct grpc_compression_options {
  // Bitmask representing enabled compression algorithms
  // Each bit corresponds to an algorithm in grpc_compression_algorithm
  uint32_t enabled_algorithms_bitset;

  // Structure for default compression level configuration
  struct grpc_compression_options_default_level {
    int is_set;                   // Flag indicating if default level is set
    grpc_compression_level level; // The default compression level
  } default_level;

  // Structure for default compression algorithm configuration
  struct grpc_compression_options_default_algorithm {
    int is_set;                         // Flag indicating if default algorithm is set
    grpc_compression_algorithm algorithm; // The default compression algorithm
  } default_algorithm;
} grpc_compression_options;

#ifdef __cplusplus
}
#endif

#endif
```

The comments added:
1. Explained the purpose of each metadata key macro
2. Documented each enum value in both compression algorithm and level enums
3. Explained the structure members and their purposes in grpc_compression_options
4. Clarified the bitset usage for enabled algorithms
5. Added general descriptions for each major component

The comments maintain the original code structure while providing clear explanations of the functionality and purpose of each element.