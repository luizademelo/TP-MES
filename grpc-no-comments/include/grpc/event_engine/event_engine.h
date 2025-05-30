// Copyright 2021 The gRPC Authors

#ifndef GRPC_EVENT_ENGINE_EVENT_ENGINE_H
#define GRPC_EVENT_ENGINE_EVENT_ENGINE_H

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/extensible.h>
#include <grpc/event_engine/internal/write_event.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/event_engine/port.h>
#include <grpc/event_engine/slice_buffer.h>
#include <grpc/support/port_platform.h>

#include <bitset>
#include <initializer_list>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace grpc_event_engine {
namespace experimental {

class EventEngine : public std::enable_shared_from_this<EventEngine>,
                    public Extensible {
 public:

  using Duration = std::chrono::duration<int64_t, std::nano>;

  class Closure {
   public:
    Closure() = default;

    Closure(const Closure&) = delete;
    Closure& operator=(const Closure&) = delete;

    virtual ~Closure() = default;

    virtual void Run() = 0;
  };

  struct TaskHandle {
    intptr_t keys[2];
    static const GRPC_DLL TaskHandle kInvalid;
  };

  struct ConnectionHandle {
    intptr_t keys[2];
    static const GRPC_DLL ConnectionHandle kInvalid;
  };

  class ResolvedAddress {
   public:
    static constexpr socklen_t MAX_SIZE_BYTES = 128;

    ResolvedAddress(const sockaddr* address, socklen_t size);
    ResolvedAddress() = default;
    ResolvedAddress(const ResolvedAddress&) = default;
    const struct sockaddr* address() const;
    socklen_t size() const;

   private:
    char address_[MAX_SIZE_BYTES] = {};
    socklen_t size_ = 0;
  };

  class Endpoint : public Extensible {
   public:

    virtual ~Endpoint() = default;

    class ReadArgs final {
     public:
      ReadArgs() = default;
      ReadArgs(const ReadArgs&) = delete;
      ReadArgs& operator=(const ReadArgs&) = delete;
      ReadArgs(ReadArgs&&) = default;
      ReadArgs& operator=(ReadArgs&&) = default;

      void set_read_hint_bytes(int64_t read_hint_bytes) {
        read_hint_bytes_ = read_hint_bytes;
      }
      int64_t read_hint_bytes() const { return read_hint_bytes_; }

     private:
      int64_t read_hint_bytes_ = 1;
    };

    virtual bool Read(absl::AnyInvocable<void(absl::Status)> on_read,
                      SliceBuffer* buffer, ReadArgs args) = 0;

    using WriteEvent = ::grpc_event_engine::experimental::internal::WriteEvent;

    struct WriteMetric {
      size_t key;
      int64_t value;
    };
    using WriteEventCallback = absl::AnyInvocable<void(
        WriteEvent, absl::Time, std::vector<WriteMetric>) const>;

    using WriteEventSet = std::bitset<static_cast<int>(WriteEvent::kCount)>;

    class WriteEventSink final {
     public:
      WriteEventSink(absl::Span<const size_t> requested_metrics,
                     std::initializer_list<WriteEvent> requested_events,
                     WriteEventCallback on_event)
          : requested_metrics_(requested_metrics),
            on_event_(std::move(on_event)) {
        for (auto event : requested_events) {
          requested_events_mask_.set(static_cast<int>(event));
        }
      }

      absl::Span<const size_t> requested_metrics() const {
        return requested_metrics_;
      }

      bool requested_event(WriteEvent event) const {
        return requested_events_mask_.test(static_cast<int>(event));
      }

      WriteEventSet requested_events_mask() const {
        return requested_events_mask_;
      }

      WriteEventCallback TakeEventCallback() { return std::move(on_event_); }

     private:
      absl::Span<const size_t> requested_metrics_;
      WriteEventSet requested_events_mask_;

      WriteEventCallback on_event_;
    };

    class WriteArgs final {
     public:
      WriteArgs() = default;
      WriteArgs(const WriteArgs&) = delete;
      WriteArgs& operator=(const WriteArgs&) = delete;
      WriteArgs(WriteArgs&&) = default;
      WriteArgs& operator=(WriteArgs&&) = default;

      std::optional<WriteEventSink> TakeMetricsSink() {
        auto sink = std::move(metrics_sink_);
        metrics_sink_.reset();
        return sink;
      }

      bool has_metrics_sink() const { return metrics_sink_.has_value(); }

      void set_metrics_sink(WriteEventSink sink) {
        metrics_sink_ = std::move(sink);
      }

      void* GetDeprecatedAndDiscouragedGoogleSpecificPointer() {
        return google_specific_;
      }

      void SetDeprecatedAndDiscouragedGoogleSpecificPointer(void* pointer) {
        google_specific_ = pointer;
      }

      int64_t max_frame_size() const { return max_frame_size_; }

      void set_max_frame_size(int64_t max_frame_size) {
        max_frame_size_ = max_frame_size;
      }

     private:
      std::optional<WriteEventSink> metrics_sink_;
      void* google_specific_ = nullptr;
      int64_t max_frame_size_ = 1024 * 1024;
    };

    virtual bool Write(absl::AnyInvocable<void(absl::Status)> on_writable,
                       SliceBuffer* data, WriteArgs args) = 0;

    virtual const ResolvedAddress& GetPeerAddress() const = 0;
    virtual const ResolvedAddress& GetLocalAddress() const = 0;

    virtual std::vector<size_t> AllWriteMetrics() = 0;

    virtual std::optional<absl::string_view> GetMetricName(size_t key) = 0;

    virtual std::optional<size_t> GetMetricKey(absl::string_view name) = 0;
  };

  using OnConnectCallback =
      absl::AnyInvocable<void(absl::StatusOr<std::unique_ptr<Endpoint>>)>;

  class Listener : public Extensible {
   public:

    using AcceptCallback = absl::AnyInvocable<void(
        std::unique_ptr<Endpoint>, MemoryAllocator memory_allocator)>;
    virtual ~Listener() = default;

    virtual absl::StatusOr<int> Bind(const ResolvedAddress& addr) = 0;
    virtual absl::Status Start() = 0;
  };

  virtual absl::StatusOr<std::unique_ptr<Listener>> CreateListener(
      Listener::AcceptCallback on_accept,
      absl::AnyInvocable<void(absl::Status)> on_shutdown,
      const EndpointConfig& config,
      std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory) = 0;

  virtual ConnectionHandle Connect(OnConnectCallback on_connect,
                                   const ResolvedAddress& addr,
                                   const EndpointConfig& args,
                                   MemoryAllocator memory_allocator,
                                   Duration timeout) = 0;

  virtual bool CancelConnect(ConnectionHandle handle) = 0;

  class DNSResolver : public Extensible {
   public:

    struct ResolverOptions {

      std::string dns_server;
    };

    struct SRVRecord {
      std::string host;
      int port = 0;
      int priority = 0;
      int weight = 0;
    };

    using LookupHostnameCallback =
        absl::AnyInvocable<void(absl::StatusOr<std::vector<ResolvedAddress>>)>;

    using LookupSRVCallback =
        absl::AnyInvocable<void(absl::StatusOr<std::vector<SRVRecord>>)>;

    using LookupTXTCallback =
        absl::AnyInvocable<void(absl::StatusOr<std::vector<std::string>>)>;

    virtual ~DNSResolver() = default;

    virtual void LookupHostname(LookupHostnameCallback on_resolve,
                                absl::string_view name,
                                absl::string_view default_port) = 0;

    virtual void LookupSRV(LookupSRVCallback on_resolve,
                           absl::string_view name) = 0;

    virtual void LookupTXT(LookupTXTCallback on_resolve,
                           absl::string_view name) = 0;
  };

  virtual ~EventEngine() = default;

  virtual bool IsWorkerThread() = 0;

  virtual absl::StatusOr<std::unique_ptr<DNSResolver>> GetDNSResolver(
      const DNSResolver::ResolverOptions& options) = 0;

  virtual void Run(Closure* closure) = 0;

  virtual void Run(absl::AnyInvocable<void()> closure) = 0;

  virtual TaskHandle RunAfter(Duration when, Closure* closure) = 0;

  virtual TaskHandle RunAfter(Duration when,
                              absl::AnyInvocable<void()> closure) = 0;

  virtual bool Cancel(TaskHandle handle) = 0;
};

void SetEventEngineFactory(
    absl::AnyInvocable<std::shared_ptr<EventEngine>()> factory);

void EventEngineFactoryReset();

std::shared_ptr<EventEngine> CreateEventEngine();

void SetDefaultEventEngine(std::shared_ptr<EventEngine> engine);

std::shared_ptr<EventEngine> GetDefaultEventEngine();

void ShutdownDefaultEventEngine();

bool operator==(const EventEngine::TaskHandle& lhs,
                const EventEngine::TaskHandle& rhs);
bool operator!=(const EventEngine::TaskHandle& lhs,
                const EventEngine::TaskHandle& rhs);
std::ostream& operator<<(std::ostream& out,
                         const EventEngine::TaskHandle& handle);
bool operator==(const EventEngine::ConnectionHandle& lhs,
                const EventEngine::ConnectionHandle& rhs);
bool operator!=(const EventEngine::ConnectionHandle& lhs,
                const EventEngine::ConnectionHandle& rhs);
std::ostream& operator<<(std::ostream& out,
                         const EventEngine::ConnectionHandle& handle);

namespace detail {
std::string FormatHandleString(uint64_t key1, uint64_t key2);
}

template <typename Sink>
void AbslStringify(Sink& out, const EventEngine::ConnectionHandle& handle) {
  out.Append(detail::FormatHandleString(handle.keys[0], handle.keys[1]));
}

template <typename Sink>
void AbslStringify(Sink& out, const EventEngine::TaskHandle& handle) {
  out.Append(detail::FormatHandleString(handle.keys[0], handle.keys[1]));
}

}
}

#endif
