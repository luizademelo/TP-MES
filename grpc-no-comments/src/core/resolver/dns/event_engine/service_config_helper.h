// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_RESOLVER_DNS_EVENT_ENGINE_SERVICE_CONFIG_HELPER_H
#define GRPC_SRC_CORE_RESOLVER_DNS_EVENT_ENGINE_SERVICE_CONFIG_HELPER_H

#include <grpc/support/port_platform.h>

#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

absl::StatusOr<std::string> ChooseServiceConfig(
    absl::string_view service_config_json);

}

#endif
