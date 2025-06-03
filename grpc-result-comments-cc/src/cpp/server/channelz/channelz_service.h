Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CPP_SERVER_CHANNELZ_CHANNELZ_SERVICE_H
#define GRPC_SRC_CPP_SERVER_CHANNELZ_CHANNELZ_SERVICE_H

// Include necessary headers
#include <grpc/support/port_platform.h>  // Platform-specific support
#include <grpcpp/grpcpp.h>               // Core gRPC C++ functionality
#include <grpcpp/support/status.h>       // gRPC status codes

// Include the generated gRPC protobuf service definition for channelz
#include "src/proto/grpc/channelz/channelz.grpc.pb.h"

namespace grpc {

// ChannelzService implements the channelz service defined in the protobuf file.
// This service provides diagnostic information about gRPC channels, servers,
// and other internal components.
class ChannelzService final : public channelz::v1::Channelz::Service {
 private:
  // Retrieves a list of top-level channels (channels not part of any subchannel)
  // that exist in the process.
  Status GetTopChannels(
      ServerContext* unused, const channelz::v1::GetTopChannelsRequest* request,
      channelz::v1::GetTopChannelsResponse* response) override;

  // Retrieves a list of servers that exist in the process.
  Status GetServers(ServerContext* unused,
                    const channelz::v1::GetServersRequest* request,
                    channelz::v1::GetServersResponse* response) override;

  // Retrieves detailed information about a specific server.
  Status GetServer(ServerContext* unused,
                   const channelz::v1::GetServerRequest* request,
                   channelz::v1::GetServerResponse* response) override;

  // Retrieves a list of sockets that belong to a particular server.
  Status GetServerSockets(
      ServerContext* unused,
      const channelz::v1::GetServerSocketsRequest* request,
      channelz::v1::GetServerSocketsResponse* response) override;

  // Retrieves detailed information about a specific channel.
  Status GetChannel(ServerContext* unused,
                    const channelz::v1::GetChannelRequest* request,
                    channelz::v1::GetChannelResponse* response) override;

  // Retrieves detailed information about a specific subchannel.
  Status GetSubchannel(ServerContext* unused,
                       const channelz::v1::GetSubchannelRequest* request,
                       channelz::v1::GetSubchannelResponse* response) override;

  // Retrieves detailed information about a specific socket.
  Status GetSocket(ServerContext* unused,
                   const channelz::v1::GetSocketRequest* request,
                   channelz::v1::GetSocketResponse* response) override;
};

}  // namespace grpc

#endif  // GRPC_SRC_CPP_SERVER_CHANNELZ_CHANNELZ_SERVICE_H
```

The comments added explain:
1. The purpose of the header guard
2. The purpose of each included header
3. The overall purpose of the ChannelzService class
4. The functionality of each service method
5. The namespace closure and header guard ending

The comments are concise yet informative, providing enough context for future maintainers to understand what each part does without being overly verbose.