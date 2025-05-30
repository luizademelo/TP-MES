
// Copyright 2019 gRPC authors.

#include "src/core/load_balancing/grpclb/grpclb_balancer_addresses.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <utility>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/useful.h"

#define GRPC_ARG_GRPCLB_BALANCER_ADDRESSES \
  GRPC_ARG_NO_SUBCHANNEL_PREFIX "grpc.grpclb_balancer_addresses"

namespace grpc_core {

namespace {

void* BalancerAddressesArgCopy(void* p) {
  EndpointAddressesList* endpoint_list = static_cast<EndpointAddressesList*>(p);
  return new EndpointAddressesList(*endpoint_list);
}

void BalancerAddressesArgDestroy(void* p) {
  EndpointAddressesList* endpoint_list = static_cast<EndpointAddressesList*>(p);
  delete endpoint_list;
}

int BalancerAddressesArgCmp(void* p, void* q) {
  auto* endpoint_list1 = static_cast<EndpointAddressesList*>(p);
  auto* endpoint_list2 = static_cast<EndpointAddressesList*>(q);
  if (endpoint_list1 == nullptr || endpoint_list2 == nullptr) {
    return QsortCompare(endpoint_list1, endpoint_list2);
  }
  if (endpoint_list1->size() > endpoint_list2->size()) return 1;
  if (endpoint_list1->size() < endpoint_list2->size()) return -1;
  for (size_t i = 0; i < endpoint_list1->size(); ++i) {
    int retval = (*endpoint_list1)[i].Cmp((*endpoint_list2)[i]);
    if (retval != 0) return retval;
  }
  return 0;
}

const grpc_arg_pointer_vtable kBalancerAddressesArgVtable = {
    BalancerAddressesArgCopy, BalancerAddressesArgDestroy,
    BalancerAddressesArgCmp};

}

grpc_arg CreateGrpclbBalancerAddressesArg(
    const EndpointAddressesList* endpoint_list) {
  return grpc_channel_arg_pointer_create(
      const_cast<char*>(GRPC_ARG_GRPCLB_BALANCER_ADDRESSES),
      const_cast<EndpointAddressesList*>(endpoint_list),
      &kBalancerAddressesArgVtable);
}

const EndpointAddressesList* FindGrpclbBalancerAddressesInChannelArgs(
    const ChannelArgs& args) {
  return args.GetPointer<const EndpointAddressesList>(
      GRPC_ARG_GRPCLB_BALANCER_ADDRESSES);
}

ChannelArgs SetGrpcLbBalancerAddresses(const ChannelArgs& args,
                                       EndpointAddressesList endpoint_list) {
  return args.Set(
      GRPC_ARG_GRPCLB_BALANCER_ADDRESSES,
      ChannelArgs::Pointer(new EndpointAddressesList(std::move(endpoint_list)),
                           &kBalancerAddressesArgVtable));
}

}
