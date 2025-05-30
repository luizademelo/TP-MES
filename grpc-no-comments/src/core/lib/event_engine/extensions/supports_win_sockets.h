// Copyright 2025 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_SUPPORTS_WIN_SOCKETS_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_SUPPORTS_WIN_SOCKETS_H

#include <grpc/support/port_platform.h>

#ifdef GRPC_WINSOCK_SOCKET
#include <grpc/event_engine/event_engine.h>

#include "absl/functional/any_invocable.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_event_engine::experimental {

class EventEngineWindowsSocketSupport {
 public:
  virtual ~EventEngineWindowsSocketSupport() = default;
  static absl::string_view EndpointExtensionName() {
    return "io.grpc.event_engine.extension.event_engine_supports_win_sockets";
  }

  virtual std::unique_ptr<EventEngine::Endpoint> CreateEndpointFromWinSocket(
      SOCKET socket, const EndpointConfig& config) = 0;
};

}

#endif

#endif
