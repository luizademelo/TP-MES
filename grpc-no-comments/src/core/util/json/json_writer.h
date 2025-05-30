
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_JSON_JSON_WRITER_H
#define GRPC_SRC_CORE_UTIL_JSON_JSON_WRITER_H

#include <grpc/support/port_platform.h>

#include <string>

#include "src/core/util/json/json.h"

namespace grpc_core {

std::string JsonDump(const Json& json, int indent = 0);

}

#endif
