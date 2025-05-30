// Copyright 2024 gRPC authors.

#include <benchmark/benchmark.h>
#include <grpc/grpc.h>

#include "absl/memory/memory.h"
#include "absl/strings/string_view.h"
#include "src/core/ext/transport/chaotic_good/client_transport.h"
#include "src/core/ext/transport/chaotic_good/server_transport.h"
#include "src/core/ext/transport/chaotic_good/tcp_frame_transport.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "test/core/call/call_spine_benchmarks.h"
#include "test/core/test_util/passthrough_endpoint.h"

namespace grpc_core {
namespace {

const Slice kTestPath = Slice::FromExternalString("/foo/bar");

class ChaoticGoodTraits {
 public:
  BenchmarkTransport MakeTransport() {
    auto channel_args = CoreConfiguration::Get()
                            .channel_args_preconditioning()
                            .PreconditionChannelArgs(nullptr);
    chaotic_good::Config client_config(channel_args);
    chaotic_good::Config server_config(channel_args);
    auto control = grpc_event_engine::experimental::PassthroughEndpoint::
        MakePassthroughEndpoint(1, 2, true);
    auto data = grpc_event_engine::experimental::PassthroughEndpoint::
        MakePassthroughEndpoint(3, 4, true);
    client_config.ServerAddPendingDataEndpoint(
        chaotic_good::ImmediateConnection(
            "foo", PromiseEndpoint(std::move(data.client), SliceBuffer())));
    server_config.ServerAddPendingDataEndpoint(
        chaotic_good::ImmediateConnection(
            "foo", PromiseEndpoint(std::move(data.server), SliceBuffer())));
    auto client = MakeOrphanable<chaotic_good::ChaoticGoodClientTransport>(
        channel_args,
        MakeOrphanable<chaotic_good::TcpFrameTransport>(
            client_config.MakeTcpFrameTransportOptions(),
            PromiseEndpoint(std::move(control.client), SliceBuffer()),
            client_config.TakePendingDataEndpoints(),
            MakeRefCounted<chaotic_good::TransportContext>(channel_args,
                                                           nullptr)),
        client_config.MakeMessageChunker());
    auto server = MakeOrphanable<chaotic_good::ChaoticGoodServerTransport>(
        channel_args,
        MakeOrphanable<chaotic_good::TcpFrameTransport>(
            client_config.MakeTcpFrameTransportOptions(),
            PromiseEndpoint(std::move(control.server), SliceBuffer()),
            server_config.TakePendingDataEndpoints(),
            MakeRefCounted<chaotic_good::TransportContext>(channel_args,
                                                           nullptr)),
        server_config.MakeMessageChunker());
    return {std::move(client), std::move(server)};
  }

  ClientMetadataHandle MakeClientInitialMetadata() {
    auto md = Arena::MakePooledForOverwrite<ClientMetadata>();
    md->Set(HttpPathMetadata(), kTestPath.Copy());
    return md;
  }

  ServerMetadataHandle MakeServerInitialMetadata() {
    return Arena::MakePooledForOverwrite<ServerMetadata>();
  }

  MessageHandle MakePayload() { return Arena::MakePooled<Message>(); }

  ServerMetadataHandle MakeServerTrailingMetadata() {
    auto md = Arena::MakePooledForOverwrite<ServerMetadata>();
    return md;
  }

 private:
  class FakeClientConnectionFactory
      : public chaotic_good::ClientConnectionFactory {
   public:
    chaotic_good::PendingConnection Connect(absl::string_view id) override {
      Crash("Connect not implemented");
    }
    void Orphaned() override {}
  };

  class FakeServerConnectionFactory
      : public chaotic_good::ServerConnectionFactory {
   public:
    chaotic_good::PendingConnection RequestDataConnection() override {
      Crash("RequestDataConnection not implemented");
    }
    void Orphaned() override {}
  };
};
GRPC_CALL_SPINE_BENCHMARK(TransportFixture<ChaoticGoodTraits>);

}
}

namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}

int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  grpc_init();
  {
    auto ee = grpc_event_engine::experimental::GetDefaultEventEngine();
    benchmark::RunTheBenchmarksNamespaced();
  }
  grpc_shutdown();
  return 0;
}
