// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_API_H
#define GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_API_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "src/core/config/core_configuration.h"
#include "src/core/lib/resource_quota/resource_quota.h"

typedef struct grpc_resource_quota grpc_resource_quota;

namespace grpc_core {

constexpr size_t kResourceQuotaChannelSize = 34 * 1024;

ResourceQuotaRefPtr ResourceQuotaFromChannelArgs(const grpc_channel_args* args);

ResourceQuotaRefPtr ResourceQuotaFromEndpointConfig(
    const grpc_event_engine::experimental::EndpointConfig& config);

void RegisterResourceQuota(CoreConfiguration::Builder* builder);

}

#endif
