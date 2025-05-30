// Copyright 2022 The gRPC Authors

#ifndef GRPC_TEST_CORE_EVENT_ENGINE_UTIL_ABORTING_EVENT_ENGINE_H
#define GRPC_TEST_CORE_EVENT_ENGINE_UTIL_ABORTING_EVENT_ENGINE_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <memory>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace grpc_event_engine {
namespace experimental {

class AbortingEventEngine : public EventEngine {
  ConnectionHandle Connect(OnConnectCallback ,
                           const ResolvedAddress& ,
                           const EndpointConfig& ,
                           MemoryAllocator ,
                           Duration ) override {
    abort();
  };
  bool CancelConnect(ConnectionHandle ) override { abort(); }
  absl::StatusOr<std::unique_ptr<Listener>> CreateListener(
      Listener::AcceptCallback ,
      absl::AnyInvocable<void(absl::Status)> ,
      const EndpointConfig& ,
      std::unique_ptr<MemoryAllocatorFactory> )
      override {
    abort();
  };
  bool IsWorkerThread() override { abort(); }
  absl::StatusOr<std::unique_ptr<DNSResolver>> GetDNSResolver(
      const DNSResolver::ResolverOptions& ) override {
    abort();
  }
  void Run(Closure* ) override { abort(); }
  void Run(absl::AnyInvocable<void()> ) override { abort(); }
  TaskHandle RunAfter(Duration , Closure* ) override {
    abort();
  }
  TaskHandle RunAfter(Duration ,
                      absl::AnyInvocable<void()> ) override {
    abort();
  }
  bool Cancel(TaskHandle ) override { abort(); }
};

}
}

#endif
