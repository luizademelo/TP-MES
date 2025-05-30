// Copyright 2022 gRPC authors.

#ifndef GRPC_TEST_CORE_EVENT_ENGINE_EVENT_ENGINE_TEST_UTILS_H
#define GRPC_TEST_CORE_EVENT_ENGINE_EVENT_ENGINE_TEST_UTILS_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/slice_buffer.h>

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/util/notification.h"
#include "src/core/util/sync.h"

using EventEngineFactory = std::function<
    std::unique_ptr<grpc_event_engine::experimental::EventEngine>()>;

namespace grpc_event_engine {
namespace experimental {

std::string ExtractSliceBufferIntoString(SliceBuffer* buf);

std::string GetNextSendMessage();

absl::Status SendValidatePayload(absl::string_view data,
                                 EventEngine::Endpoint* send_endpoint,
                                 EventEngine::Endpoint* receive_endpoint);

class ConnectionManager {
 public:
  ConnectionManager(std::unique_ptr<EventEngine> test_event_engine,
                    std::unique_ptr<EventEngine> oracle_event_engine)
      : memory_quota_(std::make_unique<grpc_core::MemoryQuota>("foo")),
        test_event_engine_(std::move(test_event_engine)),
        oracle_event_engine_(std::move(oracle_event_engine)) {}
  ~ConnectionManager() = default;

  absl::Status BindAndStartListener(const std::vector<std::string>& addrs,
                                    bool listener_type_oracle = true);

  absl::StatusOr<std::tuple<std::unique_ptr<EventEngine::Endpoint>,
                            std::unique_ptr<EventEngine::Endpoint>>>
  CreateConnection(std::string target_addr, EventEngine::Duration timeout,
                   bool client_type_oracle);

 private:
  class Connection {
   public:
    Connection() = default;
    ~Connection() = default;

    void SetClientEndpoint(
        std::unique_ptr<EventEngine::Endpoint>&& client_endpoint) {
      client_endpoint_ = std::move(client_endpoint);
      client_signal_.Notify();
    }
    void SetServerEndpoint(
        std::unique_ptr<EventEngine::Endpoint>&& server_endpoint) {
      server_endpoint_ = std::move(server_endpoint);
      server_signal_.Notify();
    }
    std::unique_ptr<EventEngine::Endpoint> GetClientEndpoint() {
      auto client_endpoint = std::move(client_endpoint_);
      client_endpoint_.reset();
      return client_endpoint;
    }
    std::unique_ptr<EventEngine::Endpoint> GetServerEndpoint() {
      auto server_endpoint = std::move(server_endpoint_);
      server_endpoint_.reset();
      return server_endpoint;
    }

   private:
    std::unique_ptr<EventEngine::Endpoint> client_endpoint_;
    std::unique_ptr<EventEngine::Endpoint> server_endpoint_;
    grpc_core::Notification client_signal_;
    grpc_core::Notification server_signal_;
  };

  grpc_core::Mutex mu_;
  std::unique_ptr<grpc_core::MemoryQuota> memory_quota_;
  int num_processed_connections_ = 0;
  Connection last_in_progress_connection_;
  std::map<std::string, std::shared_ptr<EventEngine::Listener>> listeners_;
  std::unique_ptr<EventEngine> test_event_engine_;
  std::unique_ptr<EventEngine> oracle_event_engine_;
};

void AppendStringToSliceBuffer(SliceBuffer* buf, absl::string_view data);

class NotifyOnDelete {
 public:
  explicit NotifyOnDelete(grpc_core::Notification* signal) : signal_(signal) {}
  NotifyOnDelete(const NotifyOnDelete&) = delete;
  NotifyOnDelete& operator=(const NotifyOnDelete&) = delete;
  NotifyOnDelete(NotifyOnDelete&& other) noexcept {
    signal_ = other.signal_;
    other.signal_ = nullptr;
  }
  NotifyOnDelete& operator=(NotifyOnDelete&& other) noexcept {
    signal_ = other.signal_;
    other.signal_ = nullptr;
    return *this;
  }
  ~NotifyOnDelete() {
    if (signal_ != nullptr) {
      signal_->Notify();
    }
  }

 private:
  grpc_core::Notification* signal_;
};

class ThreadedNoopEndpoint : public EventEngine::Endpoint {
 public:
  explicit ThreadedNoopEndpoint(grpc_core::Notification* destroyed)
      : state_(std::make_shared<EndpointState>(destroyed)) {}
  ~ThreadedNoopEndpoint() override {
    std::thread deleter([state = state_]() {
      CleanupThread(state->read);
      CleanupThread(state->write);
    });
    deleter.detach();
  }

  bool Read(absl::AnyInvocable<void(absl::Status)> on_read, SliceBuffer* buffer,
            ReadArgs ) override {
    buffer->Clear();
    CleanupThread(state_->read);
    state_->read = new std::thread([cb = std::move(on_read)]() mutable {
      cb(absl::UnknownError("test"));
    });
    return false;
  }

  bool Write(absl::AnyInvocable<void(absl::Status)> on_writable,
             SliceBuffer* data, WriteArgs ) override {
    data->Clear();
    CleanupThread(state_->write);
    state_->write = new std::thread([cb = std::move(on_writable)]() mutable {
      cb(absl::UnknownError("test"));
    });
    return false;
  }

  const EventEngine::ResolvedAddress& GetPeerAddress() const override {
    return peer_;
  }

  const EventEngine::ResolvedAddress& GetLocalAddress() const override {
    return local_;
  }

  std::vector<size_t> AllWriteMetrics() override { return {}; }
  std::optional<absl::string_view> GetMetricName(size_t) override {
    return std::nullopt;
  }
  std::optional<size_t> GetMetricKey(absl::string_view) override {
    return std::nullopt;
  }

 private:
  struct EndpointState {
    explicit EndpointState(grpc_core::Notification* deleter)
        : delete_notifier_(deleter) {}
    std::thread* read = nullptr;
    std::thread* write = nullptr;
    NotifyOnDelete delete_notifier_;
  };

  static void CleanupThread(std::thread* thd) {
    if (thd != nullptr) {
      thd->join();
      delete thd;
    }
  }

  std::shared_ptr<EndpointState> state_;
  EventEngine::ResolvedAddress peer_;
  EventEngine::ResolvedAddress local_;
};

bool IsSaneTimerEnvironment();

}
}

#endif
