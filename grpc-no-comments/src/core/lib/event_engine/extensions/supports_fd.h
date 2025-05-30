// Copyright 2024 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_SUPPORTS_FD_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_SUPPORTS_FD_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include "absl/functional/any_invocable.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_event_engine::experimental {

class EndpointSupportsFdExtension {
 public:
  virtual ~EndpointSupportsFdExtension() = default;
  static absl::string_view EndpointExtensionName() {
    return "io.grpc.event_engine.extension.endpoint_supports_fd";
  }

  virtual int GetWrappedFd() = 0;

  virtual void Shutdown(absl::AnyInvocable<void(absl::StatusOr<int> release_fd)>
                            on_release_fd) = 0;
};

class ListenerSupportsFdExtension {
 public:
  virtual ~ListenerSupportsFdExtension() = default;
  static absl::string_view EndpointExtensionName() {
    return "io.grpc.event_engine.extension.listener_supports_fd";
  }

  using OnPosixBindNewFdCallback =
      absl::AnyInvocable<void(absl::StatusOr<int> listener_fd)>;

  virtual absl::StatusOr<int> BindWithFd(
      const EventEngine::ResolvedAddress& addr,
      OnPosixBindNewFdCallback on_bind_new_fd) = 0;

  virtual absl::Status HandleExternalConnection(int listener_fd, int fd,
                                                SliceBuffer* pending_data) = 0;

  virtual void ShutdownListeningFds() = 0;
};

class EventEngineSupportsFdExtension {
 public:
  virtual ~EventEngineSupportsFdExtension() = default;
  static absl::string_view EndpointExtensionName() {
    return "io.grpc.event_engine.extension.event_engine_supports_fd";
  }

  virtual std::unique_ptr<EventEngine::Endpoint> CreatePosixEndpointFromFd(
      int fd, const EndpointConfig& config,
      MemoryAllocator memory_allocator) = 0;

  virtual std::unique_ptr<EventEngine::Endpoint> CreateEndpointFromFd(
      int fd, const EndpointConfig& config) = 0;

  virtual EventEngine::ConnectionHandle CreateEndpointFromUnconnectedFd(
      int fd, EventEngine::OnConnectCallback on_connect,
      const EventEngine::ResolvedAddress& addr, const EndpointConfig& config,
      MemoryAllocator memory_allocator, EventEngine::Duration timeout) = 0;

  using PosixAcceptCallback = absl::AnyInvocable<void(
      int listener_fd, std::unique_ptr<EventEngine::Endpoint> endpoint,
      bool is_external, MemoryAllocator memory_allocator,
      SliceBuffer* pending_data)>;

  virtual absl::StatusOr<std::unique_ptr<EventEngine::Listener>>
  CreatePosixListener(
      PosixAcceptCallback on_accept,
      absl::AnyInvocable<void(absl::Status)> on_shutdown,
      const EndpointConfig& config,
      std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory) = 0;
};

}

#endif
