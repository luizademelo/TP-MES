// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_WINDOWS_ENDPOINT_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_WINDOWS_WINDOWS_ENDPOINT_H
#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <grpc/event_engine/event_engine.h>

#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/lib/event_engine/windows/win_socket.h"

namespace grpc_event_engine::experimental {

class WindowsEndpoint : public EventEngine::Endpoint {
 public:
  WindowsEndpoint(const EventEngine::ResolvedAddress& peer_address,
                  std::unique_ptr<WinSocket> socket,
                  MemoryAllocator&& allocator, const EndpointConfig& config,
                  ThreadPool* thread_pool, std::shared_ptr<EventEngine> engine);
  ~WindowsEndpoint() override;
  bool Read(absl::AnyInvocable<void(absl::Status)> on_read, SliceBuffer* buffer,
            ReadArgs args) override;
  bool Write(absl::AnyInvocable<void(absl::Status)> on_writable,
             SliceBuffer* data, WriteArgs args) override;
  const EventEngine::ResolvedAddress& GetPeerAddress() const override;
  const EventEngine::ResolvedAddress& GetLocalAddress() const override;
  std::vector<size_t> AllWriteMetrics() override { return {}; }
  std::optional<absl::string_view> GetMetricName(size_t) override {
    return std::nullopt;
  }
  std::optional<size_t> GetMetricKey(absl::string_view) override {
    return std::nullopt;
  }

 private:
  struct AsyncIOState;

  class HandleReadClosure : public EventEngine::Closure {
   public:
    void Run() override;
    void Prime(std::shared_ptr<AsyncIOState> io_state, SliceBuffer* buffer,
               absl::AnyInvocable<void(absl::Status)> cb);

    [[nodiscard]] absl::AnyInvocable<void(absl::Status)>
    ResetAndReturnCallback();

    bool MaybeFinishIfDataHasAlreadyBeenRead();

    void DonateSpareSlices(SliceBuffer* buffer);

   private:
    std::shared_ptr<AsyncIOState> io_state_;
    absl::AnyInvocable<void(absl::Status)> cb_;
    SliceBuffer* buffer_ = nullptr;
    SliceBuffer last_read_buffer_;
  };

  class HandleWriteClosure : public EventEngine::Closure {
   public:
    void Run() override;
    void Prime(std::shared_ptr<AsyncIOState> io_state, SliceBuffer* buffer,
               absl::AnyInvocable<void(absl::Status)> cb);

    [[nodiscard]] absl::AnyInvocable<void(absl::Status)>
    ResetAndReturnCallback();

   private:
    std::shared_ptr<AsyncIOState> io_state_;
    absl::AnyInvocable<void(absl::Status)> cb_;
    SliceBuffer* buffer_ = nullptr;
  };

  struct AsyncIOState {
    AsyncIOState(WindowsEndpoint* endpoint, std::unique_ptr<WinSocket> socket,
                 std::shared_ptr<EventEngine> engine, ThreadPool* thread_pool);
    ~AsyncIOState();

    void DoTcpRead(SliceBuffer* buffer);

    WindowsEndpoint* const endpoint;
    std::unique_ptr<WinSocket> socket;
    HandleReadClosure handle_read_event;
    HandleWriteClosure handle_write_event;
    std::shared_ptr<EventEngine> engine;
    ThreadPool* thread_pool;
  };

  EventEngine::ResolvedAddress peer_address_;
  std::string peer_address_string_;
  EventEngine::ResolvedAddress local_address_;
  std::string local_address_string_;
  MemoryAllocator allocator_;
  std::shared_ptr<AsyncIOState> io_state_;
};

}

#endif

#endif
