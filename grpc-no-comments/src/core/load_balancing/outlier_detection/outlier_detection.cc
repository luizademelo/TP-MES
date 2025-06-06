
// Copyright 2022 gRPC authors.

#include "src/core/load_balancing/outlier_detection/outlier_detection.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <stddef.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/meta/type_traits.h"
#include "absl/random/random.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/client_channel/subchannel_interface_internal.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/load_balancing/child_policy_handler.h"
#include "src/core/load_balancing/delegating_helper.h"
#include "src/core/load_balancing/health_check_client_internal.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_factory.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/json/json.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/shared_bit_gen.h"
#include "src/core/util/sync.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/validation_errors.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

namespace {

using ::grpc_event_engine::experimental::EventEngine;

constexpr absl::string_view kOutlierDetection =
    "outlier_detection_experimental";

class OutlierDetectionLbConfig final : public LoadBalancingPolicy::Config {
 public:
  OutlierDetectionLbConfig(
      OutlierDetectionConfig outlier_detection_config,
      RefCountedPtr<LoadBalancingPolicy::Config> child_policy)
      : outlier_detection_config_(outlier_detection_config),
        child_policy_(std::move(child_policy)) {}

  absl::string_view name() const override { return kOutlierDetection; }

  bool CountingEnabled() const {
    return outlier_detection_config_.success_rate_ejection.has_value() ||
           outlier_detection_config_.failure_percentage_ejection.has_value();
  }

  const OutlierDetectionConfig& outlier_detection_config() const {
    return outlier_detection_config_;
  }

  RefCountedPtr<LoadBalancingPolicy::Config> child_policy() const {
    return child_policy_;
  }

 private:
  OutlierDetectionConfig outlier_detection_config_;
  RefCountedPtr<LoadBalancingPolicy::Config> child_policy_;
};

class OutlierDetectionLb final : public LoadBalancingPolicy {
 public:
  explicit OutlierDetectionLb(Args args);

  absl::string_view name() const override { return kOutlierDetection; }

  absl::Status UpdateLocked(UpdateArgs args) override;
  void ExitIdleLocked() override;
  void ResetBackoffLocked() override;

 private:
  class SubchannelState;
  class EndpointState;

  class SubchannelWrapper final : public DelegatingSubchannel {
   public:
    SubchannelWrapper(std::shared_ptr<WorkSerializer> work_serializer,
                      RefCountedPtr<SubchannelState> subchannel_state,
                      RefCountedPtr<SubchannelInterface> subchannel)
        : DelegatingSubchannel(std::move(subchannel)),
          work_serializer_(std::move(work_serializer)),
          subchannel_state_(std::move(subchannel_state)) {
      if (subchannel_state_ != nullptr) {
        subchannel_state_->AddSubchannel(this);
        if (subchannel_state_->endpoint_state()->ejection_time().has_value()) {
          ejected_ = true;
        }
      }
    }

    void Eject();

    void Uneject();

    void AddDataWatcher(std::unique_ptr<DataWatcherInterface> watcher) override;

    void CancelDataWatcher(DataWatcherInterface* watcher) override;

    RefCountedPtr<EndpointState> endpoint_state() const {
      if (subchannel_state_ == nullptr) return nullptr;
      return subchannel_state_->endpoint_state();
    }

   private:
    class WatcherWrapper final
        : public SubchannelInterface::ConnectivityStateWatcherInterface {
     public:
      WatcherWrapper(WeakRefCountedPtr<SubchannelWrapper> subchannel_wrapper,
                     std::shared_ptr<
                         SubchannelInterface::ConnectivityStateWatcherInterface>
                         health_watcher,
                     bool ejected)
          : subchannel_wrapper_(std::move(subchannel_wrapper)),
            watcher_(std::move(health_watcher)),
            ejected_(ejected) {}

      void Eject() {
        ejected_ = true;
        if (last_seen_state_.has_value()) {
          watcher_->OnConnectivityStateChange(
              GRPC_CHANNEL_TRANSIENT_FAILURE,
              absl::UnavailableError(
                  absl::StrCat(subchannel_wrapper_->address(),
                               ": subchannel ejected by outlier detection")));
        }
      }

      void Uneject() {
        ejected_ = false;
        if (last_seen_state_.has_value()) {
          watcher_->OnConnectivityStateChange(*last_seen_state_,
                                              last_seen_status_);
        }
      }

      void OnConnectivityStateChange(grpc_connectivity_state new_state,
                                     absl::Status status) override {
        const bool send_update = !last_seen_state_.has_value() || !ejected_;
        last_seen_state_ = new_state;
        last_seen_status_ = status;
        if (send_update) {
          if (ejected_) {
            new_state = GRPC_CHANNEL_TRANSIENT_FAILURE;
            status = absl::UnavailableError(
                absl::StrCat(subchannel_wrapper_->address(),
                             ": subchannel ejected by outlier detection"));
          }
          watcher_->OnConnectivityStateChange(new_state, status);
        }
      }

      grpc_pollset_set* interested_parties() override {
        return watcher_->interested_parties();
      }

     private:
      WeakRefCountedPtr<SubchannelWrapper> subchannel_wrapper_;
      std::shared_ptr<SubchannelInterface::ConnectivityStateWatcherInterface>
          watcher_;
      std::optional<grpc_connectivity_state> last_seen_state_;
      absl::Status last_seen_status_;
      bool ejected_;
    };

