// Copyright 2024 The gRPC Authors

#ifndef GRPC_PASSIVE_LISTENER_H
#define GRPC_PASSIVE_LISTENER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>

#include <memory>

namespace grpc_core {
class Server;

namespace experimental {
class PassiveListenerImpl;

class PassiveListener {
 public:
  virtual ~PassiveListener() = default;

  virtual absl::Status AcceptConnectedEndpoint(
      std::unique_ptr<grpc_event_engine::experimental::EventEngine::Endpoint>
          endpoint) = 0;

  virtual absl::Status AcceptConnectedFd(int fd) = 0;
};

}
}

absl::Status grpc_server_add_passive_listener(
    grpc_core::Server* server, grpc_server_credentials* credentials,
    std::shared_ptr<grpc_core::experimental::PassiveListenerImpl>
        passive_listener);

#endif
