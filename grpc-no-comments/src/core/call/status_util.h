
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_STATUS_UTIL_H
#define GRPC_SRC_CORE_CALL_STATUS_UTIL_H

#include <grpc/status.h>
#include <grpc/support/port_platform.h>

#include <string>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"

bool grpc_status_code_from_string(const char* status_str,
                                  grpc_status_code* status);

const char* grpc_status_code_to_string(grpc_status_code status);

bool grpc_status_code_from_int(int status_int, grpc_status_code* status);

namespace grpc_core {
namespace internal {

class StatusCodeSet {
 public:
  bool Empty() const { return status_code_mask_ == 0; }

  StatusCodeSet& Add(grpc_status_code status) {
    status_code_mask_ |= (1 << status);
    return *this;
  }

  bool Contains(grpc_status_code status) const {
    return status_code_mask_ & (1 << status);
  }

  bool operator==(const StatusCodeSet& other) const {
    return status_code_mask_ == other.status_code_mask_;
  }

  std::string ToString() const;

 private:
  int status_code_mask_ = 0;
};

}

absl::Status MaybeRewriteIllegalStatusCode(absl::Status status,
                                           absl::string_view source);

}

#endif