    void Orphaned() override {
      work_serializer_->Run([self = WeakRefAsSubclass<SubchannelWrapper>()]() {
        if (self->subchannel_state_ != nullptr) {
          self->subchannel_state_->RemoveSubchannel(self.get());
        }
      });
    }

    std::shared_ptr<WorkSerializer> work_serializer_;
    RefCountedPtr<SubchannelState> subchannel_state_;
    bool ejected_ = false;
    WatcherWrapper* watcher_wrapper_ = nullptr;
  };

  class SubchannelState final : public RefCounted<SubchannelState> {
   public:
    void AddSubchannel(SubchannelWrapper* wrapper) {
      subchannels_.insert(wrapper);
    }

    void RemoveSubchannel(SubchannelWrapper* wrapper) {
      subchannels_.erase(wrapper);
    }

    RefCountedPtr<EndpointState> endpoint_state() {
      MutexLock lock(&mu_);
      return endpoint_state_;
    }

    void set_endpoint_state(RefCountedPtr<EndpointState> endpoint_state) {
      MutexLock lock(&mu_);
      endpoint_state_ = std::move(endpoint_state);
    }

    void Eject() {

      for (auto it = subchannels_.begin(); it != subchannels_.end();) {
        SubchannelWrapper* subchannel = *it;
        ++it;
        subchannel->Eject();
      }
    }

    void Uneject() {
      for (auto& subchannel : subchannels_) {
        subchannel->Uneject();
      }
    }

   private:
    std::set<SubchannelWrapper*> subchannels_;
    Mutex mu_;
    RefCountedPtr<EndpointState> endpoint_state_ ABSL_GUARDED_BY(mu_);
  };

  class EndpointState final : public RefCounted<EndpointState> {
   public:
    explicit EndpointState(std::set<SubchannelState*> subchannels)
        : subchannels_(std::move(subchannels)) {
      for (SubchannelState* subchannel : subchannels_) {
        subchannel->set_endpoint_state(Ref());
      }
    }

    void RotateBucket() {
      backup_bucket_->successes = 0;
      backup_bucket_->failures = 0;
      current_bucket_.swap(backup_bucket_);
      active_bucket_.store(current_bucket_.get());
    }

    std::optional<std::pair<double, uint64_t>> GetSuccessRateAndVolume() {
      uint64_t total_request =
          backup_bucket_->successes + backup_bucket_->failures;
      if (total_request == 0) {
        return std::nullopt;
      }
      double success_rate =
          backup_bucket_->successes * 100.0 /
          (backup_bucket_->successes + backup_bucket_->failures);
      return {
          {success_rate, backup_bucket_->successes + backup_bucket_->failures}};
    }

    void AddSuccessCount() { active_bucket_.load()->successes.fetch_add(1); }

    void AddFailureCount() { active_bucket_.load()->failures.fetch_add(1); }

    std::optional<Timestamp> ejection_time() const { return ejection_time_; }

    void Eject(const Timestamp& time) {
      ejection_time_ = time;
      ++multiplier_;
      for (SubchannelState* subchannel_state : subchannels_) {
        subchannel_state->Eject();
      }
    }

    void Uneject() {
      ejection_time_.reset();
      for (SubchannelState* subchannel_state : subchannels_) {
        subchannel_state->Uneject();
      }
    }

    bool MaybeUneject(uint64_t base_ejection_time_in_millis,
                      uint64_t max_ejection_time_in_millis) {
      if (!ejection_time_.has_value()) {
        if (multiplier_ > 0) {
          --multiplier_;
        }
      } else {
        CHECK(ejection_time_.has_value());
        auto change_time = ejection_time_.value() +
                           Duration::Milliseconds(std::min(
                               base_ejection_time_in_millis * multiplier_,
                               std::max(base_ejection_time_in_millis,
                                        max_ejection_time_in_millis)));
        if (change_time < Timestamp::Now()) {
          Uneject();
          return true;
        }
      }
      return false;
    }

    void DisableEjection() {
      if (ejection_time_.has_value()) Uneject();
      multiplier_ = 0;
    }

   private:
    struct Bucket {
      std::atomic<uint64_t> successes;
      std::atomic<uint64_t> failures;
    };

    const std::set<SubchannelState*> subchannels_;

