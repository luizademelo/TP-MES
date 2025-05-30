// Copyright 2023 gRPC authors.

#include "test/core/transport/test_suite/chaotic_good_fixture_helpers.h"

namespace grpc_core {

TRANSPORT_FIXTURE(ChaoticGoodOneByteChunks) {
  auto resource_quota = MakeResourceQuota("test");
  EndpointPair control_endpoints =
      CreateEndpointPair(event_engine.get(), resource_quota.get(), 1234);
  auto channel_args =
      ChannelArgs()
          .SetObject(resource_quota)
          .SetObject(
              std::static_pointer_cast<
                  grpc_event_engine::experimental::EventEngine>(event_engine));
  chaotic_good::Config client_config(channel_args);
  chaotic_good::Config server_config(channel_args);
  client_config.TestOnlySetChunkSizes(1);
  server_config.TestOnlySetChunkSizes(1);
  auto client_socket_node = chaotic_good::TcpFrameTransport::MakeSocketNode(
      channel_args, control_endpoints.client);
  auto server_socket_node = chaotic_good::TcpFrameTransport::MakeSocketNode(
      channel_args, control_endpoints.server);
  auto client_transport =
      MakeOrphanable<chaotic_good::ChaoticGoodClientTransport>(
          channel_args,
          MakeOrphanable<chaotic_good::TcpFrameTransport>(
              client_config.MakeTcpFrameTransportOptions(),
              std::move(control_endpoints.client),
              client_config.TakePendingDataEndpoints(),
              MakeRefCounted<chaotic_good::TransportContext>(
                  channel_args, std::move(client_socket_node))),
          client_config.MakeMessageChunker());
  auto server_transport =
      MakeOrphanable<chaotic_good::ChaoticGoodServerTransport>(
          channel_args,
          MakeOrphanable<chaotic_good::TcpFrameTransport>(
              server_config.MakeTcpFrameTransportOptions(),
              std::move(control_endpoints.server),
              server_config.TakePendingDataEndpoints(),
              MakeRefCounted<chaotic_good::TransportContext>(
                  channel_args, std::move(server_socket_node))),
          server_config.MakeMessageChunker());
  return ClientAndServerTransportPair{std::move(client_transport),
                                      std::move(server_transport), true};
}

}
