// Copyright 2023 gRPC authors.

#ifndef GRPC_PYTHON_OPENCENSUS_RPC_ENCODING_H
#define GRPC_PYTHON_OPENCENSUS_RPC_ENCODING_H

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <string.h>

#include "absl/base/internal/endian.h"
#include "absl/strings/string_view.h"

namespace grpc_observability {

class RpcServerStatsEncoding {
 public:

  static constexpr size_t kRpcServerStatsSize = 10;

  static constexpr size_t kEncodeDecodeFailure = 0;

  static size_t Decode(absl::string_view buf, uint64_t* time) {
    if (buf.size() < kRpcServerStatsSize) {
      *time = 0;
      return kEncodeDecodeFailure;
    }

    uint8_t version = buf[kVersionIdOffset];
    uint32_t fieldID = buf[kServerElapsedTimeOffset];
    if (version != kVersionId || fieldID != kServerElapsedTimeField) {
      *time = 0;
      return kEncodeDecodeFailure;
    }
    *time = absl::little_endian::Load64(
        &buf[kServerElapsedTimeOffset + kFieldIdSize]);
    return kRpcServerStatsSize;
  }

  static size_t Encode(uint64_t time, char* buf, size_t buf_size) {
    if (buf_size < kRpcServerStatsSize) {
      return kEncodeDecodeFailure;
    }

    buf[kVersionIdOffset] = kVersionId;
    buf[kServerElapsedTimeOffset] = kServerElapsedTimeField;
    absl::little_endian::Store64(&buf[kServerElapsedTimeOffset + kFieldIdSize],
                                 time);
    return kRpcServerStatsSize;
  }

 private:

  static constexpr size_t kVersionIdSize = 1;

  static constexpr size_t kFieldIdSize = 1;

  static constexpr size_t kVersionIdOffset = 0;
  static constexpr size_t kVersionId = 0;

  enum FieldIdValue {
    kServerElapsedTimeField = 0,
  };

  enum FieldSize {
    kServerElapsedTimeSize = 8,
  };

  enum FieldIdOffset {
    kServerElapsedTimeOffset = kVersionIdSize,
  };

  RpcServerStatsEncoding() = delete;
  RpcServerStatsEncoding(const RpcServerStatsEncoding&) = delete;
  RpcServerStatsEncoding(RpcServerStatsEncoding&&) = delete;
  RpcServerStatsEncoding operator=(const RpcServerStatsEncoding&) = delete;
  RpcServerStatsEncoding operator=(RpcServerStatsEncoding&&) = delete;
};

}

#endif
