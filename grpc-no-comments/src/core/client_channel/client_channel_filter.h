
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_CLIENT_CHANNEL_FILTER_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_CLIENT_CHANNEL_FILTER_H

#include <grpc/grpc.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <atomic>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_set.h"
#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/channelz/channelz.h"
#include "src/core/client_channel/client_channel_args.h"
#include "src/core/client_channel/client_channel_factory.h"
#include "src/core/client_channel/config_selector.h"
#include "src/core/client_channel/dynamic_filters.h"
#include "src/core/client_channel/subchannel.h"
#include "src/core/client_channel/subchannel_pool_interface.h"
#include "src/core/filter/blackboard.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/iomgr/call_combiner.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/load_balancing/backend_metric_data.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/resolver/resolver.h"
#include "src/core/service_config/service_config.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/time_precise.h"
#include "src/core/util/work_serializer.h"

#define MAX_PENDING_BATCHES 6

namespace grpc_core {

class ClientChannelFilter final {
 public:
  static const grpc_channel_filter kFilter;

  class LoadBalancedCall;
  class FilterBasedLoadBalancedCall;

  struct RawPointerChannelArgTag {};
  static absl::string_view ChannelArgName() {
    return "grpc.internal.client_channel_filter";
  }

  grpc_connectivity_state CheckConnectivityState(bool try_to_connect);

  void AddExternalConnectivityWatcher(grpc_polling_entity pollent,
                                      grpc_connectivity_state* state,
                                      grpc_closure* on_complete,
                                      grpc_closure* watcher_timer_init) {
    new ExternalConnectivityWatcher(this, pollent, state, on_complete,
                                    watcher_timer_init);
  }

  void CancelExternalConnectivityWatcher(grpc_closure* on_complete) {
    ExternalConnectivityWatcher::RemoveWatcherFromExternalWatchersMap(
        this, on_complete, true);
  }

  void AddConnectivityWatcher(
      grpc_connectivity_state initial_state,
      OrphanablePtr<AsyncConnectivityStateWatcherInterface> watcher);
  void RemoveConnectivityWatcher(
      AsyncConnectivityStateWatcherInterface* watcher);

  OrphanablePtr<FilterBasedLoadBalancedCall> CreateLoadBalancedCall(
      const grpc_call_element_args& args, grpc_polling_entity* pollent,
      grpc_closure* on_call_destruction_complete,
      absl::AnyInvocable<void()> on_commit, bool is_transparent_retry);

 private:
  class CallData;
  class FilterBasedCallData;
  class ResolverResultHandler;
  class SubchannelWrapper;
  class ClientChannelControlHelper;
  class ConnectivityWatcherAdder;
  class ConnectivityWatcherRemover;

  class ExternalConnectivityWatcher final
      : public ConnectivityStateWatcherInterface {
   public:
    ExternalConnectivityWatcher(ClientChannelFilter* chand,
                                grpc_polling_entity pollent,
                                grpc_connectivity_state* state,
                                grpc_closure* on_complete,
                                grpc_closure* watcher_timer_init);

    ~ExternalConnectivityWatcher() override;

    static void RemoveWatcherFromExternalWatchersMap(ClientChannelFilter* chand,
                                                     grpc_closure* on_complete,
                                                     bool cancel);

    void Notify(grpc_connectivity_state state,
                const absl::Status& ) override;

    void Cancel();

   private:

    void AddWatcherLocked()
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(*chand_->work_serializer_);
    void RemoveWatcherLocked()
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(*chand_->work_serializer_);

    ClientChannelFilter* chand_;
    grpc_polling_entity pollent_;
    grpc_connectivity_state initial_state_;
    grpc_connectivity_state* state_;
    grpc_closure* on_complete_;
    grpc_closure* watcher_timer_init_;
    std::atomic<bool> done_{false};
  };

  ClientChannelFilter(grpc_channel_element_args* args,
                      grpc_error_handle* error);
  ~ClientChannelFilter();

