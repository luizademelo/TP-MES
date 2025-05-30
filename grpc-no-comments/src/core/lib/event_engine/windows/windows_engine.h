// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_WINDOWS_ENGINE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_WINDOWS_ENGINE_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GPR_WINDOWS

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/event_engine/slice_buffer.h>

#include <memory>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/event_engine/ares_resolver.h"
#include "src/core/lib/event_engine/extensions/supports_win_sockets.h"
#include "src/core/lib/event_engine/handle_containers.h"
#include "src/core/lib/event_engine/posix_engine/timer_manager.h"
#include "src/core/lib/event_engine/query_extensions.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/lib/event_engine/windows/iocp.h"
#include "src/core/lib/event_engine/windows/windows_endpoint.h"
#include "src/core/lib/surface/init_internally.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_event_engine::experimental {

class WindowsEventEngine
    : public grpc_core::KeepsGrpcInitialized,
      public ExtendedType<EventEngine, EventEngineWindowsSocketSupport> {
 public:
  class WindowsDNSResolver : public EventEngine::DNSResolver {
   public:
    WindowsDNSResolver() = delete;
#if GRPC_ARES == 1 && defined(GRPC_WINDOWS_SOCKET_ARES_EV_DRIVER)
    explicit WindowsDNSResolver(
        grpc_core::OrphanablePtr<AresResolver> ares_resolver);
#endif
    void LookupHostname(LookupHostnameCallback on_resolve,
                        absl::string_view name,
                        absl::string_view default_port) override;
    void LookupSRV(LookupSRVCallback on_resolve,
                   absl::string_view name) override;
    void LookupTXT(LookupTXTCallback on_resolve,
                   absl::string_view name) override;

#if GRPC_ARES == 1 && defined(GRPC_WINDOWS_SOCKET_ARES_EV_DRIVER)
   private:
    grpc_core::OrphanablePtr<AresResolver> ares_resolver_;
#endif
  };

  WindowsEventEngine();
  ~WindowsEventEngine() override;

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

  std::unique_ptr<EventEngine::Endpoint> CreateEndpointFromWinSocket(
      SOCKET socket, const EndpointConfig& config) override;

  ThreadPool* thread_pool() { return thread_pool_.get(); }
  IOCP* poller() { return &iocp_; }

 private:

  class ConnectionState : public std::enable_shared_from_this<ConnectionState> {
   public:
    ConnectionState(std::shared_ptr<WindowsEventEngine> engine,
                    std::unique_ptr<WinSocket> socket,
                    EventEngine::ResolvedAddress address,
                    MemoryAllocator allocator,
                    EventEngine::OnConnectCallback on_connect_user_callback);

    void Start(Duration timeout) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

    OnConnectCallback TakeCallback() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

    std::unique_ptr<WindowsEndpoint> FinishConnectingAndMakeEndpoint(
        ThreadPool* thread_pool) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

    void AbortOnConnect() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

    void AbortDeadlineTimer() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

    WinSocket* socket() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
      return socket_.get();
    }

    const EventEngine::ConnectionHandle& connection_handle() {
      return connection_handle_;
    }
    const EventEngine::TaskHandle& timer_handle() { return timer_handle_; }

    grpc_core::Mutex& mu() ABSL_LOCK_RETURNED(mu_) { return mu_; }

   private:

    friend std::ostream& operator<<(std::ostream& out,
                                    const ConnectionState& connection_state)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(connection_state.mu_);

    class OnConnectedCallback : public EventEngine::Closure {
     public:
      OnConnectedCallback(WindowsEventEngine* engine,
                          std::shared_ptr<ConnectionState> connection_state)
          : engine_(engine), connection_state_(std::move(connection_state)) {}

      void Run() override;

     private:
      WindowsEventEngine* engine_;
      std::shared_ptr<ConnectionState> connection_state_;
    };

    class DeadlineTimerCallback : public EventEngine::Closure {
     public:
      DeadlineTimerCallback(WindowsEventEngine* engine,
                            std::shared_ptr<ConnectionState> connection_state)
          : engine_(engine), connection_state_(std::move(connection_state)) {}

      void Run() override;

     private:
      WindowsEventEngine* engine_;
      std::shared_ptr<ConnectionState> connection_state_;
    };

    grpc_core::Mutex mu_
        ABSL_ACQUIRED_BEFORE(WindowsEventEngine::connection_mu_);

    std::unique_ptr<WinSocket> socket_ ABSL_GUARDED_BY(mu_);
    EventEngine::ResolvedAddress address_ ABSL_GUARDED_BY(mu_);
    MemoryAllocator allocator_ ABSL_GUARDED_BY(mu_);
    EventEngine::OnConnectCallback on_connect_user_callback_
        ABSL_GUARDED_BY(mu_);

    std::shared_ptr<WindowsEventEngine> engine_ ABSL_GUARDED_BY(mu_);

    std::unique_ptr<OnConnectedCallback> on_connected_cb_ ABSL_GUARDED_BY(mu_);
    std::unique_ptr<DeadlineTimerCallback> deadline_timer_cb_
        ABSL_GUARDED_BY(mu_);

    EventEngine::ConnectionHandle connection_handle_ ABSL_GUARDED_BY(mu_) =
        EventEngine::ConnectionHandle::kInvalid;
    EventEngine::TaskHandle timer_handle_ ABSL_GUARDED_BY(mu_) =
        EventEngine::TaskHandle::kInvalid;

    bool has_run_ ABSL_GUARDED_BY(mu_) = false;
  };

  friend std::ostream& operator<<(std::ostream& out,
                                  const ConnectionState& connection_state);

  struct TimerClosure;

  class IOCPWorkClosure : public EventEngine::Closure {
   public:
    explicit IOCPWorkClosure(ThreadPool* thread_pool, IOCP* iocp);
    void Run() override;
    void WaitForShutdown();

   private:
    std::atomic<int> workers_{1};
    grpc_core::Notification done_signal_;
    ThreadPool* thread_pool_;
    IOCP* iocp_;
  };

  void OnConnectCompleted(std::shared_ptr<ConnectionState> state);

  void OnDeadlineTimerFired(std::shared_ptr<ConnectionState> state);

  bool CancelConnectFromDeadlineTimer(ConnectionState* connection_state)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(connection_state->mu());

  bool CancelConnectInternalStateLocked(ConnectionState* connection_state)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(connection_state->mu());

  EventEngine::TaskHandle RunAfterInternal(Duration when,
                                           absl::AnyInvocable<void()> cb);
  grpc_core::Mutex task_mu_;
  TaskHandleSet known_handles_ ABSL_GUARDED_BY(task_mu_);
  grpc_core::Mutex connection_mu_;
  grpc_core::CondVar connection_cv_;
  ConnectionHandleSet known_connection_handles_ ABSL_GUARDED_BY(connection_mu_);
  std::atomic<intptr_t> aba_token_{0};

  std::shared_ptr<ThreadPool> thread_pool_;
  IOCP iocp_;
  TimerManager timer_manager_;
  IOCPWorkClosure iocp_worker_;
};

}

#endif

#endif
