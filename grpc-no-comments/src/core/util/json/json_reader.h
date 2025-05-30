
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_JSON_JSON_READER_H
#define GRPC_SRC_CORE_UTIL_JSON_JSON_READER_H

#include <grpc/support/port_platform.h>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"

namespace grpc_core {

absl::StatusOr<Json> JsonParse(absl::string_view json_str);

}

#endif