  static grpc_error_handle Init(grpc_channel_element* elem,
                                grpc_channel_element_args* args);
  static void Destroy(grpc_channel_element* elem);
  static void StartTransportOp(grpc_channel_element* elem,
                               grpc_transport_op* op);
  static void GetChannelInfo(grpc_channel_element* elem,
                             const grpc_channel_info* info);

  // Note: All methods with "Locked" suffix must be invoked from within

  void ReprocessQueuedResolverCalls()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&resolution_mu_);

  void OnResolverResultChangedLocked(Resolver::Result result)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);
  void OnResolverErrorLocked(absl::Status status)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  absl::Status CreateOrUpdateLbPolicyLocked(
      RefCountedPtr<LoadBalancingPolicy::Config> lb_policy_config,
      const std::optional<std::string>& health_check_service_name,
      Resolver::Result result) ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);
  OrphanablePtr<LoadBalancingPolicy> CreateLbPolicyLocked(
      const ChannelArgs& args) ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void UpdateStateLocked(grpc_connectivity_state state,
                         const absl::Status& status, const char* reason)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void UpdateStateAndPickerLocked(
      grpc_connectivity_state state, const absl::Status& status,
      const char* reason,
      RefCountedPtr<LoadBalancingPolicy::SubchannelPicker> picker)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void UpdateServiceConfigInControlPlaneLocked(
      RefCountedPtr<ServiceConfig> service_config,
      RefCountedPtr<ConfigSelector> config_selector, std::string lb_policy_name)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void UpdateServiceConfigInDataPlaneLocked(const ChannelArgs& args)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void CreateResolverLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);
  void DestroyResolverAndLbPolicyLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  grpc_error_handle DoPingLocked(grpc_transport_op* op)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void StartTransportOpLocked(grpc_transport_op* op)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void TryToConnectLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  ChannelArgs channel_args_;
  grpc_channel_stack* owning_stack_;
  ClientChannelFactory* client_channel_factory_;
  RefCountedPtr<ServiceConfig> default_service_config_;
  std::string target_uri_;
  std::string uri_to_resolve_;
  std::string default_authority_;
  channelz::ChannelNode* channelz_node_;
  grpc_pollset_set* interested_parties_;
  const size_t service_config_parser_index_;

  mutable Mutex resolution_mu_;

  absl::flat_hash_set<CallData*> resolver_queued_calls_
      ABSL_GUARDED_BY(resolution_mu_);

  absl::Status resolver_transient_failure_error_
      ABSL_GUARDED_BY(resolution_mu_);
  bool received_service_config_data_ ABSL_GUARDED_BY(resolution_mu_) = false;
  RefCountedPtr<ServiceConfig> service_config_ ABSL_GUARDED_BY(resolution_mu_);
  RefCountedPtr<ConfigSelector> config_selector_
      ABSL_GUARDED_BY(resolution_mu_);
  RefCountedPtr<DynamicFilters> dynamic_filters_
      ABSL_GUARDED_BY(resolution_mu_);

  mutable Mutex lb_mu_;
  RefCountedPtr<LoadBalancingPolicy::SubchannelPicker> picker_
      ABSL_GUARDED_BY(lb_mu_);
  absl::flat_hash_set<RefCountedPtr<LoadBalancedCall>,
                      RefCountedPtrHash<LoadBalancedCall>,
                      RefCountedPtrEq<LoadBalancedCall>>
      lb_queued_calls_ ABSL_GUARDED_BY(lb_mu_);

  std::shared_ptr<WorkSerializer> work_serializer_;
  ConnectivityStateTracker state_tracker_ ABSL_GUARDED_BY(*work_serializer_);
  OrphanablePtr<Resolver> resolver_ ABSL_GUARDED_BY(*work_serializer_);
  bool previous_resolution_contained_addresses_
      ABSL_GUARDED_BY(*work_serializer_) = false;
  RefCountedPtr<ServiceConfig> saved_service_config_
      ABSL_GUARDED_BY(*work_serializer_);
  RefCountedPtr<ConfigSelector> saved_config_selector_
      ABSL_GUARDED_BY(*work_serializer_);
  RefCountedPtr<const Blackboard> blackboard_
      ABSL_GUARDED_BY(*work_serializer_);
  OrphanablePtr<LoadBalancingPolicy> lb_policy_
      ABSL_GUARDED_BY(*work_serializer_);
  RefCountedPtr<SubchannelPoolInterface> subchannel_pool_
      ABSL_GUARDED_BY(*work_serializer_);

  std::map<Subchannel*, int> subchannel_refcount_map_
      ABSL_GUARDED_BY(*work_serializer_);

  absl::flat_hash_set<SubchannelWrapper*> subchannel_wrappers_
      ABSL_GUARDED_BY(*work_serializer_);
  int keepalive_time_ ABSL_GUARDED_BY(*work_serializer_) = -1;
  grpc_error_handle disconnect_error_ ABSL_GUARDED_BY(*work_serializer_);

  Mutex info_mu_;
  std::string info_lb_policy_name_ ABSL_GUARDED_BY(info_mu_);
  std::string info_service_config_json_ ABSL_GUARDED_BY(info_mu_);

  mutable Mutex external_watchers_mu_;
  std::map<grpc_closure*, RefCountedPtr<ExternalConnectivityWatcher>>
      external_watchers_ ABSL_GUARDED_BY(external_watchers_mu_);
};

