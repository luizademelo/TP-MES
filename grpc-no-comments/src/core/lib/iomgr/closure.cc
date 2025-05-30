// Copyright 2022 gRPC authors.

#include "src/core/lib/iomgr/closure.h"

#include <grpc/support/port_platform.h>

#include "absl/strings/str_format.h"

std::string grpc_closure::DebugString() const {
#ifdef NDEBUG
  return absl::StrFormat("%p", this);
#else
  return absl::StrFormat("%p|created=%s:%d", this, file_created, line_created);
#endif
}
