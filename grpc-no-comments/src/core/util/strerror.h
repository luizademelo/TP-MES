// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_STRERROR_H
#define GRPC_SRC_CORE_UTIL_STRERROR_H

#include <grpc/support/port_platform.h>

#include <string>

namespace grpc_core {

std::string StrError(int err);

}

#endif
