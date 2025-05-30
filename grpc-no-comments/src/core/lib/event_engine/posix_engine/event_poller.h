// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_EVENT_POLLER_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_EVENT_POLLER_H
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <string>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/event_engine/forkable.h"
#include "src/core/lib/event_engine/poller.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_closure.h"

namespace grpc_event_engine::experimental {

class Scheduler {
 public:
  virtual void Run(experimental::EventEngine::Closure* closure) = 0;
  virtual void Run(absl::AnyInvocable<void()>) = 0;
  virtual ~Scheduler() = default;
};

class PosixEventPoller;

class EventHandle {
 public:
  virtual int WrappedFd() = 0;

  virtual void OrphanHandle(PosixEngineClosure* on_done, int* release_fd,
                            absl::string_view reason) = 0;

  virtual void ShutdownHandle(absl::Status why) = 0;

  virtual void NotifyOnRead(PosixEngineClosure* on_read) = 0;

  virtual void NotifyOnWrite(PosixEngineClosure* on_write) = 0;

  virtual void NotifyOnError(PosixEngineClosure* on_error) = 0;

  virtual void SetReadable() = 0;

  virtual void SetWritable() = 0;

  virtual void SetHasError() = 0;

  virtual bool IsHandleShutdown() = 0;

  virtual PosixEventPoller* Poller() = 0;
  virtual ~EventHandle() = default;
};

class PosixEventPoller : public grpc_event_engine::experimental::Poller,
                         public Forkable {
 public:

  virtual EventHandle* CreateHandle(int fd, absl::string_view name,
                                    bool track_err) = 0;
  virtual bool CanTrackErrors() const = 0;
  virtual std::string Name() = 0;

  virtual void Shutdown() = 0;
  ~PosixEventPoller() override = default;
};

}

#endif
