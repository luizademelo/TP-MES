
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_SERVER_SERVER_H
#define GRPC_SRC_CORE_SERVER_SERVER_H

#include <grpc/compression.h>
#include <grpc/grpc.h>
#include <grpc/passive_listener.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <atomic>
#include <functional>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/hash/hash.h"
#include "absl/random/random.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/channelz/channelz.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/call_combiner.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/resource_quota/connection_quota.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/surface/completion_queue.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/server/server_interface.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/util/cpp_impl_of.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/random_early_detection.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

#define GRPC_ARG_SERVER_MAX_PENDING_REQUESTS "grpc.server.max_pending_requests"
#define GRPC_ARG_SERVER_MAX_PENDING_REQUESTS_HARD_LIMIT \
  "grpc.server.max_pending_requests_hard_limit"

namespace grpc_core {

class ServerConfigFetcher
    : public CppImplOf<ServerConfigFetcher, grpc_server_config_fetcher> {
 public:
  class ConnectionManager
      : public grpc_core::DualRefCounted<ConnectionManager> {
   public:
    virtual absl::StatusOr<grpc_core::ChannelArgs>
    UpdateChannelArgsForConnection(const grpc_core::ChannelArgs& args,
                                   grpc_endpoint* tcp) = 0;
  };

  class WatcherInterface {
   public:
    virtual ~WatcherInterface() = default;

    virtual void UpdateConnectionManager(
        grpc_core::RefCountedPtr<ConnectionManager> manager) = 0;

    virtual void StopServing() = 0;
  };

  virtual ~ServerConfigFetcher() = default;

  virtual void StartWatch(std::string listening_address,
                          std::unique_ptr<WatcherInterface> watcher) = 0;
  virtual void CancelWatch(WatcherInterface* watcher) = 0;
  virtual grpc_pollset_set* interested_parties() = 0;
};

namespace experimental {
class PassiveListenerImpl;
}

namespace testing {
class ServerTestPeer;
class ListenerStateTestPeer;
}

class Server : public ServerInterface,
               public InternallyRefCounted<Server>,
               public CppImplOf<Server, grpc_server> {
 public:

  static const grpc_channel_filter kServerTopFilter;

  struct RegisteredMethod;

  struct BatchCallAllocation {
    void* tag;
    grpc_call** call;
    grpc_metadata_array* initial_metadata;
    grpc_call_details* details;
    grpc_completion_queue* cq;
  };

  struct RegisteredCallAllocation {
    void* tag;
    grpc_call** call;
    grpc_metadata_array* initial_metadata;
    gpr_timespec* deadline;
    grpc_byte_buffer** optional_payload;
    grpc_completion_queue* cq;
  };

  class ListenerState;

  class ListenerInterface : public InternallyRefCounted<ListenerInterface> {
   public:

    class LogicalConnection : public InternallyRefCounted<LogicalConnection> {
     public:
      explicit LogicalConnection(const char* trace = nullptr)
          : InternallyRefCounted(trace) {}
      ~LogicalConnection() override = default;

      virtual void SendGoAway() = 0;
      virtual void DisconnectImmediately() = 0;
    };

    explicit ListenerInterface(const char* trace = nullptr)
        : InternallyRefCounted(trace) {}
    ~ListenerInterface() override = default;

    virtual void Start() = 0;

    virtual channelz::ListenSocketNode* channelz_listen_socket_node() const = 0;

    virtual void SetServerListenerState(
        RefCountedPtr<ListenerState> listener_state) = 0;

    virtual const grpc_resolved_address* resolved_address() const = 0;

    virtual void SetOnDestroyDone(grpc_closure* on_destroy_done) = 0;
  };

  class ListenerState : public RefCounted<ListenerState> {
   public:
    explicit ListenerState(RefCountedPtr<Server> server,
                           OrphanablePtr<ListenerInterface> l);

    void Start();

    void Stop();

    ListenerInterface* listener() { return listener_.get(); }

    Server* server() const { return server_.get(); }

    std::optional<ChannelArgs> AddLogicalConnection(
        OrphanablePtr<ListenerInterface::LogicalConnection> connection,
        const ChannelArgs& args, grpc_endpoint* endpoint)
        ABSL_LOCKS_EXCLUDED(mu_);

    void OnHandshakeDone(ListenerInterface::LogicalConnection* connection);

    void RemoveLogicalConnection(
        ListenerInterface::LogicalConnection* connection);

    const MemoryQuotaRefPtr& memory_quota() const { return memory_quota_; }

    const ConnectionQuotaRefPtr& connection_quota() const {
      return connection_quota_;
    }

    grpc_event_engine::experimental::EventEngine* event_engine() const {
      return event_engine_;
    }

   private:
    friend class grpc_core::testing::ListenerStateTestPeer;

    class ConfigFetcherWatcher : public ServerConfigFetcher::WatcherInterface {
     public:
      explicit ConfigFetcherWatcher(ListenerState* listener_state)
          : listener_state_(listener_state) {}

      void UpdateConnectionManager(
          RefCountedPtr<ServerConfigFetcher::ConnectionManager>
              connection_manager) override;

      void StopServing() override;

     private:

      ListenerState* const listener_state_;
    };

    struct ConnectionsToBeDrained {
      absl::flat_hash_set<OrphanablePtr<ListenerInterface::LogicalConnection>>
          connections;
      grpc_core::Timestamp timestamp;
    };

    void DrainConnectionsLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

    void OnDrainGraceTimer();

    void MaybeStartNewGraceTimerLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

    void RemoveConnectionsToBeDrainedOnEmptyLocked(
        std::deque<ConnectionsToBeDrained>::iterator it)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

    RefCountedPtr<Server> const server_;
    MemoryQuotaRefPtr const memory_quota_;
    ConnectionQuotaRefPtr connection_quota_;
    grpc_event_engine::experimental::EventEngine* const event_engine_;
    OrphanablePtr<ListenerInterface> listener_;
    grpc_closure destroy_done_;
    ConfigFetcherWatcher* config_fetcher_watcher_ = nullptr;
    Mutex mu_;

    RefCountedPtr<ServerConfigFetcher::ConnectionManager> connection_manager_
        ABSL_GUARDED_BY(mu_);
    bool is_serving_ ABSL_GUARDED_BY(mu_) = false;
    bool started_ ABSL_GUARDED_BY(mu_) = false;
    absl::flat_hash_set<OrphanablePtr<ListenerInterface::LogicalConnection>>
        connections_ ABSL_GUARDED_BY(mu_);
    std::deque<ConnectionsToBeDrained> connections_to_be_drained_list_
        ABSL_GUARDED_BY(mu_);
    grpc_event_engine::experimental::EventEngine::TaskHandle
        drain_grace_timer_handle_ ABSL_GUARDED_BY(mu_) =
            grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid;
  };

  explicit Server(const ChannelArgs& args);
  ~Server() override;

  void Orphan() ABSL_LOCKS_EXCLUDED(mu_global_) override;

  const ChannelArgs& channel_args() const override { return channel_args_; }
  channelz::ServerNode* channelz_node() const override {
    return channelz_node_.get();
  }

  const std::vector<grpc_pollset*>& pollsets() const { return pollsets_; }

  ServerConfigFetcher* config_fetcher() const { return config_fetcher_.get(); }

  ServerCallTracerFactory* server_call_tracer_factory() const override {
    return server_call_tracer_factory_;
  }

  void set_config_fetcher(std::unique_ptr<ServerConfigFetcher> config_fetcher) {
    config_fetcher_ = std::move(config_fetcher);
  }

  bool HasOpenConnections() ABSL_LOCKS_EXCLUDED(mu_global_);

  void AddListener(OrphanablePtr<ListenerInterface> listener);

  void Start() ABSL_LOCKS_EXCLUDED(mu_global_);

  grpc_error_handle SetupTransport(Transport* transport,
                                   grpc_pollset* accepting_pollset,
                                   const ChannelArgs& args)
      ABSL_LOCKS_EXCLUDED(mu_global_);

  void RegisterCompletionQueue(grpc_completion_queue* cq);

  void SetRegisteredMethodAllocator(
      grpc_completion_queue* cq, void* method_tag,
      std::function<RegisteredCallAllocation()> allocator);
  void SetBatchMethodAllocator(grpc_completion_queue* cq,
                               std::function<BatchCallAllocation()> allocator);

  RegisteredMethod* RegisterMethod(
      const char* method, const char* host,
      grpc_server_register_method_payload_handling payload_handling,
      uint32_t flags);

  grpc_call_error RequestCall(grpc_call** call, grpc_call_details* details,
                              grpc_metadata_array* request_metadata,
                              grpc_completion_queue* cq_bound_to_call,
                              grpc_completion_queue* cq_for_notification,
                              void* tag);

  grpc_call_error RequestRegisteredCall(
      RegisteredMethod* rm, grpc_call** call, gpr_timespec* deadline,
      grpc_metadata_array* request_metadata,
      grpc_byte_buffer** optional_payload,
      grpc_completion_queue* cq_bound_to_call,
      grpc_completion_queue* cq_for_notification, void* tag_new);

  void ShutdownAndNotify(grpc_completion_queue* cq, void* tag)
      ABSL_LOCKS_EXCLUDED(mu_global_, mu_call_);

  void StopListening();

  void CancelAllCalls() ABSL_LOCKS_EXCLUDED(mu_global_);

  void SendGoaways() ABSL_LOCKS_EXCLUDED(mu_global_, mu_call_);

  grpc_compression_options compression_options() const override {
    return compression_options_;
  }

 private:
  // note: the grpc_core::Server redundant namespace qualification is

  friend absl::Status(::grpc_server_add_passive_listener)(
      grpc_core::Server* server, grpc_server_credentials* credentials,
      std::shared_ptr<grpc_core::experimental::PassiveListenerImpl>
          passive_listener);

  friend class grpc_core::testing::ServerTestPeer;

  struct RequestedCall;

  class RequestMatcherInterface;
  class RealRequestMatcher;
  class AllocatingRequestMatcherBase;
  class AllocatingRequestMatcherBatch;
  class AllocatingRequestMatcherRegistered;

  class ChannelData final {
   public:
    ChannelData() = default;
    ~ChannelData();

    void InitTransport(RefCountedPtr<Server> server,
                       RefCountedPtr<Channel> channel, size_t cq_idx,
                       Transport* transport, intptr_t channelz_socket_uuid);

    RefCountedPtr<Server> server() const { return server_; }
    Channel* channel() const { return channel_.get(); }
    size_t cq_idx() const { return cq_idx_; }

    static grpc_error_handle InitChannelElement(
        grpc_channel_element* elem, grpc_channel_element_args* args);
    static void DestroyChannelElement(grpc_channel_element* elem);

   private:
    class ConnectivityWatcher;

    static void AcceptStream(void* arg, Transport* ,
                             const void* transport_server_data);

    void Destroy() ABSL_EXCLUSIVE_LOCKS_REQUIRED(server_->mu_global_);

    static void FinishDestroy(void* arg, grpc_error_handle error);

    RefCountedPtr<Server> server_;
    RefCountedPtr<Channel> channel_;

    size_t cq_idx_;
    std::optional<std::list<ChannelData*>::iterator> list_position_;
    grpc_closure finish_destroy_channel_closure_;
    intptr_t channelz_socket_uuid_;
  };

  class CallData {
   public:
    enum class CallState {
      NOT_STARTED,
      PENDING,
      ACTIVATED,
      ZOMBIED,
    };

    CallData(grpc_call_element* elem, const grpc_call_element_args& args,
             RefCountedPtr<Server> server);
    ~CallData();

    void Start(grpc_call_element* elem);

    void SetState(CallState state);

    bool MaybeActivate();

    void Publish(size_t cq_idx, RequestedCall* rc);

    void KillZombie();

    void FailCallCreation();

    static grpc_error_handle InitCallElement(
        grpc_call_element* elem, const grpc_call_element_args* args);
    static void DestroyCallElement(grpc_call_element* elem,
                                   const grpc_call_final_info* ,
                                   grpc_closure* );
    static void StartTransportStreamOpBatch(
        grpc_call_element* elem, grpc_transport_stream_op_batch* batch);

   private:

    static void RecvInitialMetadataBatchComplete(void* arg,
                                                 grpc_error_handle error);
    void StartNewRpc(grpc_call_element* elem);
    static void PublishNewRpc(void* arg, grpc_error_handle error);

    void StartTransportStreamOpBatchImpl(grpc_call_element* elem,
                                         grpc_transport_stream_op_batch* batch);
    static void RecvInitialMetadataReady(void* arg, grpc_error_handle error);
    static void RecvTrailingMetadataReady(void* arg, grpc_error_handle error);

    RefCountedPtr<Server> server_;

    grpc_call* call_;

    std::atomic<CallState> state_{CallState::NOT_STARTED};

    std::optional<Slice> path_;
    std::optional<Slice> host_;
    Timestamp deadline_ = Timestamp::InfFuture();

    grpc_completion_queue* cq_new_ = nullptr;

    RequestMatcherInterface* matcher_ = nullptr;
    grpc_byte_buffer* payload_ = nullptr;

    grpc_closure kill_zombie_closure_;

    grpc_metadata_array initial_metadata_ =
        grpc_metadata_array();
    grpc_closure recv_initial_metadata_batch_complete_;

    grpc_metadata_batch* recv_initial_metadata_ = nullptr;
    grpc_closure recv_initial_metadata_ready_;
    grpc_closure* original_recv_initial_metadata_ready_;
    grpc_error_handle recv_initial_metadata_error_;

    bool seen_recv_trailing_metadata_ready_ = false;
    grpc_closure recv_trailing_metadata_ready_;
    grpc_closure* original_recv_trailing_metadata_ready_;
    grpc_error_handle recv_trailing_metadata_error_;

    grpc_closure publish_;

    CallCombiner* call_combiner_;
  };

  struct ShutdownTag {
    ShutdownTag(void* tag_arg, grpc_completion_queue* cq_arg)
        : tag(tag_arg), cq(cq_arg) {}
    void* const tag;
    grpc_completion_queue* const cq;
    grpc_cq_completion completion;
  };

  struct StringViewStringViewPairHash
      : absl::flat_hash_set<
            std::pair<absl::string_view, absl::string_view>>::hasher {
    using is_transparent = void;
  };

  struct StringViewStringViewPairEq
      : std::equal_to<std::pair<absl::string_view, absl::string_view>> {
    using is_transparent = void;
  };

  class TransportConnectivityWatcher;

  RegisteredMethod* GetRegisteredMethod(const absl::string_view& host,
                                        const absl::string_view& path);
  void SetRegisteredMethodOnMetadata(ClientMetadata& metadata);

  static void ListenerDestroyDone(void* arg, grpc_error_handle error);

  static void DoneShutdownEvent(void* server,
                                grpc_cq_completion* ) {
    static_cast<Server*>(server)->Unref();
  }

  static void DoneRequestEvent(void* req, grpc_cq_completion* completion);

  void FailCall(size_t cq_idx, RequestedCall* rc, grpc_error_handle error);
  grpc_call_error QueueRequestedCall(size_t cq_idx, RequestedCall* rc);

  void MaybeFinishShutdown() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_global_)
      ABSL_LOCKS_EXCLUDED(mu_call_);

