
// Copyright 2015 gRPC authors.

#include "src/core/lib/compression/compression_internal.h"

#include <grpc/compression.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <string>

#include "absl/container/inlined_vector.h"
#include "absl/log/check.h"
#include "absl/strings/ascii.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/crash.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/ref_counted_string.h"

namespace grpc_core {

const char* CompressionAlgorithmAsString(grpc_compression_algorithm algorithm) {
  switch (algorithm) {
    case GRPC_COMPRESS_NONE:
      return "identity";
    case GRPC_COMPRESS_DEFLATE:
      return "deflate";
    case GRPC_COMPRESS_GZIP:
      return "gzip";
    case GRPC_COMPRESS_ALGORITHMS_COUNT:
    default:
      return nullptr;
  }
}

namespace {
class CommaSeparatedLists {
 public:
  CommaSeparatedLists() : lists_{}, text_buffer_{} {
    char* text_buffer = text_buffer_;
    auto add_char = [&text_buffer, this](char c) {
      if (text_buffer - text_buffer_ == kTextBufferSize) abort();
      *text_buffer++ = c;
    };
    for (size_t list = 0; list < kNumLists; ++list) {
      char* start = text_buffer;
      for (size_t algorithm = 0; algorithm < GRPC_COMPRESS_ALGORITHMS_COUNT;
           ++algorithm) {
        if ((list & (1 << algorithm)) == 0) continue;
        if (start != text_buffer) {
          add_char(',');
          add_char(' ');
        }
        const char* name = CompressionAlgorithmAsString(
            static_cast<grpc_compression_algorithm>(algorithm));
        for (const char* p = name; *p != '\0'; ++p) {
          add_char(*p);
        }
      }
      lists_[list] = absl::string_view(start, text_buffer - start);
    }
    if (text_buffer - text_buffer_ != kTextBufferSize) abort();
  }

  absl::string_view operator[](size_t list) const { return lists_[list]; }

 private:
  static constexpr size_t kNumLists = 1 << GRPC_COMPRESS_ALGORITHMS_COUNT;

