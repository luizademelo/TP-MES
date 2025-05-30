
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_STAT_H
#define GRPC_SRC_CORE_UTIL_STAT_H

#include <grpc/support/port_platform.h>
#include <time.h>

#include "absl/status/status.h"

namespace grpc_core {

absl::Status GetFileModificationTime(const char* filename, time_t* timestamp);

}

#endif
