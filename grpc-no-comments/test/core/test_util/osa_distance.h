// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_OSA_DISTANCE_H
#define GRPC_TEST_CORE_TEST_UTIL_OSA_DISTANCE_H

#include <stddef.h>

#include "absl/strings/string_view.h"

namespace grpc_core {

size_t OsaDistance(absl::string_view s1, absl::string_view s2);

}

#endif
