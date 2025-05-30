// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_GRPC_POLLED_FD_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_GRPC_POLLED_FD_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>

#if GRPC_ARES == 1

#include <ares.h>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "src/core/util/sync.h"

namespace grpc_event_engine::experimental {

class GrpcPolledFd {
 public:
  virtual ~GrpcPolledFd() {}

  virtual void RegisterForOnReadableLocked(
      absl::AnyInvocable<void(absl::Status)> read_closure) = 0;

  virtual void RegisterForOnWriteableLocked(
      absl::AnyInvocable<void(absl::Status)> write_closure) = 0;

  virtual bool IsFdStillReadableLocked() = 0;

  GRPC_MUST_USE_RESULT virtual bool ShutdownLocked(absl::Status error) = 0;

  virtual ares_socket_t GetWrappedAresSocketLocked() = 0;

  virtual const char* GetName() const = 0;
};

class GrpcPolledFdFactory {
 public:
  virtual ~GrpcPolledFdFactory() {}

  virtual void Initialize(grpc_core::Mutex* mutex,
                          EventEngine* event_engine) = 0;

  virtual std::unique_ptr<GrpcPolledFd> NewGrpcPolledFdLocked(
      ares_socket_t as) = 0;

  virtual void ConfigureAresChannelLocked(ares_channel channel) = 0;
};

}

#endif
#endif
