// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_RESOLVER_DNS_DNS_RESOLVER_PLUGIN_H
#define GRPC_SRC_CORE_RESOLVER_DNS_DNS_RESOLVER_PLUGIN_H
#include <grpc/support/port_platform.h>

#include "src/core/config/core_configuration.h"

namespace grpc_core {

void RegisterDnsResolver(CoreConfiguration::Builder* builder);

}

#endif
