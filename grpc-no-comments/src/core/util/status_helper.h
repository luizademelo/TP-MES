
// Copyright 2021 the gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_STATUS_HELPER_H
#define GRPC_SRC_CORE_UTIL_STATUS_HELPER_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <optional>
#include <string>
#include <vector>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "absl/time/time.h"
#include "src/core/util/debug_location.h"

extern "C" {
struct google_rpc_Status;
struct upb_Arena;
}

#define GRPC_RETURN_IF_ERROR(expr)      \
  do {                                  \
    const absl::Status status = (expr); \
    if (!status.ok()) return status;    \
  } while (0)

namespace grpc_core {

enum class StatusIntProperty {

  kStreamId,

  kRpcStatus,

  kHttp2Error,

  ChannelConnectivityState,

  kLbPolicyDrop,
};

enum class StatusStrProperty {

  kGrpcMessage,
};

absl::Status StatusCreate(absl::StatusCode code, absl::string_view msg,
                          const DebugLocation& location,
                          std::vector<absl::Status> children);

void StatusSetInt(absl::Status* status, StatusIntProperty key, intptr_t value);

GRPC_MUST_USE_RESULT
std::optional<intptr_t> StatusGetInt(const absl::Status& status,
                                     StatusIntProperty key);

void StatusSetStr(absl::Status* status, StatusStrProperty key,
                  absl::string_view value);

GRPC_MUST_USE_RESULT std::optional<std::string> StatusGetStr(
    const absl::Status& status, StatusStrProperty key);

void StatusAddChild(absl::Status* status, absl::Status child);

GRPC_MUST_USE_RESULT std::vector<absl::Status> StatusGetChildren(
    absl::Status status);

GRPC_MUST_USE_RESULT std::string StatusToString(const absl::Status& status);

absl::Status AddMessagePrefix(absl::string_view prefix,
                              const absl::Status& status);

namespace internal {

GRPC_MUST_USE_RESULT google_rpc_Status* StatusToProto(
    const absl::Status& status, upb_Arena* arena);

absl::Status StatusFromProto(google_rpc_Status* msg);

uintptr_t StatusAllocHeapPtr(absl::Status s);

void StatusFreeHeapPtr(uintptr_t ptr);

absl::Status StatusGetFromHeapPtr(uintptr_t ptr);

absl::Status StatusMoveFromHeapPtr(uintptr_t ptr);

}

}

#endif