class ClientChannelFilter::LoadBalancedCall
    : public InternallyRefCounted<LoadBalancedCall, UnrefCallDtor> {
 public:
  LoadBalancedCall(ClientChannelFilter* chand, Arena* arena,
                   absl::AnyInvocable<void()> on_commit,
                   bool is_transparent_retry);
  ~LoadBalancedCall() override;

  void Orphan() override { Unref(); }

  void RemoveCallFromLbQueuedCallsLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&ClientChannelFilter::lb_mu_);

  virtual void RetryPickLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&ClientChannelFilter::lb_mu_) = 0;

 protected:
  ClientChannelFilter* chand() const { return chand_; }
  ClientCallTracer::CallAttemptTracer* call_attempt_tracer() const {
    return call_attempt_tracer_;
  }
  ConnectedSubchannel* connected_subchannel() const {
    return connected_subchannel_.get();
  }
  LoadBalancingPolicy::SubchannelCallTrackerInterface*
  lb_subchannel_call_tracker() const {
    return lb_subchannel_call_tracker_.get();
  }
  Arena* arena() const { return arena_; }

  void Commit() {
    auto on_commit = std::move(on_commit_);
    on_commit();
  }

  std::optional<absl::Status> PickSubchannel(bool was_queued);

  void RecordCallCompletion(absl::Status status,
                            grpc_metadata_batch* recv_trailing_metadata,
                            grpc_transport_stream_stats* transport_stream_stats,
                            absl::string_view peer_address);

  void RecordLatency();

 private:
  class LbCallState;
  class Metadata;
  class BackendMetricAccessor;

  virtual grpc_polling_entity* pollent() = 0;
  virtual grpc_metadata_batch* send_initial_metadata() const = 0;

  bool PickSubchannelImpl(LoadBalancingPolicy::SubchannelPicker* picker,
                          grpc_error_handle* error);

  void AddCallToLbQueuedCallsLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&ClientChannelFilter::lb_mu_);

  virtual void OnAddToQueueLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&ClientChannelFilter::lb_mu_) = 0;

  ClientChannelFilter* chand_;

  ClientCallTracer::CallAttemptTracer* call_attempt_tracer_;

  absl::AnyInvocable<void()> on_commit_;

  RefCountedPtr<ConnectedSubchannel> connected_subchannel_;
  const BackendMetricData* backend_metric_data_ = nullptr;
  std::unique_ptr<LoadBalancingPolicy::SubchannelCallTrackerInterface>
      lb_subchannel_call_tracker_;
  Arena* const arena_;
};

