// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_TRANSPORT_ENDPOINT_TRANSPORT_CLIENT_CHANNEL_FACTORY_H
#define GRPC_SRC_CORE_TRANSPORT_ENDPOINT_TRANSPORT_CLIENT_CHANNEL_FACTORY_H

#include "src/core/client_channel/client_channel_factory.h"
#include "src/core/client_channel/subchannel.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/no_destruct.h"

namespace grpc_core {

namespace endpoint_transport_client_channel_factory_detail {

class GenericClientChannelFactory : public ClientChannelFactory {
 public:
  RefCountedPtr<Subchannel> CreateSubchannel(
      const grpc_resolved_address& address, const ChannelArgs& args) override;

 private:
  virtual OrphanablePtr<SubchannelConnector> MakeConnector() = 0;

  static absl::StatusOr<ChannelArgs> GetSecureNamingChannelArgs(
      ChannelArgs args);
};

template <typename Connector>
class TypedClientChannelFactory final : public GenericClientChannelFactory {
 private:
  OrphanablePtr<SubchannelConnector> MakeConnector() override {
    return MakeOrphanable<Connector>();
  };
};

}

template <typename Connector>
auto EndpointTransportClientChannelFactory() {
  return NoDestructSingleton<endpoint_transport_client_channel_factory_detail::
                                 TypedClientChannelFactory<Connector>>::Get();
}

}

#endif
