
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_UUID_V4_H
#define GRPC_SRC_CORE_UTIL_UUID_V4_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <string>

namespace grpc_core {

std::string GenerateUUIDv4(uint64_t hi, uint64_t lo);

}

#endif
