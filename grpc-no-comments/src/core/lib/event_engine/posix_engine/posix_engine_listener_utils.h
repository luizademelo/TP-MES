// Copyright 2022 gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_POSIX_ENGINE_LISTENER_UTILS_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_POSIX_ENGINE_LISTENER_UTILS_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include "absl/status/statusor.h"
#include "src/core/lib/event_engine/posix_engine/tcp_socket_utils.h"

namespace grpc_event_engine::experimental {

class ListenerSocketsContainer {
 public:
  struct ListenerSocket {

    PosixSocketWrapper sock;

    int port;

    bool zero_copy_enabled;

    grpc_event_engine::experimental::EventEngine::ResolvedAddress addr;

    PosixSocketWrapper::DSMode dsmode;
  };

  virtual void Append(ListenerSocket socket) = 0;

  virtual absl::StatusOr<ListenerSocket> Find(
      const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
          addr) = 0;

  virtual ~ListenerSocketsContainer() = default;
};

absl::StatusOr<ListenerSocketsContainer::ListenerSocket>
CreateAndPrepareListenerSocket(
    const PosixTcpOptions& options,
    const grpc_event_engine::experimental::EventEngine::ResolvedAddress& addr);

absl::StatusOr<int> ListenerContainerAddWildcardAddresses(
    ListenerSocketsContainer& listener_sockets, const PosixTcpOptions& options,
    int requested_port);

absl::StatusOr<int> ListenerContainerAddAllLocalAddresses(
    ListenerSocketsContainer& listener_sockets, const PosixTcpOptions& options,
    int requested_port);

bool IsSockAddrLinkLocal(const EventEngine::ResolvedAddress* resolved_addr);

}

#endif