    std::unique_ptr<Bucket> current_bucket_ = std::make_unique<Bucket>();
    std::unique_ptr<Bucket> backup_bucket_ = std::make_unique<Bucket>();

    std::atomic<Bucket*> active_bucket_{current_bucket_.get()};
    uint32_t multiplier_ = 0;
    std::optional<Timestamp> ejection_time_;
  };

  class Picker final : public SubchannelPicker {
   public:
    Picker(OutlierDetectionLb* outlier_detection_lb,
           RefCountedPtr<SubchannelPicker> picker, bool counting_enabled);

    PickResult Pick(PickArgs args) override;

   private:
    class SubchannelCallTracker;
    RefCountedPtr<SubchannelPicker> picker_;
    bool counting_enabled_;
  };

  class Helper final
      : public ParentOwningDelegatingChannelControlHelper<OutlierDetectionLb> {
   public:
    explicit Helper(RefCountedPtr<OutlierDetectionLb> outlier_detection_policy)
        : ParentOwningDelegatingChannelControlHelper(
              std::move(outlier_detection_policy)) {}

    RefCountedPtr<SubchannelInterface> CreateSubchannel(
        const grpc_resolved_address& address,
        const ChannelArgs& per_address_args, const ChannelArgs& args) override;
    void UpdateState(grpc_connectivity_state state, const absl::Status& status,
                     RefCountedPtr<SubchannelPicker> picker) override;
  };

  class EjectionTimer final : public InternallyRefCounted<EjectionTimer> {
   public:
    EjectionTimer(RefCountedPtr<OutlierDetectionLb> parent,
                  Timestamp start_time);

    void Orphan() override;

    Timestamp StartTime() const { return start_time_; }

   private:
    void OnTimerLocked();

    RefCountedPtr<OutlierDetectionLb> parent_;
    std::optional<EventEngine::TaskHandle> timer_handle_;
    Timestamp start_time_;
  };

  ~OutlierDetectionLb() override;

  void ShutdownLocked() override;

  OrphanablePtr<LoadBalancingPolicy> CreateChildPolicyLocked(
      const ChannelArgs& args);

  void MaybeUpdatePickerLocked();

  RefCountedPtr<OutlierDetectionLbConfig> config_;

  bool shutting_down_ = false;

  OrphanablePtr<LoadBalancingPolicy> child_policy_;

