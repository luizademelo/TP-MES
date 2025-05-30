
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_SUBCHANNEL_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_SUBCHANNEL_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <functional>
#include <map>
#include <memory>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/client_channel/connector.h"
#include "src/core/client_channel/subchannel_pool_interface.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/iomgr/call_combiner.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/backoff.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/time_precise.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

class SubchannelCall;

class ConnectedSubchannel : public RefCounted<ConnectedSubchannel> {
 public:
  const ChannelArgs& args() const { return args_; }

  virtual void StartWatch(
      grpc_pollset_set* interested_parties,
      OrphanablePtr<ConnectivityStateWatcherInterface> watcher) = 0;

  virtual void Ping(absl::AnyInvocable<void(absl::Status)> on_ack) = 0;
  virtual RefCountedPtr<UnstartedCallDestination> unstarted_call_destination()
      const = 0;

  virtual grpc_channel_stack* channel_stack() const = 0;
  virtual size_t GetInitialCallSizeEstimate() const = 0;
  virtual void Ping(grpc_closure* on_initiate, grpc_closure* on_ack) = 0;

 protected:
  explicit ConnectedSubchannel(const ChannelArgs& args);

 private:
  ChannelArgs args_;
};

class LegacyConnectedSubchannel;

class SubchannelCall final {
 public:
  struct Args {
    RefCountedPtr<ConnectedSubchannel> connected_subchannel;
    grpc_polling_entity* pollent;
    gpr_cycle_counter start_time;
    Timestamp deadline;
    Arena* arena;
    CallCombiner* call_combiner;
  };
  static RefCountedPtr<SubchannelCall> Create(Args args,
                                              grpc_error_handle* error);

  void StartTransportStreamOpBatch(grpc_transport_stream_op_batch* batch);

  grpc_call_stack* GetCallStack();

  void SetAfterCallStackDestroy(grpc_closure* closure);

  GRPC_MUST_USE_RESULT RefCountedPtr<SubchannelCall> Ref();
  GRPC_MUST_USE_RESULT RefCountedPtr<SubchannelCall> Ref(
      const DebugLocation& location, const char* reason);

  void Unref();
  void Unref(const DebugLocation& location, const char* reason);

 private:

  template <typename T>
  friend class RefCountedPtr;

  SubchannelCall(Args args, grpc_error_handle* error);

  void MaybeInterceptRecvTrailingMetadata(
      grpc_transport_stream_op_batch* batch);

  static void RecvTrailingMetadataReady(void* arg, grpc_error_handle error);

  void IncrementRefCount();
  void IncrementRefCount(const DebugLocation& location, const char* reason);

  static void Destroy(void* arg, grpc_error_handle error);

  RefCountedPtr<LegacyConnectedSubchannel> connected_subchannel_;
  grpc_closure* after_call_stack_destroy_ = nullptr;

  grpc_closure recv_trailing_metadata_ready_;
  grpc_closure* original_recv_trailing_metadata_ = nullptr;
  grpc_metadata_batch* recv_trailing_metadata_ = nullptr;
  Timestamp deadline_;
};

class Subchannel final : public DualRefCounted<Subchannel> {
 public:

  class ConnectivityStateWatcherInterface
      : public RefCounted<ConnectivityStateWatcherInterface> {
   public:

    virtual void OnConnectivityStateChange(grpc_connectivity_state state,
                                           const absl::Status& status) = 0;

    virtual grpc_pollset_set* interested_parties() = 0;
  };

  class DataProducerInterface : public DualRefCounted<DataProducerInterface> {
   public:

    virtual UniqueTypeName type() const = 0;
  };

  static RefCountedPtr<Subchannel> Create(
      OrphanablePtr<SubchannelConnector> connector,
      const grpc_resolved_address& address, const ChannelArgs& args);

  Subchannel(SubchannelKey key, OrphanablePtr<SubchannelConnector> connector,
             const ChannelArgs& args);
  ~Subchannel() override;

  void ThrottleKeepaliveTime(int new_keepalive_time) ABSL_LOCKS_EXCLUDED(mu_);

  grpc_pollset_set* pollset_set() const { return pollset_set_; }

  channelz::SubchannelNode* channelz_node();

  std::string address() const {
    return grpc_sockaddr_to_uri(&key_.address())
        .value_or("<unknown address type>");
  }

  void WatchConnectivityState(
      RefCountedPtr<ConnectivityStateWatcherInterface> watcher)
      ABSL_LOCKS_EXCLUDED(mu_);

