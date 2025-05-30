
// Copyright 2018 gRPC authors.

#include "src/cpp/ext/filters/census/rpc_encoding.h"

#include <grpc/support/port_platform.h>

namespace grpc {
namespace internal {

constexpr size_t RpcServerStatsEncoding::kRpcServerStatsSize;
constexpr size_t RpcServerStatsEncoding::kEncodeDecodeFailure;
constexpr size_t RpcServerStatsEncoding::kVersionIdSize;
constexpr size_t RpcServerStatsEncoding::kFieldIdSize;
constexpr size_t RpcServerStatsEncoding::kVersionIdOffset;
constexpr size_t RpcServerStatsEncoding::kVersionId;

}
}