  grpc_connectivity_state state_ = GRPC_CHANNEL_IDLE;
  absl::Status status_;
  RefCountedPtr<SubchannelPicker> picker_;
  std::map<EndpointAddressSet, RefCountedPtr<EndpointState>>
      endpoint_state_map_;
  std::map<grpc_resolved_address, RefCountedPtr<SubchannelState>,
           ResolvedAddressLessThan>
      subchannel_state_map_;
  OrphanablePtr<EjectionTimer> ejection_timer_;
};

void OutlierDetectionLb::SubchannelWrapper::Eject() {
  ejected_ = true;
  if (watcher_wrapper_ != nullptr) watcher_wrapper_->Eject();
}

void OutlierDetectionLb::SubchannelWrapper::Uneject() {
  ejected_ = false;
  if (watcher_wrapper_ != nullptr) watcher_wrapper_->Uneject();
}

void OutlierDetectionLb::SubchannelWrapper::AddDataWatcher(
    std::unique_ptr<DataWatcherInterface> watcher) {
  auto* w = static_cast<InternalSubchannelDataWatcherInterface*>(watcher.get());
  if (w->type() == HealthProducer::Type()) {
    auto* health_watcher = static_cast<HealthWatcher*>(watcher.get());
    auto watcher_wrapper = std::make_shared<WatcherWrapper>(
        WeakRefAsSubclass<SubchannelWrapper>(), health_watcher->TakeWatcher(),
        ejected_);
    watcher_wrapper_ = watcher_wrapper.get();
    health_watcher->SetWatcher(std::move(watcher_wrapper));
  }
  DelegatingSubchannel::AddDataWatcher(std::move(watcher));
}

void OutlierDetectionLb::SubchannelWrapper::CancelDataWatcher(
    DataWatcherInterface* watcher) {
  auto* w = static_cast<InternalSubchannelDataWatcherInterface*>(watcher);
  if (w->type() == HealthProducer::Type()) watcher_wrapper_ = nullptr;
  DelegatingSubchannel::CancelDataWatcher(watcher);
}

class OutlierDetectionLb::Picker::SubchannelCallTracker final
    : public LoadBalancingPolicy::SubchannelCallTrackerInterface {
 public:
  SubchannelCallTracker(
      std::unique_ptr<LoadBalancingPolicy::SubchannelCallTrackerInterface>
          original_subchannel_call_tracker,
      RefCountedPtr<EndpointState> endpoint_state)
      : original_subchannel_call_tracker_(
            std::move(original_subchannel_call_tracker)),
        endpoint_state_(std::move(endpoint_state)) {}

  ~SubchannelCallTracker() override {
    endpoint_state_.reset(DEBUG_LOCATION, "SubchannelCallTracker");
  }

  void Start() override {

    if (original_subchannel_call_tracker_ != nullptr) {
      original_subchannel_call_tracker_->Start();
    }
  }

  void Finish(FinishArgs args) override {

    if (original_subchannel_call_tracker_ != nullptr) {
      original_subchannel_call_tracker_->Finish(args);
    }

    if (args.status.ok()) {
      endpoint_state_->AddSuccessCount();
    } else {
      endpoint_state_->AddFailureCount();
    }
  }

 private:
  std::unique_ptr<LoadBalancingPolicy::SubchannelCallTrackerInterface>
      original_subchannel_call_tracker_;
  RefCountedPtr<EndpointState> endpoint_state_;
};

OutlierDetectionLb::Picker::Picker(OutlierDetectionLb* outlier_detection_lb,
                                   RefCountedPtr<SubchannelPicker> picker,
                                   bool counting_enabled)
    : picker_(std::move(picker)), counting_enabled_(counting_enabled) {
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << outlier_detection_lb
      << "] constructed new picker " << this << " and counting " << "is "
      << (counting_enabled ? "enabled" : "disabled");
}

LoadBalancingPolicy::PickResult OutlierDetectionLb::Picker::Pick(
    LoadBalancingPolicy::PickArgs args) {
  if (picker_ == nullptr) {
    return PickResult::Fail(absl::InternalError(
        "outlier_detection picker not given any child picker"));
  }

  PickResult result = picker_->Pick(args);
  auto* complete_pick = std::get_if<PickResult::Complete>(&result.result);
  if (complete_pick != nullptr) {
    auto* subchannel_wrapper =
        static_cast<SubchannelWrapper*>(complete_pick->subchannel.get());

    if (counting_enabled_) {
      auto endpoint_state = subchannel_wrapper->endpoint_state();
      if (endpoint_state != nullptr) {
        complete_pick->subchannel_call_tracker =
            std::make_unique<SubchannelCallTracker>(
                std::move(complete_pick->subchannel_call_tracker),
                std::move(endpoint_state));
      }
    }

    complete_pick->subchannel = subchannel_wrapper->wrapped_subchannel();
  }
  return result;
}

OutlierDetectionLb::OutlierDetectionLb(Args args)
    : LoadBalancingPolicy(std::move(args)) {
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << this << "] created";
}

OutlierDetectionLb::~OutlierDetectionLb() {
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << this
      << "] destroying outlier_detection LB policy";
}

void OutlierDetectionLb::ShutdownLocked() {
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << this << "] shutting down";
  ejection_timer_.reset();
  shutting_down_ = true;

  if (child_policy_ != nullptr) {
    grpc_pollset_set_del_pollset_set(child_policy_->interested_parties(),
                                     interested_parties());
    child_policy_.reset();
  }

  picker_.reset();
}

void OutlierDetectionLb::ExitIdleLocked() {
  if (child_policy_ != nullptr) child_policy_->ExitIdleLocked();
}

void OutlierDetectionLb::ResetBackoffLocked() {
  if (child_policy_ != nullptr) child_policy_->ResetBackoffLocked();
}

absl::Status OutlierDetectionLb::UpdateLocked(UpdateArgs args) {
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << this << "] Received update";
  auto old_config = std::move(config_);

  config_ = args.config.TakeAsSubclass<OutlierDetectionLbConfig>();

  if (!config_->CountingEnabled()) {

    GRPC_TRACE_LOG(outlier_detection_lb, INFO)
        << "[outlier_detection_lb " << this
        << "] counting disabled, cancelling timer";
    ejection_timer_.reset();
  } else if (ejection_timer_ == nullptr) {

    GRPC_TRACE_LOG(outlier_detection_lb, INFO)
        << "[outlier_detection_lb " << this << "] starting timer";
    ejection_timer_ = MakeOrphanable<EjectionTimer>(
        RefAsSubclass<OutlierDetectionLb>(), Timestamp::Now());
    for (const auto& [_, endpoint_state] : endpoint_state_map_) {
      endpoint_state->RotateBucket();
    }
  } else if (old_config->outlier_detection_config().interval !=
             config_->outlier_detection_config().interval) {

    GRPC_TRACE_LOG(outlier_detection_lb, INFO)
        << "[outlier_detection_lb " << this
        << "] interval changed, replacing timer";
    ejection_timer_ = MakeOrphanable<EjectionTimer>(
        RefAsSubclass<OutlierDetectionLb>(), ejection_timer_->StartTime());
  }

  if (args.addresses.ok()) {
    std::set<EndpointAddressSet> current_endpoints;
    std::set<grpc_resolved_address, ResolvedAddressLessThan> current_addresses;
    (*args.addresses)->ForEach([&](const EndpointAddresses& endpoint) {
      EndpointAddressSet key(endpoint.addresses());
      current_endpoints.emplace(key);
      for (const grpc_resolved_address& address : endpoint.addresses()) {
        current_addresses.emplace(address);
      }

      auto it = endpoint_state_map_.find(key);
      if (it == endpoint_state_map_.end()) {
        GRPC_TRACE_LOG(outlier_detection_lb, INFO)
            << "[outlier_detection_lb " << this
            << "] adding endpoint entry for " << key.ToString();

        std::set<SubchannelState*> subchannels;
        for (const grpc_resolved_address& address : endpoint.addresses()) {
          auto it2 = subchannel_state_map_.find(address);
          if (it2 == subchannel_state_map_.end()) {
            if (GRPC_TRACE_FLAG_ENABLED(outlier_detection_lb)) {
              std::string address_str = grpc_sockaddr_to_string(&address, false)
                                            .value_or("<unknown>");
              LOG(INFO) << "[outlier_detection_lb " << this
                        << "] adding address entry for " << address_str;
            }
            it2 = subchannel_state_map_
                      .emplace(address, MakeRefCounted<SubchannelState>())
                      .first;
          }
          subchannels.insert(it2->second.get());
        }

        endpoint_state_map_.emplace(
            key, MakeRefCounted<EndpointState>(std::move(subchannels)));
      } else if (!config_->CountingEnabled()) {

        GRPC_TRACE_LOG(outlier_detection_lb, INFO)
            << "[outlier_detection_lb " << this
            << "] counting disabled; disabling ejection for " << key.ToString();
        it->second->DisableEjection();
      }
    });

    for (auto it = subchannel_state_map_.begin();
         it != subchannel_state_map_.end();) {
      auto& [address, subchannel_state] = *it;
      if (current_addresses.find(address) == current_addresses.end()) {
        if (GRPC_TRACE_FLAG_ENABLED(outlier_detection_lb)) {
          std::string address_str =
              grpc_sockaddr_to_string(&address, false).value_or("<unknown>");
          LOG(INFO) << "[outlier_detection_lb " << this
                    << "] removing subchannel map entry " << address_str;
        }

        subchannel_state->set_endpoint_state(nullptr);
        it = subchannel_state_map_.erase(it);
      } else {
        ++it;
      }
    }

    for (auto it = endpoint_state_map_.begin();
         it != endpoint_state_map_.end();) {
      auto& endpoint_addresses = it->first;
      if (current_endpoints.find(endpoint_addresses) ==
          current_endpoints.end()) {
        GRPC_TRACE_LOG(outlier_detection_lb, INFO)
            << "[outlier_detection_lb " << this
            << "] removing endpoint map entry "
            << endpoint_addresses.ToString();
        it = endpoint_state_map_.erase(it);
      } else {
        ++it;
      }
    }
  }

  if (child_policy_ == nullptr) {
    child_policy_ = CreateChildPolicyLocked(args.args);
  }

  UpdateArgs update_args;
  update_args.addresses = std::move(args.addresses);
  update_args.resolution_note = std::move(args.resolution_note);
  update_args.config = config_->child_policy();
  update_args.args = std::move(args.args);
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << this << "] Updating child policy handler "
      << child_policy_.get();
  return child_policy_->UpdateLocked(std::move(update_args));
}

void OutlierDetectionLb::MaybeUpdatePickerLocked() {
  if (picker_ != nullptr) {
    auto outlier_detection_picker =
        MakeRefCounted<Picker>(this, picker_, config_->CountingEnabled());
    GRPC_TRACE_LOG(outlier_detection_lb, INFO)
        << "[outlier_detection_lb " << this
        << "] updating connectivity: state=" << ConnectivityStateName(state_)
        << " status=(" << status_
        << ") picker=" << outlier_detection_picker.get();
    channel_control_helper()->UpdateState(state_, status_,
                                          std::move(outlier_detection_picker));
  }
}

OrphanablePtr<LoadBalancingPolicy> OutlierDetectionLb::CreateChildPolicyLocked(
    const ChannelArgs& args) {
  LoadBalancingPolicy::Args lb_policy_args;
  lb_policy_args.work_serializer = work_serializer();
  lb_policy_args.args = args;
  lb_policy_args.channel_control_helper = std::make_unique<Helper>(
      RefAsSubclass<OutlierDetectionLb>(DEBUG_LOCATION, "Helper"));
  OrphanablePtr<LoadBalancingPolicy> lb_policy =
      MakeOrphanable<ChildPolicyHandler>(std::move(lb_policy_args),
                                         &outlier_detection_lb_trace);
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << this
      << "] Created new child policy handler " << lb_policy.get();

  grpc_pollset_set_add_pollset_set(lb_policy->interested_parties(),
                                   interested_parties());
  return lb_policy;
}

RefCountedPtr<SubchannelInterface> OutlierDetectionLb::Helper::CreateSubchannel(
    const grpc_resolved_address& address, const ChannelArgs& per_address_args,
    const ChannelArgs& args) {
  if (parent()->shutting_down_) return nullptr;
  RefCountedPtr<SubchannelState> subchannel_state;
  auto it = parent()->subchannel_state_map_.find(address);
  if (it != parent()->subchannel_state_map_.end()) {
    subchannel_state = it->second->Ref();
  }
  if (GRPC_TRACE_FLAG_ENABLED(outlier_detection_lb)) {
    std::string address_str =
        grpc_sockaddr_to_string(&address, false).value_or("<unknown>");
    LOG(INFO) << "[outlier_detection_lb " << parent()
              << "] creating subchannel for " << address_str
              << ", subchannel state " << subchannel_state.get();
  }
  auto subchannel = MakeRefCounted<SubchannelWrapper>(
      parent()->work_serializer(), subchannel_state,
      parent()->channel_control_helper()->CreateSubchannel(
          address, per_address_args, args));
  if (subchannel_state != nullptr) {
    subchannel_state->AddSubchannel(subchannel.get());
  }
  return subchannel;
}

void OutlierDetectionLb::Helper::UpdateState(
    grpc_connectivity_state state, const absl::Status& status,
    RefCountedPtr<SubchannelPicker> picker) {
  if (parent()->shutting_down_) return;
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << parent()
      << "] child connectivity state update: state="
      << ConnectivityStateName(state) << " (" << status
      << ") picker=" << picker.get();

  parent()->state_ = state;
  parent()->status_ = status;
  parent()->picker_ = std::move(picker);

  parent()->MaybeUpdatePickerLocked();
}

OutlierDetectionLb::EjectionTimer::EjectionTimer(
    RefCountedPtr<OutlierDetectionLb> parent, Timestamp start_time)
    : parent_(std::move(parent)), start_time_(start_time) {
  auto interval = parent_->config_->outlier_detection_config().interval;
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << parent_.get()
      << "] ejection timer will run in " << interval.ToString();
  timer_handle_ = parent_->channel_control_helper()->GetEventEngine()->RunAfter(
      interval, [self = Ref(DEBUG_LOCATION, "EjectionTimer")]() mutable {
        ExecCtx exec_ctx;
        auto self_ptr = self.get();
        self_ptr->parent_->work_serializer()->Run(
            [self = std::move(self)]() { self->OnTimerLocked(); });
      });
}

void OutlierDetectionLb::EjectionTimer::Orphan() {
  if (timer_handle_.has_value()) {
    parent_->channel_control_helper()->GetEventEngine()->Cancel(*timer_handle_);
    timer_handle_.reset();
  }
  Unref();
}

void OutlierDetectionLb::EjectionTimer::OnTimerLocked() {
  if (!timer_handle_.has_value()) return;
  timer_handle_.reset();
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << parent_.get()
      << "] ejection timer running";
  std::map<EndpointState*, double> success_rate_ejection_candidates;
  std::map<EndpointState*, double> failure_percentage_ejection_candidates;
  size_t ejected_host_count = 0;
  double success_rate_sum = 0;
  auto time_now = Timestamp::Now();
  auto& config = parent_->config_->outlier_detection_config();
  for (auto& [_, endpoint_state] : parent_->endpoint_state_map_) {

    endpoint_state->RotateBucket();

    if (endpoint_state->ejection_time().has_value()) ++ejected_host_count;
    std::optional<std::pair<double, uint64_t>> host_success_rate_and_volume =
        endpoint_state->GetSuccessRateAndVolume();
    if (!host_success_rate_and_volume.has_value()) continue;
    auto [success_rate, request_volume] = *host_success_rate_and_volume;
    if (config.success_rate_ejection.has_value()) {
      if (request_volume >= config.success_rate_ejection->request_volume) {
        success_rate_ejection_candidates[endpoint_state.get()] = success_rate;
        success_rate_sum += success_rate;
      }
    }
    if (config.failure_percentage_ejection.has_value()) {
      if (request_volume >=
          config.failure_percentage_ejection->request_volume) {
        failure_percentage_ejection_candidates[endpoint_state.get()] =
            success_rate;
      }
    }
  }
  GRPC_TRACE_LOG(outlier_detection_lb, INFO)
      << "[outlier_detection_lb " << parent_.get() << "] found "
      << success_rate_ejection_candidates.size()
      << " success rate candidates and "
      << failure_percentage_ejection_candidates.size()
      << " failure percentage candidates; ejected_host_count="
      << ejected_host_count
      << "; success_rate_sum=" << absl::StrFormat("%.3f", success_rate_sum);

  if (!success_rate_ejection_candidates.empty() &&
      success_rate_ejection_candidates.size() >=
          config.success_rate_ejection->minimum_hosts) {
    GRPC_TRACE_LOG(outlier_detection_lb, INFO)
        << "[outlier_detection_lb " << parent_.get()
        << "] running success rate algorithm: " << "stdev_factor="
        << config.success_rate_ejection->stdev_factor
        << ", enforcement_percentage="
        << config.success_rate_ejection->enforcement_percentage;

    double mean = success_rate_sum / success_rate_ejection_candidates.size();
    double variance = 0;
    for (const auto& [_, success_rate] : success_rate_ejection_candidates) {
      variance += std::pow(success_rate - mean, 2);
    }
    variance /= success_rate_ejection_candidates.size();
    double stdev = std::sqrt(variance);
    const double success_rate_stdev_factor =
        static_cast<double>(config.success_rate_ejection->stdev_factor) / 1000;
    double ejection_threshold = mean - (stdev * success_rate_stdev_factor);
    GRPC_TRACE_LOG(outlier_detection_lb, INFO)
        << "[outlier_detection_lb " << parent_.get() << "] stdev=" << stdev
        << ", ejection_threshold=" << ejection_threshold;
    for (auto& [endpoint_state, success_rate] :
         success_rate_ejection_candidates) {
      GRPC_TRACE_LOG(outlier_detection_lb, INFO)
          << "[outlier_detection_lb " << parent_.get()
          << "] checking candidate " << endpoint_state
          << ": success_rate=" << success_rate;
      if (success_rate < ejection_threshold) {
        SharedBitGen bit_gen;
        uint32_t random_key = absl::Uniform(bit_gen, 1, 100);
        double current_percent =
            100.0 * ejected_host_count / parent_->endpoint_state_map_.size();
        GRPC_TRACE_LOG(outlier_detection_lb, INFO)
            << "[outlier_detection_lb " << parent_.get()
            << "] random_key=" << random_key
            << " ejected_host_count=" << ejected_host_count
            << " current_percent=" << absl::StrFormat("%.3f", current_percent);
        if (random_key < config.success_rate_ejection->enforcement_percentage &&
            (ejected_host_count == 0 ||
             (current_percent < config.max_ejection_percent))) {

          GRPC_TRACE_LOG(outlier_detection_lb, INFO)
              << "[outlier_detection_lb " << parent_.get()
              << "] ejecting candidate";
          endpoint_state->Eject(time_now);
          ++ejected_host_count;
        }
      }
    }
  }

  if (!failure_percentage_ejection_candidates.empty() &&
      failure_percentage_ejection_candidates.size() >=
          config.failure_percentage_ejection->minimum_hosts) {
    GRPC_TRACE_LOG(outlier_detection_lb, INFO)
        << "[outlier_detection_lb " << parent_.get()
        << "] running failure percentage algorithm: " << "threshold="
        << config.failure_percentage_ejection->threshold
        << ", enforcement_percentage="
        << config.failure_percentage_ejection->enforcement_percentage;
    for (auto& [endpoint_state, success_rate] :
         failure_percentage_ejection_candidates) {
      GRPC_TRACE_LOG(outlier_detection_lb, INFO)
          << "[outlier_detection_lb " << parent_.get()
          << "] checking candidate " << endpoint_state
          << ": success_rate=" << success_rate;

      if (endpoint_state->ejection_time().has_value()) continue;
      if ((100.0 - success_rate) >
          config.failure_percentage_ejection->threshold) {
        uint32_t random_key = absl::Uniform(SharedBitGen(), 1, 100);
        double current_percent =
            100.0 * ejected_host_count / parent_->endpoint_state_map_.size();
        GRPC_TRACE_LOG(outlier_detection_lb, INFO)
            << "[outlier_detection_lb " << parent_.get()
            << "] random_key=" << random_key
            << " ejected_host_count=" << ejected_host_count
            << " current_percent=" << current_percent;
        if (random_key <
                config.failure_percentage_ejection->enforcement_percentage &&
            (ejected_host_count == 0 ||
             (current_percent < config.max_ejection_percent))) {

          GRPC_TRACE_LOG(outlier_detection_lb, INFO)
              << "[outlier_detection_lb " << parent_.get()
              << "] ejecting candidate";
          endpoint_state->Eject(time_now);
          ++ejected_host_count;
        }
      }
    }
  }

  for (auto& [address_set, endpoint_state] : parent_->endpoint_state_map_) {
    const bool unejected = endpoint_state->MaybeUneject(
        config.base_ejection_time.millis(), config.max_ejection_time.millis());
    if (unejected && GRPC_TRACE_FLAG_ENABLED(outlier_detection_lb)) {
      LOG(INFO) << "[outlier_detection_lb " << parent_.get()
                << "] unejected endpoint " << address_set.ToString() << " ("
                << endpoint_state.get() << ")";
    }
  }
  parent_->ejection_timer_ =
      MakeOrphanable<EjectionTimer>(parent_, Timestamp::Now());
}

class OutlierDetectionLbFactory final : public LoadBalancingPolicyFactory {
 public:
  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args args) const override {
    return MakeOrphanable<OutlierDetectionLb>(std::move(args));
  }

