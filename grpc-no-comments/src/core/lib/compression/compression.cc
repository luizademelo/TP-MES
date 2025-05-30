
// Copyright 2015 gRPC authors.

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

int grpc_compression_algorithm_is_message(grpc_compression_algorithm) {
  return 1;
}

int grpc_compression_algorithm_is_stream(grpc_compression_algorithm) {
  return 0;
}

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

grpc_compression_algorithm grpc_compression_algorithm_for_level(
    grpc_compression_level level, uint32_t accepted_encodings) {
  return grpc_core::CompressionAlgorithmSet::FromUint32(accepted_encodings)
      .CompressionAlgorithmForLevel(level);
}

void grpc_compression_options_init(grpc_compression_options* opts) {
  memset(opts, 0, sizeof(*opts));

  opts->enabled_algorithms_bitset = (1u << GRPC_COMPRESS_ALGORITHMS_COUNT) - 1;
}

void grpc_compression_options_enable_algorithm(
    grpc_compression_options* opts, grpc_compression_algorithm algorithm) {
  grpc_core::SetBit(&opts->enabled_algorithms_bitset, algorithm);
}

void grpc_compression_options_disable_algorithm(
    grpc_compression_options* opts, grpc_compression_algorithm algorithm) {
  grpc_core::ClearBit(&opts->enabled_algorithms_bitset, algorithm);
}

int grpc_compression_options_is_algorithm_enabled(
    const grpc_compression_options* opts,
    grpc_compression_algorithm algorithm) {
  return grpc_core::CompressionAlgorithmSet::FromUint32(
             opts->enabled_algorithms_bitset)
      .IsSet(algorithm);
}
