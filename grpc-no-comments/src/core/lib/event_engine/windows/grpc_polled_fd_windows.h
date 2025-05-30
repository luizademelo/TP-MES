// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_GRPC_POLLED_FD_WINDOWS_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_GRPC_POLLED_FD_WINDOWS_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#if GRPC_ARES == 1 && defined(GRPC_WINDOWS_SOCKET_ARES_EV_DRIVER)

#include <ares.h>
#include <grpc/event_engine/event_engine.h>

#include <memory>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/grpc_polled_fd.h"
#include "src/core/lib/event_engine/windows/iocp.h"
#include "src/core/lib/event_engine/windows/win_socket.h"
#include "src/core/util/sync.h"

struct iovec;

namespace grpc_event_engine::experimental {

class GrpcPolledFdWindows;

class GrpcPolledFdFactoryWindows : public GrpcPolledFdFactory {
 public:
  explicit GrpcPolledFdFactoryWindows(IOCP* iocp);
  ~GrpcPolledFdFactoryWindows() override;

  void Initialize(grpc_core::Mutex* mutex, EventEngine* event_engine) override;
  std::unique_ptr<GrpcPolledFd> NewGrpcPolledFdLocked(
      ares_socket_t as) override;
  void ConfigureAresChannelLocked(ares_channel channel) override;

 private:
  friend class CustomSockFuncs;

  grpc_core::Mutex* mu_;

  IOCP* iocp_;

  EventEngine* event_engine_;
  std::map<SOCKET, std::unique_ptr<GrpcPolledFdWindows>> sockets_;
};

}

#endif

#endif
