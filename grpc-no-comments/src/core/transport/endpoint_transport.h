// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_TRANSPORT_ENDPOINT_TRANSPORT_H
#define GRPC_SRC_CORE_TRANSPORT_ENDPOINT_TRANSPORT_H

#include <grpc/impl/grpc_types.h>

#include <memory>
#include <string>

#include "src/core/lib/channel/channel_args.h"

namespace grpc_core {

class Server;

#define GRPC_ARG_PREFERRED_TRANSPORT_PROTOCOLS \
  "grpc.preferred_transport_protocols"

class EndpointTransport {
 public:
  virtual absl::StatusOr<grpc_channel*> ChannelCreate(
      std::string target, const ChannelArgs& args) = 0;
  virtual absl::StatusOr<int> AddPort(Server* server, std::string addr,
                                      const ChannelArgs& args) = 0;
  virtual ~EndpointTransport() = default;
};

class EndpointTransportRegistry {
 private:
  using TransportMap =
      std::map<std::string, std::unique_ptr<EndpointTransport>>;

 public:
  class Builder {
   public:
    void RegisterTransport(std::string name,
                           std::unique_ptr<EndpointTransport> transport) {
      if (transports_.find(name) != transports_.end()) {
        LOG(FATAL) << "Duplicate endpoint transport registration: " << name;
      }
      transports_[name] = std::move(transport);
    }

    EndpointTransportRegistry Build() {
      return EndpointTransportRegistry(std::move(transports_));
    }

   private:
    TransportMap transports_;
  };

  EndpointTransport* GetTransport(absl::string_view name) const {
    auto it = transports_.find(std::string(name));
    if (it == transports_.end()) {
      return nullptr;
    }
    return it->second.get();
  }

 private:
  explicit EndpointTransportRegistry(TransportMap transports)
      : transports_(std::move(transports)) {}

  TransportMap transports_;
};

}

#endif
