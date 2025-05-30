
// Copyright 2021 the gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_TIME_UTIL_H
#define GRPC_SRC_CORE_UTIL_TIME_UTIL_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include "absl/time/time.h"

namespace grpc_core {

gpr_timespec ToGprTimeSpec(absl::Duration duration);

gpr_timespec ToGprTimeSpec(absl::Time time);

absl::Duration ToAbslDuration(gpr_timespec ts);

absl::Time ToAbslTime(gpr_timespec ts);

}

#endif
