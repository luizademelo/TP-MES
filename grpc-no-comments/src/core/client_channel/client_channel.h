
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_CLIENT_CHANNEL_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_CLIENT_CHANNEL_H

#include <grpc/support/port_platform.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata.h"
#include "src/core/client_channel/client_channel_factory.h"
#include "src/core/client_channel/config_selector.h"
#include "src/core/client_channel/subchannel.h"
#include "src/core/ext/filters/channel_idle/idle_filter_state.h"
#include "src/core/filter/blackboard.h"
#include "src/core/lib/promise/observable.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/resolver/resolver.h"
#include "src/core/service_config/service_config.h"
#include "src/core/util/single_set_ptr.h"

namespace grpc_core {

class ClientChannel : public Channel {
 public:
  using PickerObservable =
      Observable<RefCountedPtr<LoadBalancingPolicy::SubchannelPicker>>;

  class CallDestinationFactory {
   public:
    struct RawPointerChannelArgTag {};

    static absl::string_view ChannelArgName() {
      return "grpc.internal.client_channel_call_destination";
    }

    virtual RefCountedPtr<UnstartedCallDestination> CreateCallDestination(
        PickerObservable) = 0;

   protected:
    ~CallDestinationFactory() = default;
  };

  static absl::StatusOr<RefCountedPtr<Channel>> Create(
      std::string target, ChannelArgs channel_args);

  ClientChannel(std::string target_uri, ChannelArgs args,
                std::string uri_to_resolve,
                RefCountedPtr<ServiceConfig> default_service_config,
                ClientChannelFactory* client_channel_factory,
                CallDestinationFactory* call_destination_factory);

  ~ClientChannel() override;

  void Orphaned() override;

  grpc_call* CreateCall(grpc_call* parent_call, uint32_t propagation_mask,
                        grpc_completion_queue* cq,
                        grpc_pollset_set* ,
                        Slice path, std::optional<Slice> authority,
                        Timestamp deadline, bool registered_method) override;

  void StartCall(UnstartedCallHandler unstarted_handler) override;

  grpc_event_engine::experimental::EventEngine* event_engine() const override {
    return event_engine_.get();
  }

  bool IsLame() const override { return false; }

  bool SupportsConnectivityWatcher() const override { return true; }

  grpc_connectivity_state CheckConnectivityState(bool try_to_connect) override;

  void WatchConnectivityState(grpc_connectivity_state last_observed_state,
                              Timestamp deadline, grpc_completion_queue* cq,
                              void* tag) override;

  void AddConnectivityWatcher(
      grpc_connectivity_state initial_state,
      OrphanablePtr<AsyncConnectivityStateWatcherInterface> watcher) override;
  void RemoveConnectivityWatcher(
      AsyncConnectivityStateWatcherInterface* watcher) override;

  void GetInfo(const grpc_channel_info* channel_info) override;

  void ResetConnectionBackoff() override;

  void Ping(grpc_completion_queue* cq, void* tag) override;

  struct RawPointerChannelArgTag {};
  static absl::string_view ChannelArgName() {
    return "grpc.internal.client_channel";
  }

 private:
  class ClientChannelControlHelper;
  class ResolverResultHandler;
  class SubchannelWrapper;

  void CreateResolverLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);
  void DestroyResolverAndLbPolicyLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void TryToConnectLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

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

  void UpdateServiceConfigInControlPlaneLocked(
      RefCountedPtr<ServiceConfig> service_config,
      RefCountedPtr<ConfigSelector> config_selector, std::string lb_policy_name)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void UpdateServiceConfigInDataPlaneLocked(const ChannelArgs& args)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void UpdateStateLocked(grpc_connectivity_state state,
                         const absl::Status& status, const char* reason)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void UpdateStateAndPickerLocked(
      grpc_connectivity_state state, const absl::Status& status,
      const char* reason,
      RefCountedPtr<LoadBalancingPolicy::SubchannelPicker> picker)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(*work_serializer_);

  void StartIdleTimer();

  absl::Status ApplyServiceConfigToCall(
      ConfigSelector& config_selector,
      ClientMetadata& client_initial_metadata) const;

  const std::string default_authority_;
  const std::shared_ptr<GlobalStatsPluginRegistry::StatsPluginGroup>
      stats_plugin_group_;
  const ChannelArgs channel_args_;
  const std::shared_ptr<grpc_event_engine::experimental::EventEngine>
      event_engine_;
  const std::string uri_to_resolve_;
  const size_t service_config_parser_index_;
  const RefCountedPtr<ServiceConfig> default_service_config_;
  ClientChannelFactory* const client_channel_factory_;
  channelz::ChannelNode* const channelz_node_;

  const Duration idle_timeout_;
  IdleFilterState idle_state_{false};
  SingleSetPtr<Activity, typename ActivityPtr::deleter_type> idle_activity_;

  struct ResolverDataForCalls {
    RefCountedPtr<ConfigSelector> config_selector;
    RefCountedPtr<UnstartedCallDestination> call_destination;
  };
  Observable<absl::StatusOr<ResolverDataForCalls>> resolver_data_for_calls_;

  PickerObservable picker_;
  const RefCountedPtr<UnstartedCallDestination> call_destination_;

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
  absl::Status disconnect_error_ ABSL_GUARDED_BY(*work_serializer_);

  Mutex info_mu_;
  std::string info_lb_policy_name_ ABSL_GUARDED_BY(info_mu_);
  std::string info_service_config_json_ ABSL_GUARDED_BY(info_mu_);
};

}

#endif
