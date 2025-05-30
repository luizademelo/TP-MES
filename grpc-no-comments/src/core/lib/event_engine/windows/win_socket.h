// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_WIN_SOCKET_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_WIN_SOCKET_H

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <grpc/event_engine/event_engine.h>

#include "absl/base/thread_annotations.h"
#include "absl/functional/any_invocable.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/sync.h"

namespace grpc_event_engine::experimental {

class WinSocket {
 public:
  struct OverlappedResult {
    int wsa_error;
    DWORD bytes_transferred;
    absl::Status error_status;
  };

  class OpState {
   public:
    explicit OpState(WinSocket* win_socket) noexcept;

    void SetReady();

    void SetResult(int wsa_error, DWORD bytes, absl::string_view context);

    void SetErrorStatus(absl::Status error_status);

    void GetOverlappedResult();

    void GetOverlappedResult(SOCKET sock);

    const OverlappedResult& result() const { return result_; }

    LPOVERLAPPED overlapped() { return &overlapped_; }

   private:
    friend class WinSocket;

    OVERLAPPED overlapped_;
    WinSocket* win_socket_ = nullptr;
    EventEngine::Closure* closure_ = nullptr;
    OverlappedResult result_;
  };

  WinSocket(SOCKET socket, ThreadPool* thread_pool) noexcept;
  ~WinSocket();

  void NotifyOnRead(EventEngine::Closure* on_read);
  void NotifyOnWrite(EventEngine::Closure* on_write);

  void UnregisterReadCallback();
  void UnregisterWriteCallback();

  bool IsShutdown();

  void Shutdown();
  void Shutdown(const grpc_core::DebugLocation& location,
                absl::string_view reason);

  OpState* GetOpInfoForOverlapped(OVERLAPPED* overlapped);

  OpState* read_info() { return &read_info_; }
  OpState* write_info() { return &write_info_; }

  SOCKET raw_socket();

 private:
  void NotifyOnReady(OpState& info, EventEngine::Closure* closure);

  SOCKET socket_;
  std::atomic<bool> is_shutdown_{false};
  ThreadPool* thread_pool_;

  OpState read_info_;
  OpState write_info_;
};

absl::Status PrepareSocket(SOCKET sock);

absl::Status SetSocketNonBlock(SOCKET sock);

absl::StatusOr<EventEngine::ResolvedAddress> SocketToAddress(SOCKET sock);

}

#endif

#endif
