// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_WINDOWS_LISTENER_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_WINDOWS_LISTENER_H

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>

#include <list>

#include "absl/base/thread_annotations.h"
#include "absl/status/statusor.h"
#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/extensions/iomgr_compatible.h"
#include "src/core/lib/event_engine/query_extensions.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/lib/event_engine/windows/iocp.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/sync.h"

#ifdef GRPC_HAVE_UNIX_SOCKET

#include <ws2def.h>
#include <afunix.h>

#endif

namespace grpc_event_engine::experimental {

class WindowsEventEngineListener
    : public ExtendedType<
          EventEngine::Listener,
          grpc_event_engine::experimental::IomgrCompatibleListener> {
 public:
  WindowsEventEngineListener(
      IOCP* iocp, AcceptCallback accept_cb,
      absl::AnyInvocable<void(absl::Status)> on_shutdown,
      std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory,
      std::shared_ptr<EventEngine> engine, ThreadPool* thread_pool_,
      const EndpointConfig& config);
  ~WindowsEventEngineListener() override;
  absl::StatusOr<int> Bind(const EventEngine::ResolvedAddress& addr) override;
  absl::Status Start() override;

  void Shutdown() override;

 private:

  class SinglePortSocketListener {
   public:
    ~SinglePortSocketListener();

    static absl::StatusOr<std::unique_ptr<SinglePortSocketListener>> Create(
        WindowsEventEngineListener* listener, SOCKET sock,
        EventEngine::ResolvedAddress addr);

    absl::Status Start();
    absl::Status StartLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(io_state_->mu);

    EventEngine::ResolvedAddress listener_sockname() {
      return listener_sockname_;
    };
    int port() { return port_; }

   private:
    struct AsyncIOState;

    class OnAcceptCallbackWrapper : public EventEngine::Closure {
     public:
      void Run() override;
      void Prime(std::shared_ptr<AsyncIOState> io_state);

     private:
      std::shared_ptr<AsyncIOState> io_state_;
    };

    struct AsyncIOState {
      AsyncIOState(SinglePortSocketListener* port_listener,
                   std::unique_ptr<WinSocket> listener_socket);
      ~AsyncIOState();
      SinglePortSocketListener* const port_listener;
      OnAcceptCallbackWrapper on_accept_cb;

      grpc_core::Mutex mu;

      SOCKET accept_socket ABSL_GUARDED_BY(mu) = INVALID_SOCKET;

      std::unique_ptr<WinSocket> listener_socket ABSL_GUARDED_BY(mu);
    };

    SinglePortSocketListener(WindowsEventEngineListener* listener,
                             LPFN_ACCEPTEX AcceptEx,
                             std::unique_ptr<WinSocket> listener_socket,
                             int port, EventEngine::ResolvedAddress hostbyname);

    struct PrepareListenerSocketResult {
      int port;
      EventEngine::ResolvedAddress hostbyname;
    };
    static absl::StatusOr<PrepareListenerSocketResult> PrepareListenerSocket(
        SOCKET sock, const EventEngine::ResolvedAddress& addr);

    void OnAcceptCallbackLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(io_state_->mu);

    LPFN_ACCEPTEX AcceptEx;

#ifdef GRPC_HAVE_UNIX_SOCKET

    uint8_t addresses_[(sizeof(sockaddr_un) + 16) * 2] = {};
#else
    uint8_t addresses_[(sizeof(sockaddr_in6) + 16) * 2] = {};
#endif

    WindowsEventEngineListener* listener_;

    std::shared_ptr<AsyncIOState> io_state_;

    int port_;
    EventEngine::ResolvedAddress listener_sockname_;
  };
  absl::StatusOr<SinglePortSocketListener*> AddSinglePortSocketListener(
      SOCKET sock, EventEngine::ResolvedAddress addr);

  IOCP* const iocp_;
  const EndpointConfig& config_;
  std::shared_ptr<EventEngine> engine_;
  ThreadPool* thread_pool_;
  const std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory_;
  AcceptCallback accept_cb_;
  absl::AnyInvocable<void(absl::Status)> on_shutdown_;
  std::atomic<bool> started_{false};
  grpc_core::Mutex port_listeners_mu_;
  std::list<std::unique_ptr<SinglePortSocketListener>> port_listeners_
      ABSL_GUARDED_BY(port_listeners_mu_);
  bool listeners_shutdown_ ABSL_GUARDED_BY(port_listeners_mu_) = false;
};

}

#endif

#endif
