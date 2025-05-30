// Copyright 2024 The gRPC Authors.

#ifndef GRPC_SRC_CORE_SERVER_SERVER_CALL_TRACER_FILTER_H
#define GRPC_SRC_CORE_SERVER_SERVER_CALL_TRACER_FILTER_H

#include <grpc/support/port_platform.h>

#include "src/core/config/core_configuration.h"

namespace grpc_core {

void RegisterServerCallTracerFilter(CoreConfiguration::Builder* builder);

}

#endif
