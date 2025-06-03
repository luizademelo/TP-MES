Here's the commented version of the code:

```c++
// Copyright 2025 gRPC authors.

// Core configuration and transport-related headers
#include "src/core/config/core_configuration.h"
#include "src/core/ext/transport/chttp2/client/chttp2_connector.h"
#include "src/core/ext/transport/chttp2/server/chttp2_server.h"
#include "src/core/transport/endpoint_transport.h"

namespace grpc_core {
namespace {
// Implementation of EndpointTransport for HTTP/2 protocol
// This class provides concrete implementations for creating HTTP/2 channels
// and adding HTTP/2 ports to servers
class Chttp2Transport final : public EndpointTransport {
 public:
  // Creates an HTTP/2 channel to the specified target with given arguments
  // @param target The target address to connect to
  // @param args Channel configuration arguments
  // @return Returns either a successfully created channel or an error status
  absl::StatusOr<grpc_channel*> ChannelCreate(
      std::string target, const ChannelArgs& args) override {
    return CreateHttp2Channel(target, args);
  }

  // Adds an HTTP/2 port to the server
  // @param server The server to add the port to
  // @param addr The address to listen on
  // @param args Channel configuration arguments
  // @return Returns either the bound port number or an error status
  absl::StatusOr<int> AddPort(Server* server, std::string addr,
                              const ChannelArgs& args) override {
    return Chttp2ServerAddPort(server, addr.c_str(), args);
  }
};
}  // namespace

// Registers the HTTP/2 transport implementation with the core configuration
// @param builder The CoreConfiguration builder that maintains transport registry
void RegisterChttp2Transport(CoreConfiguration::Builder* builder) {
  builder->endpoint_transport_registry()->RegisterTransport(
      "h2",  // Protocol identifier for HTTP/2
      std::make_unique<Chttp2Transport>());
}
}  // namespace grpc_core
```

The comments explain:
1. The purpose of each include directive
2. The overall role of the Chttp2Transport class
3. The functionality of each method (parameters, return values, and purpose)
4. The registration process for the HTTP/2 transport
5. The meaning of the "h2" protocol identifier

The comments are placed close to the relevant code and provide clear explanations without being overly verbose. They follow a consistent style and cover both high-level concepts and implementation details.