Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_FILTERS_CENSUS_RPC_ENCODING_H
#define GRPC_SRC_CPP_EXT_FILTERS_CENSUS_RPC_ENCODING_H

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <string.h>

#include "absl/base/internal/endian.h"
#include "absl/strings/string_view.h"

namespace grpc {
namespace internal {

// Class for encoding and decoding RPC server statistics in a binary format.
// The format consists of:
// - 1 byte version identifier
// - 1 byte field ID
// - 8 bytes of server elapsed time (little-endian)
class RpcServerStatsEncoding {
 public:
  // Total size of the encoded RPC server stats (1 + 1 + 8 bytes)
  static constexpr size_t kRpcServerStatsSize = 10;

  // Return value indicating encoding/decoding failure
  static constexpr size_t kEncodeDecodeFailure = 0;

  // Decodes RPC server statistics from a buffer.
  // buf: Input buffer containing encoded data
  // time: Output parameter for the decoded server elapsed time
  // Returns: Number of bytes consumed (kRpcServerStatsSize) on success,
  //          kEncodeDecodeFailure on failure
  static size_t Decode(absl::string_view buf, uint64_t* time) {
    // Check if buffer is large enough to contain the encoded data
    if (buf.size() < kRpcServerStatsSize) {
      *time = 0;
      return kEncodeDecodeFailure;
    }

    // Verify version and field ID match expected values
    uint8_t version = buf[kVersionIdOffset];
    uint32_t fieldID = buf[kServerElapsedTimeOffset];
    if (version != kVersionId || fieldID != kServerElapsedTimeField) {
      *time = 0;
      return kEncodeDecodeFailure;
    }
    // Extract and convert little-endian 64-bit time value
    *time = absl::little_endian::Load64(
        &buf[kServerElapsedTimeOffset + kFieldIdSize]);
    return kRpcServerStatsSize;
  }

  // Encodes RPC server statistics into a buffer.
  // time: Server elapsed time to encode
  // buf: Output buffer for encoded data
  // buf_size: Size of the output buffer
  // Returns: Number of bytes written (kRpcServerStatsSize) on success,
  //          kEncodeDecodeFailure on failure
  static size_t Encode(uint64_t time, char* buf, size_t buf_size) {
    // Check if buffer is large enough to hold the encoded data
    if (buf_size < kRpcServerStatsSize) {
      return kEncodeDecodeFailure;
    }

    // Write version ID and field ID
    buf[kVersionIdOffset] = kVersionId;
    buf[kServerElapsedTimeOffset] = kServerElapsedTimeField;
    // Store time value in little-endian format
    absl::little_endian::Store64(&buf[kServerElapsedTimeOffset + kFieldIdSize],
                                 time);
    return kRpcServerStatsSize;
  }

 private:
  // Size of version ID field (1 byte)
  static constexpr size_t kVersionIdSize = 1;
  
  // Size of field ID (1 byte)
  static constexpr size_t kFieldIdSize = 1;

  // Offset and value of version ID field
  static constexpr size_t kVersionIdOffset = 0;
  static constexpr size_t kVersionId = 0;

  // Field ID values
  enum FieldIdValue {
    kServerElapsedTimeField = 0,  // Field ID for server elapsed time
  };

  // Field sizes
  enum FieldSize {
    kServerElapsedTimeSize = 8,  // Size of server elapsed time field (8 bytes)
  };

  // Field offsets
  enum FieldIdOffset {
    kServerElapsedTimeOffset = kVersionIdSize,  // Offset of server time field
  };

  // Disallow instantiation and copying
  RpcServerStatsEncoding() = delete;
  RpcServerStatsEncoding(const RpcServerStatsEncoding&) = delete;
  RpcServerStatsEncoding(RpcServerStatsEncoding&&) = delete;
  RpcServerStatsEncoding operator=(const RpcServerStatsEncoding&) = delete;
  RpcServerStatsEncoding operator=(RpcServerStatsEncoding&&) = delete;
};

}  // namespace internal
}  // namespace grpc

#endif  // GRPC_SRC_CPP_EXT_FILTERS_CENSUS_RPC_ENCODING_H
```