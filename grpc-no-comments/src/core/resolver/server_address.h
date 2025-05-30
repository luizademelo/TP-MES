
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_SERVER_ADDRESS_H
#define GRPC_SRC_CORE_RESOLVER_SERVER_ADDRESS_H

#include <grpc/support/port_platform.h>

#include "src/core/resolver/endpoint_addresses.h"

namespace grpc_core {

using ServerAddress = EndpointAddresses;
using ServerAddressList = EndpointAddressesList;

}

#endif
