// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_IOCP_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_IOCP_H

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <grpc/event_engine/event_engine.h>

#include "absl/status/status.h"
#include "src/core/lib/event_engine/poller.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/lib/event_engine/windows/win_socket.h"

namespace grpc_event_engine::experimental {

class IOCP final : public Poller {
 public:
  explicit IOCP(ThreadPool* thread_pool) noexcept;
  ~IOCP() override;

  IOCP(const IOCP&) = delete;
  IOCP& operator=(const IOCP&) = delete;

  IOCP(IOCP&& other) = delete;
  IOCP& operator=(IOCP&& other) = delete;

  void Shutdown();
  WorkResult Work(EventEngine::Duration timeout,
                  absl::FunctionRef<void()> schedule_poll_again) override;
  void Kick() override;

  std::unique_ptr<WinSocket> Watch(SOCKET socket);

  static DWORD GetDefaultSocketFlags();

 private:

  static DWORD WSASocketFlagsInit();

  ThreadPool* thread_pool_;
  HANDLE iocp_handle_;
  OVERLAPPED kick_overlap_;
  ULONG kick_token_;
  std::atomic<int> outstanding_kicks_{0};
};

}

#endif

#endif
