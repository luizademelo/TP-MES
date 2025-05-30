// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_RESOLVER_DNS_C_ARES_DNS_RESOLVER_ARES_H
#define GRPC_SRC_CORE_RESOLVER_DNS_C_ARES_DNS_RESOLVER_ARES_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"

namespace grpc_core {

bool ShouldUseAresDnsResolver(absl::string_view resolver_env);
void RegisterAresDnsResolver(CoreConfiguration::Builder*);

}

#endif
