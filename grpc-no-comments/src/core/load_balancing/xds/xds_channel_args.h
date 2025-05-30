
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_XDS_XDS_CHANNEL_ARGS_H
#define GRPC_SRC_CORE_LOAD_BALANCING_XDS_XDS_CHANNEL_ARGS_H

#include <grpc/support/port_platform.h>

#include "src/core/resolver/endpoint_addresses.h"

#define GRPC_ARG_XDS_CLUSTER_NAME "grpc.internal.xds_cluster_name"

#define GRPC_ARG_XDS_LOGICAL_DNS_CLUSTER_FAKE_RESOLVER_RESPONSE_GENERATOR \
  "grpc.TEST_ONLY.xds_logical_dns_cluster_fake_resolver_response_generator"

#define GRPC_ARG_XDS_LOCALITY_WEIGHT \
  GRPC_ARG_NO_SUBCHANNEL_PREFIX "xds_locality_weight"

#endif
