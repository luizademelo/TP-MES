
// Copyright 2015 gRPC authors.

#include "src/core/lib/slice/slice_string_helpers.h"

#include <grpc/support/port_platform.h>

#include "src/core/util/string.h"

char* grpc_dump_slice(const grpc_slice& s, uint32_t flags) {
  return gpr_dump(reinterpret_cast<const char*> GRPC_SLICE_START_PTR(s),
                  GRPC_SLICE_LENGTH(s), flags);
}
