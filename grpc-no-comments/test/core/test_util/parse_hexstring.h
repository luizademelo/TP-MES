
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_PARSE_HEXSTRING_H
#define GRPC_TEST_CORE_TEST_UTIL_PARSE_HEXSTRING_H

#include "absl/strings/string_view.h"
#include "src/core/lib/slice/slice.h"

namespace grpc_core {
Slice ParseHexstring(absl::string_view hexstring);
}

#endif
