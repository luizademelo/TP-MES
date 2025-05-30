// Copyright 2025 gRPC authors.

#include "src/core/lib/promise/wait_set.h"

#include "absl/strings/str_join.h"

namespace grpc_core {

std::string WaitSet::ToString() {
  return absl::StrJoin(pending_, ", ",
                       [](std::string* out, const Waker& waker) {
                         absl::StrAppend(out, waker.DebugString());
                       });
}

}
