
// Copyright 2022 gRPC authors.

#ifndef GRPC_TEST_CORE_XDS_XDS_TRANSPORT_FAKE_H
#define GRPC_TEST_CORE_XDS_XDS_TRANSPORT_FAKE_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <deque>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "absl/time/time.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"
#include "src/core/xds/xds_client/xds_transport.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.h"

namespace grpc_core {

class FakeXdsTransportFactory : public XdsTransportFactory {
 private:
  class FakeXdsTransport;

 public:
  static constexpr char kAdsMethod[] =
      "/envoy.service.discovery.v3.AggregatedDiscoveryService/"
      "StreamAggregatedResources";
  static constexpr char kLrsMethod[] =
      "/envoy.service.load_stats.v3.LoadReportingService/StreamLoadStats";

  class FakeStreamingCall : public XdsTransport::StreamingCall {
   public:
    FakeStreamingCall(
        WeakRefCountedPtr<FakeXdsTransport> transport, const char* method,
        std::unique_ptr<StreamingCall::EventHandler> event_handler)
        : transport_(std::move(transport)),
          method_(method),
          event_engine_(transport_->factory()->event_engine_),
          event_handler_(MakeRefCounted<RefCountedEventHandler>(
              std::move(event_handler))) {}

    ~FakeStreamingCall() override;

    void Orphan() override;

    bool IsOrphaned();

    void StartRecvMessage() override;

    using StreamingCall::Ref;

    bool HaveMessageFromClient();
    std::optional<std::string> WaitForMessageFromClient();

    void CompleteSendMessageFromClient(bool ok = true);

    void SendMessageToClient(absl::string_view payload);
    void MaybeSendStatusToClient(absl::Status status);

    bool WaitForReadsStarted(size_t expected);

   private:
    class RefCountedEventHandler : public RefCounted<RefCountedEventHandler> {
     public:
      explicit RefCountedEventHandler(
          std::unique_ptr<StreamingCall::EventHandler> event_handler)
          : event_handler_(std::move(event_handler)) {}

      void OnRequestSent(bool ok) { event_handler_->OnRequestSent(ok); }
      void OnRecvMessage(absl::string_view payload) {
        event_handler_->OnRecvMessage(payload);
      }
      void OnStatusReceived(absl::Status status) {
        event_handler_->OnStatusReceived(std::move(status));
      }

     private:
      std::unique_ptr<StreamingCall::EventHandler> event_handler_;
    };

    void SendMessage(std::string payload) override;

    void CompleteSendMessageFromClientLocked(bool ok)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);
    void MaybeDeliverMessageToClient();

    WeakRefCountedPtr<FakeXdsTransport> transport_;
    const char* method_;
    std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine>
        event_engine_;

    Mutex mu_;
    RefCountedPtr<RefCountedEventHandler> event_handler_ ABSL_GUARDED_BY(&mu_);
    std::deque<std::string> from_client_messages_ ABSL_GUARDED_BY(&mu_);
    bool status_sent_ ABSL_GUARDED_BY(&mu_) = false;
    bool orphaned_ ABSL_GUARDED_BY(&mu_) = false;
    size_t reads_started_ ABSL_GUARDED_BY(&mu_) = 0;
    size_t num_pending_reads_ ABSL_GUARDED_BY(&mu_) = 0;
    std::deque<std::string> to_client_messages_ ABSL_GUARDED_BY(&mu_);
  };

  explicit FakeXdsTransportFactory(
      std::function<void()> too_many_pending_reads_callback,
      std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine>
          event_engine)
      : event_engine_(std::move(event_engine)),
        too_many_pending_reads_callback_(
            std::move(too_many_pending_reads_callback)) {}

  void TriggerConnectionFailure(const XdsBootstrap::XdsServerTarget& server,
                                absl::Status status);

  void SetAutoCompleteMessagesFromClient(bool value);

  void SetAbortOnUndrainedMessages(bool value);

  RefCountedPtr<FakeStreamingCall> WaitForStream(
      const XdsBootstrap::XdsServerTarget& server, const char* method);

  void Orphaned() override;

 private:
  class FakeXdsTransport : public XdsTransport {
   public:
    FakeXdsTransport(WeakRefCountedPtr<FakeXdsTransportFactory> factory,
                     const XdsBootstrap::XdsServerTarget& server,
                     bool auto_complete_messages_from_client,
                     bool abort_on_undrained_messages)
        : factory_(std::move(factory)),
          server_(server),
          auto_complete_messages_from_client_(
              auto_complete_messages_from_client),
          abort_on_undrained_messages_(abort_on_undrained_messages),
          event_engine_(factory_->event_engine_) {}

    void Orphaned() override;

    bool auto_complete_messages_from_client() const {
      return auto_complete_messages_from_client_;
    }

    bool abort_on_undrained_messages() const {
      return abort_on_undrained_messages_;
    }

    void TriggerConnectionFailure(absl::Status status);

    RefCountedPtr<FakeStreamingCall> WaitForStream(const char* method);

    void RemoveStream(const char* method, FakeStreamingCall* call);

    FakeXdsTransportFactory* factory() const { return factory_.get(); }

    const XdsBootstrap::XdsServerTarget* server() const { return &server_; }

   private:
    void StartConnectivityFailureWatch(
        RefCountedPtr<ConnectivityFailureWatcher> watcher) override;
    void StopConnectivityFailureWatch(
        const RefCountedPtr<ConnectivityFailureWatcher>& watcher) override;

    OrphanablePtr<StreamingCall> CreateStreamingCall(
        const char* method,
        std::unique_ptr<StreamingCall::EventHandler> event_handler) override;

    void ResetBackoff() override {}

    WeakRefCountedPtr<FakeXdsTransportFactory> factory_;
    const XdsBootstrap::XdsServerTarget& server_;
    const bool auto_complete_messages_from_client_;
    const bool abort_on_undrained_messages_;
    std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine>
        event_engine_;

    Mutex mu_;
    std::set<RefCountedPtr<ConnectivityFailureWatcher>> watchers_
        ABSL_GUARDED_BY(&mu_);
    std::map<std::string , RefCountedPtr<FakeStreamingCall>>
        active_calls_ ABSL_GUARDED_BY(&mu_);
  };

  RefCountedPtr<XdsTransport> GetTransport(
      const XdsBootstrap::XdsServerTarget& server,
      absl::Status* ) override;

  RefCountedPtr<FakeXdsTransport> GetTransport(
      const XdsBootstrap::XdsServerTarget& server);

  RefCountedPtr<FakeXdsTransport> GetTransportLocked(const std::string& key)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

  std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine>
      event_engine_;

  Mutex mu_;
  std::map<std::string , FakeXdsTransport*> transport_map_
      ABSL_GUARDED_BY(&mu_);
  bool auto_complete_messages_from_client_ ABSL_GUARDED_BY(&mu_) = true;
  bool abort_on_undrained_messages_ ABSL_GUARDED_BY(&mu_) = true;
  std::function<void()> too_many_pending_reads_callback_;
};

}

#endif
