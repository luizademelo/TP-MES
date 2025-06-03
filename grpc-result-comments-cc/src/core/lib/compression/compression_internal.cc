Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for compression functionality
#include "src/core/lib/compression/compression_internal.h"
#include <grpc/compression.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>
#include <string>

// Includes from Abseil library for utility functions
#include "absl/container/inlined_vector.h"
#include "absl/log/check.h"
#include "absl/strings/ascii.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"

// Includes from gRPC core library
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/crash.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/ref_counted_string.h"

namespace grpc_core {

// Converts a compression algorithm enum value to its string representation
const char* CompressionAlgorithmAsString(grpc_compression_algorithm algorithm) {
  switch (algorithm) {
    case GRPC_COMPRESS_NONE:
      return "identity";  // No compression
    case GRPC_COMPRESS_DEFLATE:
      return "deflate";   // DEFLATE compression
    case GRPC_COMPRESS_GZIP:
      return "gzip";      // GZIP compression
    case GRPC_COMPRESS_ALGORITHMS_COUNT:
    default:
      return nullptr;     // Invalid algorithm
  }
}

namespace {
// Helper class for managing comma-separated lists of compression algorithms
class CommaSeparatedLists {
 public:
  // Constructor builds all possible combinations of compression algorithms
  CommaSeparatedLists() : lists_{}, text_buffer_{} {
    char* text_buffer = text_buffer_;
    // Lambda to safely add characters to the buffer
    auto add_char = [&text_buffer, this](char c) {
      if (text_buffer - text_buffer_ == kTextBufferSize) abort();
      *text_buffer++ = c;
    };
    
    // Generate all possible combinations of algorithms
    for (size_t list = 0; list < kNumLists; ++list) {
      char* start = text_buffer;
      for (size_t algorithm = 0; algorithm < GRPC_COMPRESS_ALGORITHMS_COUNT;
           ++algorithm) {
        if ((list & (1 << algorithm)) == 0) continue;
        if (start != text_buffer) {
          add_char(',');  // Add comma separator
          add_char(' ');
        }
        // Get algorithm name and add to buffer
        const char* name = CompressionAlgorithmAsString(
            static_cast<grpc_compression_algorithm>(algorithm));
        for (const char* p = name; *p != '\0'; ++p) {
          add_char(*p);
        }
      }
      // Store the generated string view
      lists_[list] = absl::string_view(start, text_buffer - start);
    }
    if (text_buffer - text_buffer_ != kTextBufferSize) abort();
  }

  // Accessor for getting a specific algorithm combination
  absl::string_view operator[](size_t list) const { return lists_[list]; }