  void CancelConnectivityStateWatch(ConnectivityStateWatcherInterface* watcher)
      ABSL_LOCKS_EXCLUDED(mu_);

  RefCountedPtr<ConnectedSubchannel> connected_subchannel()
      ABSL_LOCKS_EXCLUDED(mu_) {
    MutexLock lock(&mu_);
    return connected_subchannel_;
  }

  RefCountedPtr<UnstartedCallDestination> call_destination() {
    MutexLock lock(&mu_);
    if (connected_subchannel_ == nullptr) return nullptr;
    return connected_subchannel_->unstarted_call_destination();
  }

  void RequestConnection() ABSL_LOCKS_EXCLUDED(mu_);

  void ResetBackoff() ABSL_LOCKS_EXCLUDED(mu_);

  void GetOrAddDataProducer(
      UniqueTypeName type,
      std::function<void(DataProducerInterface**)> get_or_add)
      ABSL_LOCKS_EXCLUDED(mu_);

  void RemoveDataProducer(DataProducerInterface* data_producer)
      ABSL_LOCKS_EXCLUDED(mu_);

  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine() {
    return event_engine_;
  }

  static ChannelArgs MakeSubchannelArgs(
      const ChannelArgs& channel_args, const ChannelArgs& address_args,
      const RefCountedPtr<SubchannelPoolInterface>& subchannel_pool,
      const std::string& channel_default_authority);

 private:

  void Orphaned() override ABSL_LOCKS_EXCLUDED(mu_);

  class ConnectivityStateWatcherList final {
   public:
    explicit ConnectivityStateWatcherList(Subchannel* subchannel)
        : subchannel_(subchannel) {}

    ~ConnectivityStateWatcherList() { Clear(); }

    void AddWatcherLocked(
        RefCountedPtr<ConnectivityStateWatcherInterface> watcher);
    void RemoveWatcherLocked(ConnectivityStateWatcherInterface* watcher);

    void NotifyLocked(grpc_connectivity_state state,
                      const absl::Status& status);

    void Clear() { watchers_.clear(); }

    bool empty() const { return watchers_.empty(); }

   private:
    Subchannel* subchannel_;
    absl::flat_hash_set<RefCountedPtr<ConnectivityStateWatcherInterface>,
                        RefCountedPtrHash<ConnectivityStateWatcherInterface>,
                        RefCountedPtrEq<ConnectivityStateWatcherInterface>>
        watchers_;
  };

  class ConnectedSubchannelStateWatcher;

  void SetConnectivityStateLocked(grpc_connectivity_state state,
                                  const absl::Status& status)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  void OnRetryTimer() ABSL_LOCKS_EXCLUDED(mu_);
  void OnRetryTimerLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  void StartConnectingLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  static void OnConnectingFinished(void* arg, grpc_error_handle error)
      ABSL_LOCKS_EXCLUDED(mu_);
  void OnConnectingFinishedLocked(grpc_error_handle error)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  bool PublishTransportLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  RefCountedPtr<SubchannelPoolInterface> subchannel_pool_;

  const SubchannelKey key_;

  grpc_resolved_address address_for_connect_;

  ChannelArgs args_;

  grpc_pollset_set* pollset_set_;

  RefCountedPtr<channelz::SubchannelNode> channelz_node_;

  Duration min_connect_timeout_;

  OrphanablePtr<SubchannelConnector> connector_;
  SubchannelConnector::Result connecting_result_;
  grpc_closure on_connecting_finished_;

  Mutex mu_;

  bool shutdown_ ABSL_GUARDED_BY(mu_) = false;

  grpc_connectivity_state state_ ABSL_GUARDED_BY(mu_) = GRPC_CHANNEL_IDLE;
  absl::Status status_ ABSL_GUARDED_BY(mu_);

  ConnectivityStateWatcherList watcher_list_ ABSL_GUARDED_BY(mu_);

  WorkSerializer work_serializer_;

  RefCountedPtr<ConnectedSubchannel> connected_subchannel_ ABSL_GUARDED_BY(mu_);

  BackOff backoff_ ABSL_GUARDED_BY(mu_);
  Timestamp next_attempt_time_ ABSL_GUARDED_BY(mu_);
  grpc_event_engine::experimental::EventEngine::TaskHandle retry_timer_handle_
      ABSL_GUARDED_BY(mu_);

  int keepalive_time_ ABSL_GUARDED_BY(mu_) = -1;

  std::map<UniqueTypeName, DataProducerInterface*> data_producer_map_
      ABSL_GUARDED_BY(mu_);
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
};

}

#endif
