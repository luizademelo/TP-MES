// Copyright 2022 The gRPC Authors

#include "test/core/event_engine/test_init.h"

#include <grpc/support/port_platform.h>

#include <string>

#include "absl/strings/str_cat.h"

namespace grpc_event_engine {
namespace experimental {

absl::Status InitializeTestingEventEngineFactory(absl::string_view engine) {
  if (engine == "default" || engine.empty()) {

    return absl::OkStatus();
  }
  return absl::InvalidArgumentError(
      absl::StrCat("Unknown EventEngine implementation: ", engine));
}

}
}