class ClientChannelFilter::FilterBasedLoadBalancedCall final
    : public ClientChannelFilter::LoadBalancedCall {
 public:

  FilterBasedLoadBalancedCall(ClientChannelFilter* chand,
                              const grpc_call_element_args& args,
                              grpc_polling_entity* pollent,
                              grpc_closure* on_call_destruction_complete,
                              absl::AnyInvocable<void()> on_commit,
                              bool is_transparent_retry);
  ~FilterBasedLoadBalancedCall() override;

  void Orphan() override;

  void StartTransportStreamOpBatch(grpc_transport_stream_op_batch* batch);

  RefCountedPtr<SubchannelCall> subchannel_call() const {
    return subchannel_call_;
  }

 private:
  class LbQueuedCallCanceller;

  using LoadBalancedCall::chand;
  using LoadBalancedCall::Commit;

  grpc_polling_entity* pollent() override { return pollent_; }
  grpc_metadata_batch* send_initial_metadata() const override {
    return pending_batches_[0]
        ->payload->send_initial_metadata.send_initial_metadata;
  }

  static size_t GetBatchIndex(grpc_transport_stream_op_batch* batch);
  void PendingBatchesAdd(grpc_transport_stream_op_batch* batch);
  static void FailPendingBatchInCallCombiner(void* arg,
                                             grpc_error_handle error);

  typedef bool (*YieldCallCombinerPredicate)(
      const CallCombinerClosureList& closures);
  static bool YieldCallCombiner(const CallCombinerClosureList& ) {
    return true;
  }
  static bool NoYieldCallCombiner(const CallCombinerClosureList& ) {
    return false;
  }
  static bool YieldCallCombinerIfPendingBatchesFound(
      const CallCombinerClosureList& closures) {
    return closures.size() > 0;
  }

  void PendingBatchesFail(
      grpc_error_handle error,
      YieldCallCombinerPredicate yield_call_combiner_predicate);
  static void ResumePendingBatchInCallCombiner(void* arg,
                                               grpc_error_handle ignored);

  void PendingBatchesResume();

  static void SendInitialMetadataOnComplete(void* arg, grpc_error_handle error);
  static void RecvInitialMetadataReady(void* arg, grpc_error_handle error);
  static void RecvTrailingMetadataReady(void* arg, grpc_error_handle error);

  void TryPick(bool was_queued);

  void OnAddToQueueLocked() override
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&ClientChannelFilter::lb_mu_);

  void RetryPickLocked() override
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&ClientChannelFilter::lb_mu_);

  void CreateSubchannelCall();

  grpc_call_stack* owning_call_;
  CallCombiner* call_combiner_;
  grpc_polling_entity* pollent_;
  grpc_closure* on_call_destruction_complete_;
  std::optional<Slice> peer_string_;

  grpc_error_handle cancel_error_;

  grpc_error_handle failure_error_;

  LbQueuedCallCanceller* lb_call_canceller_
      ABSL_GUARDED_BY(&ClientChannelFilter::lb_mu_) = nullptr;

  RefCountedPtr<SubchannelCall> subchannel_call_;

  grpc_metadata_batch* recv_initial_metadata_ = nullptr;
  grpc_closure recv_initial_metadata_ready_;
  grpc_closure* original_recv_initial_metadata_ready_ = nullptr;

  grpc_metadata_batch* recv_trailing_metadata_ = nullptr;
  grpc_transport_stream_stats* transport_stream_stats_ = nullptr;
  grpc_closure recv_trailing_metadata_ready_;
  grpc_closure* original_recv_trailing_metadata_ready_ = nullptr;

  grpc_transport_stream_op_batch* pending_batches_[MAX_PENDING_BATCHES] = {};
};

}

#endif
