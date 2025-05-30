// Copyright 2022 The gRPC Authors

#ifndef GRPC_TEST_CORE_EVENT_ENGINE_TEST_INIT_H
#define GRPC_TEST_CORE_EVENT_ENGINE_TEST_INIT_H
#include <grpc/support/port_platform.h>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"

namespace grpc_event_engine {
namespace experimental {

absl::Status InitializeTestingEventEngineFactory(absl::string_view engine);

}
}

#endif