  absl::string_view name() const override { return kOutlierDetection; }

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& json) const override {
    ValidationErrors errors;
    OutlierDetectionConfig outlier_detection_config;
    RefCountedPtr<LoadBalancingPolicy::Config> child_policy;
    {
      outlier_detection_config =
          LoadFromJson<OutlierDetectionConfig>(json, JsonArgs(), &errors);

      {
        ValidationErrors::ScopedField field(&errors, ".childPolicy");
        auto it = json.object().find("childPolicy");
        if (it == json.object().end()) {
          errors.AddError("field not present");
        } else if (auto child_policy_config =
                       CoreConfiguration::Get()
                           .lb_policy_registry()
                           .ParseLoadBalancingConfig(it->second);
                   !child_policy_config.ok()) {
          errors.AddError(child_policy_config.status().message());
        } else {
          child_policy = std::move(*child_policy_config);
        }
      }
    }
    if (!errors.ok()) {
      return errors.status(
          absl::StatusCode::kInvalidArgument,
          "errors validating outlier_detection LB policy config");
    }
    return MakeRefCounted<OutlierDetectionLbConfig>(outlier_detection_config,
                                                    std::move(child_policy));
  }
};

}

const JsonLoaderInterface*
OutlierDetectionConfig::SuccessRateEjection::JsonLoader(const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<SuccessRateEjection>()
          .OptionalField("stdevFactor", &SuccessRateEjection::stdev_factor)
          .OptionalField("enforcementPercentage",
                         &SuccessRateEjection::enforcement_percentage)
          .OptionalField("minimumHosts", &SuccessRateEjection::minimum_hosts)
          .OptionalField("requestVolume", &SuccessRateEjection::request_volume)
          .Finish();
  return loader;
}

