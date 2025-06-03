Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#ifndef GRPC_PYTHON_OPENCENSUS_RPC_ENCODING_H
#define GRPC_PYTHON_OPENCENSUS_RPC_ENCODING_H

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <string.h>

#include "absl/base/internal/endian.h"
#include "absl/strings/string_view.h"

namespace grpc_observability {

// Class for encoding and decoding RPC server statistics in a binary format.
// The format consists of a version byte followed by field ID-value pairs.
class RpcServerStatsEncoding {
 public:
  // Fixed size of the encoded RPC server stats (1 byte version + 1 byte field ID + 8 bytes value)
  static constexpr size_t kRpcServerStatsSize = 10;

  // Return value indicating encode/decode failure
  static constexpr size_t kEncodeDecodeFailure = 0;

  // Decodes RPC server statistics from a buffer.
  // Args:
  //   buf: Input buffer containing encoded data
  //   time: Output parameter for the decoded server elapsed time
  // Returns:
  //   Size of decoded data (kRpcServerStatsSize) on success,
  //   kEncodeDecodeFailure on failure
  static size_t Decode(absl::string_view buf, uint64_t* time) {
    if (buf.size() < kRpcServerStatsSize) {
      *time = 0;
      return kEncodeDecodeFailure;
    }

    // Check version and field ID
    uint8_t version = buf[kVersionIdOffset];
    uint32_t fieldID = buf[kServerElapsedTimeOffset];
    if (version != kVersionId || fieldID != kServerElapsedTimeField) {
      *time = 0;
      return kEncodeDecodeFailure;
    }
    // Read little-endian 64-bit time value
    *time = absl::little_endian::Load64(
        &buf[kServerElapsedTimeOffset + kFieldIdSize]);
    return kRpcServerStatsSize;
  }

  // Encodes RPC server statistics into a buffer.
  // Args:
  //   time: Server elapsed time to encode
  //   buf: Output buffer for encoded data
  //   buf_size: Size of output buffer
  // Returns:
  //   Size of encoded data (kRpcServerStatsSize) on success,
  //   kEncodeDecodeFailure on failure
  static size_t Encode(uint64_t time, char* buf, size_t buf_size) {
    if (buf_size < kRpcServerStatsSize) {
      return kEncodeDecodeFailure;
    }

    // Write version byte and field ID
    buf[kVersionIdOffset] = kVersionId;
    buf[kServerElapsedTimeOffset] = kServerElapsedTimeField;
    // Write little-endian 64-bit time value
    absl::little_endian::Store64(&buf[kServerElapsedTimeOffset + kFieldIdSize],
                                 time);
    return kRpcServerStatsSize;
  }

 private:
  // Size of version field (1 byte)
  static constexpr size_t kVersionIdSize = 1;
  // Size of field ID (1 byte)
  static constexpr size_t kFieldIdSize = 1;

  // Offset of version field in the buffer
  static constexpr size_t kVersionIdOffset = 0;
  // Current version identifier
  static constexpr size_t kVersionId = 0;

  // Field ID values
  enum FieldIdValue {
    kServerElapsedTimeField = 0,  // Field ID for server elapsed time
  };

  // Field sizes
  enum FieldSize {
    kServerElapsedTimeSize = 8,  // Size of server elapsed time field (8 bytes)
  };

  // Field offsets in the buffer
  enum FieldIdOffset {
    kServerElapsedTimeOffset = kVersionIdSize,  // Offset of server elapsed time field
  };

  // Prevent instantiation - this is a utility class with only static methods
  RpcServerStatsEncoding() = delete;
  RpcServerStatsEncoding(const RpcServerStatsEncoding&) = delete;
  RpcServerStatsEncoding(RpcServerStatsEncoding&&) = delete;
  RpcServerStatsEncoding operator=(const RpcServerStatsEncoding&) = delete;
  RpcServerStatsEncoding operator=(RpcServerStatsEncoding&&) = delete;
};

}  // namespace grpc_observability

#endif  // GRPC_PYTHON_OPENCENSUS_RPC_ENCODING_H
```

The comments explain:
1. The overall purpose of the class (encoding/decoding RPC server stats)
2. Each public method's purpose, parameters, and return values
3. The binary format structure (version byte + field ID + value)
4. The meaning of each constant and enum
5. The prevention of instantiation/copying
6. The little-endian encoding used for the time value

The comments are designed to help future developers understand:
- How to use the class
- The binary format specification
- The error handling approach
- The purpose of each component