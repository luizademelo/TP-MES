Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary headers for compression functionality and core utilities
#include <grpc/compression.h>
#include <grpc/impl/compression_types.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <string.h>

#include <optional>

#include "src/core/lib/compression/compression_internal.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/useful.h"

// Returns whether the given compression algorithm is for message compression.
// Currently hardcoded to return true (1) for all algorithms.
int grpc_compression_algorithm_is_message(grpc_compression_algorithm) {
  return 1;
}

// Returns whether the given compression algorithm is for stream compression.
// Currently hardcoded to return false (0) for all algorithms.
int grpc_compression_algorithm_is_stream(grpc_compression_algorithm) {
  return 0;
}

// Parses a compression algorithm from a slice name.
// Returns 1 and sets the algorithm if successful, 0 otherwise.
int grpc_compression_algorithm_parse(grpc_slice name,
                                     grpc_compression_algorithm* algorithm) {
  std::optional<grpc_compression_algorithm> alg =
      grpc_core::ParseCompressionAlgorithm(
          grpc_core::StringViewFromSlice(name));
  if (alg.has_value()) {
    *algorithm = alg.value();
    return 1;
  }
  return 0;
}

// Gets the name of a compression algorithm as a string.
// Returns 1 and sets the name if successful, 0 otherwise.
// Also logs the operation via GRPC_TRACE_LOG.
int grpc_compression_algorithm_name(grpc_compression_algorithm algorithm,
                                    const char** name) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_compression_algorithm_name(algorithm=" << (int)algorithm
      << ", name=" << name << ")";
  const char* result = grpc_core::CompressionAlgorithmAsString(algorithm);
  if (result != nullptr) {
    *name = result;
    return 1;
  }
  return 0;
}

// Determines the appropriate compression algorithm for a given compression level
// and set of accepted encodings.
grpc_compression_algorithm grpc_compression_algorithm_for_level(
    grpc_compression_level level, uint32_t accepted_encodings) {
  return grpc_core::CompressionAlgorithmSet::FromUint32(accepted_encodings)
      .CompressionAlgorithmForLevel(level);
}

// Initializes compression options with default values.
// Enables all compression algorithms by default (sets all bits in the bitset).
void grpc_compression_options_init(grpc_compression_options* opts) {
  memset(opts, 0, sizeof(*opts));
  opts->enabled_algorithms_bitset = (1u << GRPC_COMPRESS_ALGORITHMS_COUNT) - 1;
}

// Enables a specific compression algorithm in the options.
void grpc_compression_options_enable_algorithm(
    grpc_compression_options* opts, grpc_compression_algorithm algorithm) {
  grpc_core::SetBit(&opts->enabled_algorithms_bitset, algorithm);
}

// Disables a specific compression algorithm in the options.
void grpc_compression_options_disable_algorithm(
    grpc_compression_options* opts, grpc_compression_algorithm algorithm) {
  grpc_core::ClearBit(&opts->enabled_algorithms_bitset, algorithm);
}

// Checks if a specific compression algorithm is enabled in the options.
// Returns 1 if enabled, 0 otherwise.
int grpc_compression_options_is_algorithm_enabled(
    const grpc_compression_options* opts,
    grpc_compression_algorithm algorithm) {
  return grpc_core::CompressionAlgorithmSet::FromUint32(
             opts->enabled_algorithms_bitset)
      .IsSet(algorithm);
}
```

Key improvements in the comments:
1. Added clear descriptions of each function's purpose
2. Documented return values and their meanings
3. Explained the behavior of important operations
4. Noted where default values are being set
5. Clarified the purpose of bit manipulation operations
6. Added context for the trace logging
7. Maintained consistent comment style throughout

The comments now provide a comprehensive understanding of the compression-related functionality while maintaining readability.