  static constexpr size_t kTextBufferSize = 86;
  absl::string_view lists_[kNumLists];
  char text_buffer_[kTextBufferSize];
};

const CommaSeparatedLists kCommaSeparatedLists;
}

std::optional<grpc_compression_algorithm> ParseCompressionAlgorithm(
    absl::string_view algorithm) {
  if (algorithm == "identity") {
    return GRPC_COMPRESS_NONE;
  } else if (algorithm == "deflate") {
    return GRPC_COMPRESS_DEFLATE;
  } else if (algorithm == "gzip") {
    return GRPC_COMPRESS_GZIP;
  } else {
    return std::nullopt;
  }
}

grpc_compression_algorithm
CompressionAlgorithmSet::CompressionAlgorithmForLevel(
    grpc_compression_level level) const {
  if (level > GRPC_COMPRESS_LEVEL_HIGH) {
    Crash(absl::StrFormat("Unknown message compression level %d.",
                          static_cast<int>(level)));
  }

  if (level == GRPC_COMPRESS_LEVEL_NONE) {
    return GRPC_COMPRESS_NONE;
  }

  CHECK_GT(level, 0);

  absl::InlinedVector<grpc_compression_algorithm,
                      GRPC_COMPRESS_ALGORITHMS_COUNT>
      algos;
  for (auto algo : {GRPC_COMPRESS_GZIP, GRPC_COMPRESS_DEFLATE}) {
    if (set_.is_set(algo)) {
      algos.push_back(algo);
    }
  }

  if (algos.empty()) {
    return GRPC_COMPRESS_NONE;
  }

  switch (level) {
    case GRPC_COMPRESS_LEVEL_NONE:
      abort();
    case GRPC_COMPRESS_LEVEL_LOW:
      return algos[0];
    case GRPC_COMPRESS_LEVEL_MED:
      return algos[algos.size() / 2];
    case GRPC_COMPRESS_LEVEL_HIGH:
      return algos.back();
    default:
      abort();
  };
}

CompressionAlgorithmSet CompressionAlgorithmSet::FromUint32(uint32_t value) {
  CompressionAlgorithmSet set;
  for (size_t i = 0; i < GRPC_COMPRESS_ALGORITHMS_COUNT; i++) {
    if (value & (1u << i)) {
      set.set_.set(i);
    }
  }
  return set;
}

CompressionAlgorithmSet CompressionAlgorithmSet::FromChannelArgs(
    const ChannelArgs& args) {
  CompressionAlgorithmSet set;
  static const uint32_t kEverything =
      (1u << GRPC_COMPRESS_ALGORITHMS_COUNT) - 1;
  return CompressionAlgorithmSet::FromUint32(
      args.GetInt(GRPC_COMPRESSION_CHANNEL_ENABLED_ALGORITHMS_BITSET)
          .value_or(kEverything));
}

CompressionAlgorithmSet::CompressionAlgorithmSet() = default;

CompressionAlgorithmSet::CompressionAlgorithmSet(
    std::initializer_list<grpc_compression_algorithm> algorithms) {
  for (auto algorithm : algorithms) {
    Set(algorithm);
  }
}

bool CompressionAlgorithmSet::IsSet(
    grpc_compression_algorithm algorithm) const {
  size_t i = static_cast<size_t>(algorithm);
  if (i < GRPC_COMPRESS_ALGORITHMS_COUNT) {
    return set_.is_set(i);
  } else {
    return false;
  }
}

void CompressionAlgorithmSet::Set(grpc_compression_algorithm algorithm) {
  size_t i = static_cast<size_t>(algorithm);
  if (i < GRPC_COMPRESS_ALGORITHMS_COUNT) {
    set_.set(i);
  }
}

absl::string_view CompressionAlgorithmSet::ToString() const {
  return kCommaSeparatedLists[ToLegacyBitmask()];
}

Slice CompressionAlgorithmSet::ToSlice() const {
  return Slice::FromStaticString(ToString());
}

CompressionAlgorithmSet CompressionAlgorithmSet::FromString(
    absl::string_view str) {
  CompressionAlgorithmSet set{GRPC_COMPRESS_NONE};
  for (auto algorithm : absl::StrSplit(str, ',')) {
    auto parsed =
        ParseCompressionAlgorithm(absl::StripAsciiWhitespace(algorithm));
    if (parsed.has_value()) {
      set.Set(*parsed);
    }
  }
  return set;
}

uint32_t CompressionAlgorithmSet::ToLegacyBitmask() const {
  return set_.ToInt<uint32_t>();
}

std::optional<grpc_compression_algorithm>
DefaultCompressionAlgorithmFromChannelArgs(const ChannelArgs& args) {
  auto* value = args.Get(GRPC_COMPRESSION_CHANNEL_DEFAULT_ALGORITHM);
  if (value == nullptr) return std::nullopt;
  auto ival = value->GetIfInt();
  if (ival.has_value()) {
    return static_cast<grpc_compression_algorithm>(*ival);
  }
  auto sval = value->GetIfString();
  if (sval != nullptr) {
    return ParseCompressionAlgorithm(sval->as_string_view());
  }
  return std::nullopt;
}

grpc_compression_options CompressionOptionsFromChannelArgs(
    const ChannelArgs& args) {

  grpc_compression_options compression_options;
  grpc_compression_options_init(&compression_options);
  auto default_level = args.GetInt(GRPC_COMPRESSION_CHANNEL_DEFAULT_LEVEL);
  if (default_level.has_value()) {
    compression_options.default_level.is_set = true;
    compression_options.default_level.level =
        static_cast<grpc_compression_level>(
            Clamp(*default_level, static_cast<int>(GRPC_COMPRESS_LEVEL_NONE),
                  static_cast<int>(GRPC_COMPRESS_LEVEL_COUNT - 1)));
  }
  auto default_algorithm =
      args.GetInt(GRPC_COMPRESSION_CHANNEL_DEFAULT_ALGORITHM);
  if (default_algorithm.has_value()) {
    compression_options.default_algorithm.is_set = true;
    compression_options.default_algorithm.algorithm =
        Clamp(static_cast<grpc_compression_algorithm>(*default_algorithm),
              GRPC_COMPRESS_NONE,
              static_cast<grpc_compression_algorithm>(
                  GRPC_COMPRESS_ALGORITHMS_COUNT - 1));
  }
  auto enabled_algorithms_bitset =
      args.GetInt(GRPC_COMPRESSION_CHANNEL_ENABLED_ALGORITHMS_BITSET);
  if (enabled_algorithms_bitset.has_value()) {
    compression_options.enabled_algorithms_bitset =
        *enabled_algorithms_bitset | 1 ;
  }
  return compression_options;
}

}