  void KillPendingWorkLocked(grpc_error_handle error)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_call_);

  static grpc_call_error ValidateServerRequest(
      grpc_completion_queue* cq_for_notification, void* tag,
      grpc_byte_buffer** optional_payload, RegisteredMethod* rm);
  grpc_call_error ValidateServerRequestAndCq(
      size_t* cq_idx, grpc_completion_queue* cq_for_notification, void* tag,
      grpc_byte_buffer** optional_payload, RegisteredMethod* rm);

  std::vector<RefCountedPtr<Channel>> GetChannelsLocked() const;

  bool ShutdownRefOnRequest() {
    int old_value = shutdown_refs_.fetch_add(2, std::memory_order_acq_rel);
    return (old_value & 1) != 0;
  }

  void ShutdownUnrefOnRequest() ABSL_LOCKS_EXCLUDED(mu_global_) {
    if (shutdown_refs_.fetch_sub(2, std::memory_order_acq_rel) == 2) {
      MutexLock lock(&mu_global_);
      MaybeFinishShutdown();
    }
  }
  void ShutdownUnrefOnShutdownCall() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_global_) {
    if (shutdown_refs_.fetch_sub(1, std::memory_order_acq_rel) == 1) {

      MaybeFinishShutdown();
    }
  }

  bool ShutdownCalled() const {
    return (shutdown_refs_.load(std::memory_order_acquire) & 1) == 0;
  }

  bool ShutdownReady() const {
    return shutdown_refs_.load(std::memory_order_acquire) == 0;
  }

  auto MatchRequestAndMaybeReadFirstMessage(CallHandler call_handler,
                                            ClientMetadataHandle md);
  auto MatchAndPublishCall(CallHandler call_handler);
  absl::StatusOr<RefCountedPtr<UnstartedCallDestination>> MakeCallDestination(
      const ChannelArgs& args);

  ChannelArgs const channel_args_;
  RefCountedPtr<channelz::ServerNode> channelz_node_;
  std::unique_ptr<ServerConfigFetcher> config_fetcher_;
  ServerCallTracerFactory* const server_call_tracer_factory_;

  std::vector<grpc_completion_queue*> cqs_;
  std::vector<grpc_pollset*> pollsets_;
  bool started_ = false;
  const grpc_compression_options compression_options_;

  Mutex mu_global_;
  Mutex mu_call_;

  bool starting_ ABSL_GUARDED_BY(mu_global_) = false;
  CondVar starting_cv_;

  absl::flat_hash_map<std::pair<std::string, std::string> ,
                      std::unique_ptr<RegisteredMethod>,
                      StringViewStringViewPairHash, StringViewStringViewPairEq>
      registered_methods_;

  std::unique_ptr<RequestMatcherInterface> unregistered_request_matcher_;

  std::atomic<int> shutdown_refs_{1};
  bool shutdown_published_ ABSL_GUARDED_BY(mu_global_) = false;
  std::vector<ShutdownTag> shutdown_tags_ ABSL_GUARDED_BY(mu_global_);

  RandomEarlyDetection pending_backlog_protector_ ABSL_GUARDED_BY(mu_call_){
      static_cast<uint64_t>(
          std::max(0, channel_args_.GetInt(GRPC_ARG_SERVER_MAX_PENDING_REQUESTS)
                          .value_or(1000))),
      static_cast<uint64_t>(std::max(
          0,
          channel_args_.GetInt(GRPC_ARG_SERVER_MAX_PENDING_REQUESTS_HARD_LIMIT)
              .value_or(3000)))};
  const Duration max_time_in_pending_queue_;

  std::list<ChannelData*> channels_;
  absl::flat_hash_set<OrphanablePtr<ServerTransport>> connections_
      ABSL_GUARDED_BY(mu_global_);
  RefCountedPtr<ServerConfigFetcher::ConnectionManager> connection_manager_
      ABSL_GUARDED_BY(mu_global_);
  size_t connections_open_ ABSL_GUARDED_BY(mu_global_) = 0;

  std::list<RefCountedPtr<ListenerState>> listener_states_;
  size_t listeners_destroyed_ = 0;

  gpr_timespec last_shutdown_message_time_;
};

}

#endif
