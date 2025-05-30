
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_COMPRESSION_COMPRESSION_INTERNAL_H
#define GRPC_SRC_CORE_LIB_COMPRESSION_COMPRESSION_INTERNAL_H

#include <grpc/impl/compression_types.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <initializer_list>
#include <optional>

#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/bitset.h"

namespace grpc_core {

std::optional<grpc_compression_algorithm> ParseCompressionAlgorithm(
    absl::string_view algorithm);

const char* CompressionAlgorithmAsString(grpc_compression_algorithm algorithm);

std::optional<grpc_compression_algorithm>
DefaultCompressionAlgorithmFromChannelArgs(const ChannelArgs& args);

class CompressionAlgorithmSet {
 public:

  static CompressionAlgorithmSet FromUint32(uint32_t value);

  static CompressionAlgorithmSet FromChannelArgs(const ChannelArgs& args);

  static CompressionAlgorithmSet FromString(absl::string_view str);

  CompressionAlgorithmSet();

  CompressionAlgorithmSet(
      std::initializer_list<grpc_compression_algorithm> algorithms);

  grpc_compression_algorithm CompressionAlgorithmForLevel(
      grpc_compression_level level) const;

  bool IsSet(grpc_compression_algorithm algorithm) const;

  void Set(grpc_compression_algorithm algorithm);

  absl::string_view ToString() const;
  Slice ToSlice() const;

  uint32_t ToLegacyBitmask() const;

  bool operator==(const CompressionAlgorithmSet& other) const {
    return set_ == other.set_;
  }

 private:
  BitSet<GRPC_COMPRESS_ALGORITHMS_COUNT> set_;
};

grpc_compression_options CompressionOptionsFromChannelArgs(
    const ChannelArgs& args);

}

#endif
