// Copyright 2025 gRPC authors.

#include "src/core/config/core_configuration.h"
#include "src/core/ext/transport/chttp2/client/chttp2_connector.h"
#include "src/core/ext/transport/chttp2/server/chttp2_server.h"
#include "src/core/transport/endpoint_transport.h"

namespace grpc_core {
namespace {
class Chttp2Transport final : public EndpointTransport {
 public:
  absl::StatusOr<grpc_channel*> ChannelCreate(
      std::string target, const ChannelArgs& args) override {
    return CreateHttp2Channel(target, args);
  }

  absl::StatusOr<int> AddPort(Server* server, std::string addr,
                              const ChannelArgs& args) override {
    return Chttp2ServerAddPort(server, addr.c_str(), args);
  }
};
}

void RegisterChttp2Transport(CoreConfiguration::Builder* builder) {
  builder->endpoint_transport_registry()->RegisterTransport(
      "h2", std::make_unique<Chttp2Transport>());
}
}