void OutlierDetectionConfig::SuccessRateEjection::JsonPostLoad(
    const Json&, const JsonArgs&, ValidationErrors* errors) {
  if (enforcement_percentage > 100) {
    ValidationErrors::ScopedField field(errors, ".enforcement_percentage");
    errors->AddError("value must be <= 100");
  }
}

const JsonLoaderInterface*
OutlierDetectionConfig::FailurePercentageEjection::JsonLoader(const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<FailurePercentageEjection>()
          .OptionalField("threshold", &FailurePercentageEjection::threshold)
          .OptionalField("enforcementPercentage",
                         &FailurePercentageEjection::enforcement_percentage)
          .OptionalField("minimumHosts",
                         &FailurePercentageEjection::minimum_hosts)
          .OptionalField("requestVolume",
                         &FailurePercentageEjection::request_volume)
          .Finish();
  return loader;
}

void OutlierDetectionConfig::FailurePercentageEjection::JsonPostLoad(
    const Json&, const JsonArgs&, ValidationErrors* errors) {
  if (enforcement_percentage > 100) {
    ValidationErrors::ScopedField field(errors, ".enforcement_percentage");
    errors->AddError("value must be <= 100");
  }
  if (threshold > 100) {
    ValidationErrors::ScopedField field(errors, ".threshold");
    errors->AddError("value must be <= 100");
  }
}

