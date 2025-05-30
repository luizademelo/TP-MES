
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_GRPCLB_GRPCLB_BALANCER_ADDRESSES_H
#define GRPC_SRC_CORE_LOAD_BALANCING_GRPCLB_GRPCLB_BALANCER_ADDRESSES_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/resolver/endpoint_addresses.h"

namespace grpc_core {

grpc_arg CreateGrpclbBalancerAddressesArg(
    const EndpointAddressesList* endpoint_list);
GRPC_MUST_USE_RESULT
ChannelArgs SetGrpcLbBalancerAddresses(const ChannelArgs& args,
                                       EndpointAddressesList endpoint_list);
const EndpointAddressesList* FindGrpclbBalancerAddressesInChannelArgs(
    const ChannelArgs& args);

}

#endif
