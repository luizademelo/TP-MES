
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_CHANNELZ_CHANNELZ_SERVICE_H
#define GRPC_SRC_CPP_SERVER_CHANNELZ_CHANNELZ_SERVICE_H

#include <grpc/support/port_platform.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/status.h>

#include "src/proto/grpc/channelz/channelz.grpc.pb.h"

namespace grpc {

class ChannelzService final : public channelz::v1::Channelz::Service {
 private:

  Status GetTopChannels(
      ServerContext* unused, const channelz::v1::GetTopChannelsRequest* request,
      channelz::v1::GetTopChannelsResponse* response) override;

  Status GetServers(ServerContext* unused,
                    const channelz::v1::GetServersRequest* request,
                    channelz::v1::GetServersResponse* response) override;

  Status GetServer(ServerContext* unused,
                   const channelz::v1::GetServerRequest* request,
                   channelz::v1::GetServerResponse* response) override;

  Status GetServerSockets(
      ServerContext* unused,
      const channelz::v1::GetServerSocketsRequest* request,
      channelz::v1::GetServerSocketsResponse* response) override;

  Status GetChannel(ServerContext* unused,
                    const channelz::v1::GetChannelRequest* request,
                    channelz::v1::GetChannelResponse* response) override;

  Status GetSubchannel(ServerContext* unused,
                       const channelz::v1::GetSubchannelRequest* request,
                       channelz::v1::GetSubchannelResponse* response) override;

  Status GetSocket(ServerContext* unused,
                   const channelz::v1::GetSocketRequest* request,
                   channelz::v1::GetSocketResponse* response) override;
};

}

#endif
