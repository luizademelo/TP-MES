// Copyright 2025 gRPC authors.

#include "src/core/ext/transport/chaotic_good/chaotic_good.h"

#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/transport/chaotic_good/client/chaotic_good_connector.h"
#include "src/core/ext/transport/chaotic_good/server/chaotic_good_server.h"

namespace grpc_core::chaotic_good {

namespace {

class ChaoticGoodEndpointTransport final : public EndpointTransport {
 public:
  absl::StatusOr<grpc_channel*> ChannelCreate(
      std::string target, const ChannelArgs& args) override {
    return CreateChaoticGoodChannel(std::move(target), args);
  }

  absl::StatusOr<int> AddPort(Server* server, std::string addr,
                              const ChannelArgs& args) override {
    return AddChaoticGoodPort(server, std::move(addr), args);
  }
};

const absl::string_view kWireFormatPreferences = []() {

  CoreConfiguration::RegisterPersistentBuilder(
      [](CoreConfiguration::Builder* builder) {
        builder->endpoint_transport_registry()->RegisterTransport(
            "cg3", std::make_unique<ChaoticGoodEndpointTransport>());
      });
  return "cg3";
}();

}

absl::string_view WireFormatPreferences() { return kWireFormatPreferences; }

}
