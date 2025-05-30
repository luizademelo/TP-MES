// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_LOAD_FILE_H
#define GRPC_SRC_CORE_UTIL_LOAD_FILE_H

#include <grpc/support/port_platform.h>

#include <string>

#include "absl/status/statusor.h"
#include "src/core/lib/slice/slice.h"

namespace grpc_core {

absl::StatusOr<Slice> LoadFile(const std::string& filename,
                               bool add_null_terminator);
}

#endif
