// Copyright 2025 gRPC authors.

#ifndef GRPC_TEST_CORE_EVENT_ENGINE_UTIL_DELEGATING_EVENT_ENGINE_H
#define GRPC_TEST_CORE_EVENT_ENGINE_UTIL_DELEGATING_EVENT_ENGINE_H

#include <grpc/event_engine/event_engine.h>

namespace grpc_event_engine::experimental {

class DelegatingEventEngine : public EventEngine {
 public:
  DelegatingEventEngine() : wrapped_engine_(CreateEventEngine()) {}
  explicit DelegatingEventEngine(std::shared_ptr<EventEngine> engine)
      : wrapped_engine_(std::move(engine)) {}
  ~DelegatingEventEngine() override = default;

  void Run(Closure* closure) override {
    run_count_++;
    wrapped_engine_->Run(closure);
  }

  void Run(absl::AnyInvocable<void()> closure) override {
    run_count_++;
    wrapped_engine_->Run(std::move(closure));
  }

  int get_run_count() { return run_count_.load(); }

  absl::StatusOr<std::unique_ptr<Listener>> CreateListener(
      Listener::AcceptCallback on_accept,
      absl::AnyInvocable<void(absl::Status)> on_shutdown,
      const EndpointConfig& config,
      std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory)
      override {
    return wrapped_engine_->CreateListener(std::move(on_accept),
                                           std::move(on_shutdown), config,
                                           std::move(memory_allocator_factory));
  }
  ConnectionHandle Connect(OnConnectCallback on_connect,
                           const ResolvedAddress& addr,
                           const EndpointConfig& args,
                           MemoryAllocator memory_allocator,
                           Duration timeout) override {
    return wrapped_engine_->Connect(std::move(on_connect), addr, args,
                                    std::move(memory_allocator), timeout);
  }
  bool CancelConnect(ConnectionHandle handle) override {
    return wrapped_engine_->CancelConnect(handle);
  }

  bool IsWorkerThread() override { return wrapped_engine_->IsWorkerThread(); }

  absl::StatusOr<std::unique_ptr<DNSResolver>> GetDNSResolver(
      const DNSResolver::ResolverOptions& options) override {
    return wrapped_engine_->GetDNSResolver(options);
  }

  TaskHandle RunAfter(Duration when, Closure* closure) override {
    return wrapped_engine_->RunAfter(when, closure);
  }

  TaskHandle RunAfter(Duration when,
                      absl::AnyInvocable<void()> closure) override {
    return wrapped_engine_->RunAfter(when, std::move(closure));
  }
  bool Cancel(TaskHandle handle) override {
    return wrapped_engine_->Cancel(handle);
  }

  std::shared_ptr<EventEngine> wrapped_engine() { return wrapped_engine_; }

 private:
  std::shared_ptr<EventEngine> wrapped_engine_;
  std::atomic<int> run_count_{0};
};

}

#endif
