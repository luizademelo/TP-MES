// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_JSON_JSON_ARGS_H
#define GRPC_SRC_CORE_UTIL_JSON_JSON_ARGS_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"

namespace grpc_core {

class JsonArgs {
 public:
  JsonArgs() = default;
  virtual ~JsonArgs() = default;

  virtual bool IsEnabled(absl::string_view ) const { return true; }
};

}

#endif
