// Copyright 2022 gRPC authors.

#ifndef GRPC_TEST_CORE_EVENT_ENGINE_MOCK_EVENT_ENGINE_H
#define GRPC_TEST_CORE_EVENT_ENGINE_MOCK_EVENT_ENGINE_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>

#include <memory>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "gmock/gmock.h"

namespace grpc_event_engine {
namespace experimental {

class MockEventEngine : public EventEngine {
 public:
  MOCK_METHOD(
      absl::StatusOr<std::unique_ptr<Listener>>, CreateListener,
      (Listener::AcceptCallback on_accept,
       absl::AnyInvocable<void(absl::Status)> on_shutdown,
       const EndpointConfig& config,
       std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory));
  MOCK_METHOD(ConnectionHandle, Connect,
              (OnConnectCallback on_connect, const ResolvedAddress& addr,
               const EndpointConfig& args, MemoryAllocator memory_allocator,
               Duration timeout));
  MOCK_METHOD(bool, CancelConnect, (ConnectionHandle handle));
  MOCK_METHOD(bool, IsWorkerThread, ());
  MOCK_METHOD(absl::StatusOr<std::unique_ptr<DNSResolver>>, GetDNSResolver,
              (const DNSResolver::ResolverOptions& options));
  MOCK_METHOD(void, Run, (Closure * closure));
  MOCK_METHOD(void, Run, (absl::AnyInvocable<void()> closure));
  MOCK_METHOD(TaskHandle, RunAfter, (Duration when, Closure* closure));
  MOCK_METHOD(TaskHandle, RunAfter,
              (Duration when, absl::AnyInvocable<void()> closure));
  MOCK_METHOD(bool, Cancel, (TaskHandle handle));
};

}
}

#endif
