// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_THREADY_EVENT_ENGINE_THREADY_EVENT_ENGINE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_THREADY_EVENT_ENGINE_THREADY_EVENT_ENGINE_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_event_engine::experimental {

class ThreadyEventEngine final : public EventEngine {
 public:
  explicit ThreadyEventEngine(std::shared_ptr<EventEngine> impl)
      : impl_(std::move(impl)) {}

  absl::StatusOr<std::unique_ptr<Listener>> CreateListener(
      Listener::AcceptCallback on_accept,
      absl::AnyInvocable<void(absl::Status)> on_shutdown,
      const EndpointConfig& config,
      std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory)
      override;

  ConnectionHandle Connect(OnConnectCallback on_connect,
                           const ResolvedAddress& addr,
                           const EndpointConfig& args,
                           MemoryAllocator memory_allocator,
                           Duration timeout) override;

  bool CancelConnect(ConnectionHandle handle) override;

  bool IsWorkerThread() override;

  absl::StatusOr<std::unique_ptr<DNSResolver>> GetDNSResolver(
      const DNSResolver::ResolverOptions& options) override;

  void Run(Closure* closure) override;
  void Run(absl::AnyInvocable<void()> closure) override;

  TaskHandle RunAfter(Duration when, Closure* closure) override;
  TaskHandle RunAfter(Duration when,
                      absl::AnyInvocable<void()> closure) override;

  bool Cancel(TaskHandle handle) override;

 private:
  class ThreadyDNSResolver final : public DNSResolver {
   public:
    ThreadyDNSResolver(std::unique_ptr<DNSResolver> impl,
                       std::shared_ptr<ThreadyEventEngine> engine)
        : impl_(std::move(impl)), engine_(std::move(engine)) {}
    void LookupHostname(LookupHostnameCallback on_resolve,
                        absl::string_view name,
                        absl::string_view default_port) override;
    void LookupSRV(LookupSRVCallback on_resolve,
                   absl::string_view name) override;
    void LookupTXT(LookupTXTCallback on_resolve,
                   absl::string_view name) override;

   private:
    std::unique_ptr<DNSResolver> impl_;
    std::shared_ptr<ThreadyEventEngine> engine_;
  };

  void Asynchronously(absl::AnyInvocable<void()> fn);

  std::shared_ptr<EventEngine> impl_;
};

}

#endif