const JsonLoaderInterface* OutlierDetectionConfig::JsonLoader(const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<OutlierDetectionConfig>()
          .OptionalField("interval", &OutlierDetectionConfig::interval)
          .OptionalField("baseEjectionTime",
                         &OutlierDetectionConfig::base_ejection_time)
          .OptionalField("maxEjectionTime",
                         &OutlierDetectionConfig::max_ejection_time)
          .OptionalField("maxEjectionPercent",
                         &OutlierDetectionConfig::max_ejection_percent)
          .OptionalField("successRateEjection",
                         &OutlierDetectionConfig::success_rate_ejection)
          .OptionalField("failurePercentageEjection",
                         &OutlierDetectionConfig::failure_percentage_ejection)
          .Finish();
  return loader;
}

void OutlierDetectionConfig::JsonPostLoad(const Json& json, const JsonArgs&,
                                          ValidationErrors* errors) {
  if (json.object().find("maxEjectionTime") == json.object().end()) {
    max_ejection_time = std::max(base_ejection_time, Duration::Seconds(300));
  }
  if (max_ejection_percent > 100) {
    ValidationErrors::ScopedField field(errors, ".max_ejection_percent");
    errors->AddError("value must be <= 100");
  }
}

void RegisterOutlierDetectionLbPolicy(CoreConfiguration::Builder* builder) {
  builder->lb_policy_registry()->RegisterLoadBalancingPolicyFactory(
      std::make_unique<OutlierDetectionLbFactory>());
}

}
