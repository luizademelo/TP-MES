// Copyright 2024 The gRPC Authors

#ifndef GRPC_SRC_CORE_UTIL_GLOB_H
#define GRPC_SRC_CORE_UTIL_GLOB_H

#include "absl/strings/string_view.h"

namespace grpc_core {

bool GlobMatch(absl::string_view name, absl::string_view pattern);

}

#endif