 private:
  static constexpr size_t kNumLists = 1 << GRPC_COMPRESS_ALGORITHMS_COUNT;
  static constexpr size_t kTextBufferSize = 86;
  absl::string_view lists_[kNumLists];  // Storage for all combinations
  char text_buffer_[kTextBufferSize];   // Buffer for string data
};

// Global instance of comma-separated lists
const CommaSeparatedLists kCommaSeparatedLists;
}

// Parses a string to determine the compression algorithm
std::optional<grpc_compression_algorithm> ParseCompressionAlgorithm(
    absl::string_view algorithm) {
  if (algorithm == "identity") {
    return GRPC_COMPRESS_NONE;
  } else if (algorithm == "deflate") {
    return GRPC_COMPRESS_DEFLATE;
  } else if (algorithm == "gzip") {
    return GRPC_COMPRESS_GZIP;
  } else {
    return std::nullopt;  // Unknown algorithm
  }
}

// Selects the appropriate compression algorithm based on compression level
grpc_compression_algorithm
CompressionAlgorithmSet::CompressionAlgorithmForLevel(
    grpc_compression_level level) const {
  // Validate input level
  if (level > GRPC_COMPRESS_LEVEL_HIGH) {
    Crash(absl::StrFormat("Unknown message compression level %d.",
                          static_cast<int>(level)));
  }

  // No compression requested
  if (level == GRPC_COMPRESS_LEVEL_NONE) {
    return GRPC_COMPRESS_NONE;
  }

  CHECK_GT(level, 0);

  // Collect available algorithms
  absl::InlinedVector<grpc_compression_algorithm,
                      GRPC_COMPRESS_ALGORITHMS_COUNT>
      algos;
  for (auto algo : {GRPC_COMPRESS_GZIP, GRPC_COMPRESS_DEFLATE}) {
    if (set_.is_set(algo)) {
      algos.push_back(algo);
    }
  }

  // Fallback if no algorithms available
  if (algos.empty()) {
    return GRPC_COMPRESS_NONE;
  }

  // Select algorithm based on level
  switch (level) {
    case GRPC_COMPRESS_LEVEL_NONE:
      abort();  // Shouldn't reach here
    case GRPC_COMPRESS_LEVEL_LOW:
      return algos[0];  // First available algorithm
    case GRPC_COMPRESS_LEVEL_MED:
      return algos[algos.size() / 2];  // Middle algorithm
    case GRPC_COMPRESS_LEVEL_HIGH:
      return algos.back();  // Last algorithm
    default:
      abort();
  };
}

// Creates a CompressionAlgorithmSet from a bitmask
CompressionAlgorithmSet CompressionAlgorithmSet::FromUint32(uint32_t value) {
  CompressionAlgorithmSet set;
  // Check each bit in the value
  for (size_t i = 0; i < GRPC_COMPRESS_ALGORITHMS_COUNT; i++) {
    if (value & (1u << i)) {
      set.set_.set(i);  // Enable algorithm if bit is set
    }
  }
  return set;
}

// Creates a CompressionAlgorithmSet from channel arguments
CompressionAlgorithmSet CompressionAlgorithmSet::FromChannelArgs(
    const ChannelArgs& args) {
  CompressionAlgorithmSet set;
  static const uint32_t kEverything =
      (1u << GRPC_COMPRESS_ALGORITHMS_COUNT) - 1;  // All bits set
  return CompressionAlgorithmSet::FromUint32(
      args.GetInt(GRPC_COMPRESSION_CHANNEL_ENABLED_ALGORITHMS_BITSET)
          .value_or(kEverything));  // Default to all if not specified
}

// Default constructor
CompressionAlgorithmSet::CompressionAlgorithmSet() = default;

// Constructor from initializer list of algorithms
CompressionAlgorithmSet::CompressionAlgorithmSet(
    std::initializer_list<grpc_compression_algorithm> algorithms) {
  for (auto algorithm : algorithms) {
    Set(algorithm);  // Set each algorithm in the list
  }
}

// Checks if an algorithm is enabled
bool CompressionAlgorithmSet::IsSet(
    grpc_compression_algorithm algorithm) const {
  size_t i = static_cast<size_t>(algorithm);
  if (i < GRPC_COMPRESS_ALGORITHMS_COUNT) {
    return set_.is_set(i);
  } else {
    return false;  // Invalid algorithm
  }
}

// Enables a specific algorithm
void CompressionAlgorithmSet::Set(grpc_compression_algorithm algorithm) {
  size_t i = static_cast<size_t>(algorithm);
  if (i < GRPC_COMPRESS_ALGORITHMS_COUNT) {
    set_.set(i);  // Set the bit for this algorithm
  }
}

// Returns a string representation of enabled algorithms
absl::string_view CompressionAlgorithmSet::ToString() const {
  return kCommaSeparatedLists[ToLegacyBitmask()];
}

// Returns a Slice containing the string representation
Slice CompressionAlgorithmSet::ToSlice() const {
  return Slice::FromStaticString(ToString());
}

// Creates a CompressionAlgorithmSet from a string
CompressionAlgorithmSet CompressionAlgorithmSet::FromString(
    absl::string_view str) {
  CompressionAlgorithmSet set{GRPC_COMPRESS_NONE};  // Start with identity
  // Split string by commas and parse each algorithm
  for (auto algorithm : absl::StrSplit(str, ',')) {
    auto parsed =
        ParseCompressionAlgorithm(absl::StripAsciiWhitespace(algorithm));
    if (parsed.has_value()) {
      set.Set(*parsed);  // Enable parsed algorithm
    }
  }
  return set;
}

// Converts the set to a legacy bitmask representation
uint32_t CompressionAlgorithmSet::ToLegacyBitmask() const {
  return set_.ToInt<uint32_t>();
}

// Gets default compression algorithm from channel arguments
std::optional<grpc_compression_algorithm>
DefaultCompressionAlgorithmFromChannelArgs(const ChannelArgs& args) {
  auto* value = args.Get(GRPC_COMPRESSION_CHANNEL_DEFAULT_ALGORITHM);
  if (value == nullptr) return std::nullopt;
  // Try to get as integer first
  auto ival = value->GetIfInt();
  if (ival.has_value()) {
    return static_cast<grpc_compression_algorithm>(*ival);
  }
  // Try to get as string if not an integer
  auto sval = value->GetIfString();
  if (sval != nullptr) {
    return ParseCompressionAlgorithm(sval->as_string_view());
  }
  return std::nullopt;
}

// Creates compression options from channel arguments
grpc_compression_options CompressionOptionsFromChannelArgs(
    const ChannelArgs& args) {
  grpc_compression_options compression_options;
  grpc_compression_options_init(&compression_options);
  
  // Set default compression level if specified
  auto default_level = args.GetInt(GRPC_COMPRESSION_CHANNEL_DEFAULT_LEVEL);
  if (default_level.has_value()) {
    compression_options.default_level.is_set = true;
    compression_options.default_level.level =
        static_cast<grpc_compression_level>(
            Clamp(*default_level, static_cast<int>(GRPC_COMPRESS_LEVEL_NONE),
                  static_cast<int>(GRPC_COMPRESS_LEVEL_COUNT - 1)));
  }
  
  // Set default algorithm if specified
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
  
  // Set enabled algorithms if specified
  auto enabled_algorithms_bitset =
      args.GetInt(GRPC_COMPRESSION_CHANNEL_ENABLED_ALGORITHMS_BITSET);
  if (enabled_algorithms_bitset.has_value()) {
    // Ensure at least identity (no compression) is always enabled
    compression_options.enabled_algorithms_bitset =
        *enabled_algorithms_bitset | 1;
  }
  return compression_options;
}

}  // namespace grpc_core
```