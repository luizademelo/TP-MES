// Copyright 2024 gRPC authors.

#include <benchmark/benchmark.h>
#include <grpc/grpc.h>

#include <cstddef>

#include "absl/strings/string_view.h"
#include "src/core/call/metadata.h"
#include "src/core/ext/filters/http/client/http_client_filter.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/lib/transport/transport.h"
#include "test/core/call/call_spine_benchmarks.h"

namespace grpc_core {

class HttpClientFilterTraits {
 public:
  using Filter = HttpClientFilter;

  ChannelArgs MakeChannelArgs() { return ChannelArgs().SetObject(&transport_); }

  ClientMetadataHandle MakeClientInitialMetadata() {
    return Arena::MakePooledForOverwrite<ClientMetadata>();
  }

  ServerMetadataHandle MakeServerInitialMetadata() {
    return Arena::MakePooledForOverwrite<ServerMetadata>();
  }

  MessageHandle MakePayload() { return Arena::MakePooled<Message>(); }

  ServerMetadataHandle MakeServerTrailingMetadata() {
    auto md = Arena::MakePooledForOverwrite<ServerMetadata>();
    md->Set(HttpStatusMetadata(), 200);
    return md;
  }

 private:
  class FakeTransport final : public Transport {
   public:
    FilterStackTransport* filter_stack_transport() override { return nullptr; }
    ClientTransport* client_transport() override { return nullptr; }
    ServerTransport* server_transport() override { return nullptr; }
    absl::string_view GetTransportName() const override { return "fake-http"; }
    void SetPollset(grpc_stream*, grpc_pollset*) override {}
    void SetPollsetSet(grpc_stream*, grpc_pollset_set*) override {}
    void PerformOp(grpc_transport_op*) override {}
    void Orphan() override {}
    RefCountedPtr<channelz::SocketNode> GetSocketNode() const override {
      return nullptr;
    }
  };

  FakeTransport transport_;
};
GRPC_CALL_SPINE_BENCHMARK(FilterFixture<HttpClientFilterTraits>);

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
