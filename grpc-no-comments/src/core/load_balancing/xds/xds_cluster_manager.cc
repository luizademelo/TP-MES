
// Copyright 2018 gRPC authors.

#include <grpc/event_engine/event_engine.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "src/core/client_channel/client_channel_internal.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/load_balancing/child_policy_handler.h"
#include "src/core/load_balancing/delegating_helper.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_factory.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/xds/xds_resolver_attributes.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "src/core/util/validation_errors.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

namespace {

using ::grpc_event_engine::experimental::EventEngine;

constexpr Duration kChildRetentionInterval = Duration::Minutes(15);
constexpr absl::string_view kXdsClusterManager =
    "xds_cluster_manager_experimental";

class XdsClusterManagerLbConfig final : public LoadBalancingPolicy::Config {
 public:
  struct Child {
    RefCountedPtr<LoadBalancingPolicy::Config> config;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
    void JsonPostLoad(const Json& json, const JsonArgs&,
                      ValidationErrors* errors);
  };

  XdsClusterManagerLbConfig() = default;

  XdsClusterManagerLbConfig(const XdsClusterManagerLbConfig&) = delete;
  XdsClusterManagerLbConfig& operator=(const XdsClusterManagerLbConfig&) =
      delete;

  XdsClusterManagerLbConfig(XdsClusterManagerLbConfig&& other) = delete;
  XdsClusterManagerLbConfig& operator=(XdsClusterManagerLbConfig&& other) =
      delete;

  absl::string_view name() const override { return kXdsClusterManager; }

  const std::map<std::string, Child>& cluster_map() const {
    return cluster_map_;
  }

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);

 private:
  std::map<std::string, Child> cluster_map_;
};

class XdsClusterManagerLb final : public LoadBalancingPolicy {
 public:
  explicit XdsClusterManagerLb(Args args);

  absl::string_view name() const override { return kXdsClusterManager; }

  absl::Status UpdateLocked(UpdateArgs args) override;
  void ExitIdleLocked() override;
  void ResetBackoffLocked() override;

 private:

  class ClusterPicker final : public SubchannelPicker {
   public:

    using ClusterMap = std::map<std::string ,
                                RefCountedPtr<SubchannelPicker>, std::less<>>;

    explicit ClusterPicker(ClusterMap cluster_map)
        : cluster_map_(std::move(cluster_map)) {}

    PickResult Pick(PickArgs args) override;

   private:
    ClusterMap cluster_map_;
  };

  class ClusterChild final : public InternallyRefCounted<ClusterChild> {
   public:
    ClusterChild(RefCountedPtr<XdsClusterManagerLb> xds_cluster_manager_policy,
                 const std::string& name);
    ~ClusterChild() override;

    void Orphan() override;

    absl::Status UpdateLocked(
        RefCountedPtr<LoadBalancingPolicy::Config> config,
        const absl::StatusOr<std::shared_ptr<EndpointAddressesIterator>>&
            addresses,
        const ChannelArgs& args);
    void ExitIdleLocked();
    void ResetBackoffLocked();
    void DeactivateLocked();

    grpc_connectivity_state connectivity_state() const {
      return connectivity_state_;
    }
    RefCountedPtr<SubchannelPicker> picker() const { return picker_; }

   private:
    class Helper final : public DelegatingChannelControlHelper {
     public:
      explicit Helper(RefCountedPtr<ClusterChild> xds_cluster_manager_child)
          : xds_cluster_manager_child_(std::move(xds_cluster_manager_child)) {}

      ~Helper() override {
        xds_cluster_manager_child_.reset(DEBUG_LOCATION, "Helper");
      }

      void UpdateState(grpc_connectivity_state state,
                       const absl::Status& status,
                       RefCountedPtr<SubchannelPicker> picker) override;

     private:
      ChannelControlHelper* parent_helper() const override {
        return xds_cluster_manager_child_->xds_cluster_manager_policy_
            ->channel_control_helper();
      }

      RefCountedPtr<ClusterChild> xds_cluster_manager_child_;
    };

    OrphanablePtr<LoadBalancingPolicy> CreateChildPolicyLocked(
        const ChannelArgs& args);

    void OnDelayedRemovalTimerLocked();

    RefCountedPtr<XdsClusterManagerLb> xds_cluster_manager_policy_;

    const std::string name_;

    OrphanablePtr<LoadBalancingPolicy> child_policy_;

    RefCountedPtr<SubchannelPicker> picker_;
    grpc_connectivity_state connectivity_state_ = GRPC_CHANNEL_CONNECTING;

    std::optional<EventEngine::TaskHandle> delayed_removal_timer_handle_;
    bool shutdown_ = false;
  };

  ~XdsClusterManagerLb() override;

  void ShutdownLocked() override;

  void UpdateStateLocked();

  RefCountedPtr<XdsClusterManagerLbConfig> config_;

  bool shutting_down_ = false;
  bool update_in_progress_ = false;

  std::map<std::string, OrphanablePtr<ClusterChild>> children_;
};

XdsClusterManagerLb::PickResult XdsClusterManagerLb::ClusterPicker::Pick(
    PickArgs args) {
  auto* call_state = static_cast<ClientChannelLbCallState*>(args.call_state);
  auto* cluster_name_attribute =
      call_state->GetCallAttribute<XdsClusterAttribute>();
  absl::string_view cluster_name;
  if (cluster_name_attribute != nullptr) {
    cluster_name = cluster_name_attribute->cluster();
  }
  auto it = cluster_map_.find(cluster_name);
  if (it != cluster_map_.end()) {
    return it->second->Pick(args);
  }
  return PickResult::Fail(absl::InternalError(absl::StrCat(
      "xds cluster manager picker: unknown cluster \"", cluster_name, "\"")));
}

XdsClusterManagerLb::XdsClusterManagerLb(Args args)
    : LoadBalancingPolicy(std::move(args)) {}

XdsClusterManagerLb::~XdsClusterManagerLb() {
  GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
      << "[xds_cluster_manager_lb " << this
      << "] destroying xds_cluster_manager LB policy";
}

void XdsClusterManagerLb::ShutdownLocked() {
  GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
      << "[xds_cluster_manager_lb " << this << "] shutting down";
  shutting_down_ = true;
  children_.clear();
}

void XdsClusterManagerLb::ExitIdleLocked() {
  for (auto& [_, child] : children_) child->ExitIdleLocked();
}

void XdsClusterManagerLb::ResetBackoffLocked() {
  for (auto& [_, child] : children_) child->ResetBackoffLocked();
}

absl::Status XdsClusterManagerLb::UpdateLocked(UpdateArgs args) {
  if (shutting_down_) return absl::OkStatus();
  GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
      << "[xds_cluster_manager_lb " << this << "] Received update";
  update_in_progress_ = true;

  config_ = args.config.TakeAsSubclass<XdsClusterManagerLbConfig>();

  for (const auto& [name, child] : children_) {
    if (config_->cluster_map().find(name) == config_->cluster_map().end()) {
      child->DeactivateLocked();
    }
  }

  std::vector<std::string> errors;
  for (const auto& [name, cluster] : config_->cluster_map()) {
    const RefCountedPtr<LoadBalancingPolicy::Config>& config = cluster.config;
    auto& child = children_[name];
    if (child == nullptr) {
      child = MakeOrphanable<ClusterChild>(
          RefAsSubclass<XdsClusterManagerLb>(DEBUG_LOCATION, "ClusterChild"),
          name);
    }
    absl::Status status =
        child->UpdateLocked(config, args.addresses, args.args);
    if (!status.ok()) {
      errors.emplace_back(
          absl::StrCat("child ", name, ": ", status.ToString()));
    }
  }
  update_in_progress_ = false;
  UpdateStateLocked();

  if (!errors.empty()) {
    return absl::UnavailableError(absl::StrCat(
        "errors from children: [", absl::StrJoin(errors, "; "), "]"));
  }
  return absl::OkStatus();
}

void XdsClusterManagerLb::UpdateStateLocked() {

  if (update_in_progress_) return;

  size_t num_ready = 0;
  size_t num_connecting = 0;
  size_t num_idle = 0;
  for (const auto& [child_name, child] : children_) {

    if (config_->cluster_map().find(child_name) ==
        config_->cluster_map().end()) {
      continue;
    }
    switch (child->connectivity_state()) {
      case GRPC_CHANNEL_READY: {
        ++num_ready;
        break;
      }
      case GRPC_CHANNEL_CONNECTING: {
        ++num_connecting;
        break;
      }
      case GRPC_CHANNEL_IDLE: {
        ++num_idle;
        break;
      }
      case GRPC_CHANNEL_TRANSIENT_FAILURE: {
        break;
      }
      default:
        GPR_UNREACHABLE_CODE(return);
    }
  }

  grpc_connectivity_state connectivity_state;
  if (num_ready > 0) {
    connectivity_state = GRPC_CHANNEL_READY;
  } else if (num_connecting > 0) {
    connectivity_state = GRPC_CHANNEL_CONNECTING;
  } else if (num_idle > 0) {
    connectivity_state = GRPC_CHANNEL_IDLE;
  } else {
    connectivity_state = GRPC_CHANNEL_TRANSIENT_FAILURE;
  }
  GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
      << "[xds_cluster_manager_lb " << this << "] connectivity changed to "
      << ConnectivityStateName(connectivity_state);
  ClusterPicker::ClusterMap cluster_map;
  for (const auto& [cluster_name, _] : config_->cluster_map()) {
    RefCountedPtr<SubchannelPicker>& child_picker = cluster_map[cluster_name];
    child_picker = children_[cluster_name]->picker();
    if (child_picker == nullptr) {
      GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
          << "[xds_cluster_manager_lb " << this << "] child " << cluster_name
          << " has not yet returned a picker; creating a QueuePicker.";
      child_picker =
          MakeRefCounted<QueuePicker>(Ref(DEBUG_LOCATION, "QueuePicker"));
    }
  }
  auto picker = MakeRefCounted<ClusterPicker>(std::move(cluster_map));
  absl::Status status;
  if (connectivity_state == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    status = absl::Status(absl::StatusCode::kUnavailable,
                          "TRANSIENT_FAILURE from XdsClusterManagerLb");
  }
  channel_control_helper()->UpdateState(connectivity_state, status,
                                        std::move(picker));
}

XdsClusterManagerLb::ClusterChild::ClusterChild(
    RefCountedPtr<XdsClusterManagerLb> xds_cluster_manager_policy,
    const std::string& name)
    : xds_cluster_manager_policy_(std::move(xds_cluster_manager_policy)),
      name_(name),
      picker_(MakeRefCounted<QueuePicker>(nullptr)) {
  GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
      << "[xds_cluster_manager_lb " << xds_cluster_manager_policy_.get()
      << "] created ClusterChild " << this << " for " << name_;
}

XdsClusterManagerLb::ClusterChild::~ClusterChild() {
  GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
      << "[xds_cluster_manager_lb " << xds_cluster_manager_policy_.get()
      << "] ClusterChild " << this << ": destroying child";
  xds_cluster_manager_policy_.reset(DEBUG_LOCATION, "ClusterChild");
}

void XdsClusterManagerLb::ClusterChild::Orphan() {
  GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
      << "[xds_cluster_manager_lb " << xds_cluster_manager_policy_.get()
      << "] ClusterChild " << this << " " << name_ << ": shutting down child";

  grpc_pollset_set_del_pollset_set(
      child_policy_->interested_parties(),
      xds_cluster_manager_policy_->interested_parties());
  child_policy_.reset();

  picker_.reset();
  if (delayed_removal_timer_handle_.has_value()) {
    xds_cluster_manager_policy_->channel_control_helper()
        ->GetEventEngine()
        ->Cancel(*delayed_removal_timer_handle_);
  }
  shutdown_ = true;
  Unref();
}

OrphanablePtr<LoadBalancingPolicy>
XdsClusterManagerLb::ClusterChild::CreateChildPolicyLocked(
    const ChannelArgs& args) {
  LoadBalancingPolicy::Args lb_policy_args;
  lb_policy_args.work_serializer =
      xds_cluster_manager_policy_->work_serializer();
  lb_policy_args.args = args;
  lb_policy_args.channel_control_helper =
      std::make_unique<Helper>(this->Ref(DEBUG_LOCATION, "Helper"));
  OrphanablePtr<LoadBalancingPolicy> lb_policy =
      MakeOrphanable<ChildPolicyHandler>(std::move(lb_policy_args),
                                         &xds_cluster_manager_lb_trace);
  GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
      << "[xds_cluster_manager_lb " << xds_cluster_manager_policy_.get()
      << "] ClusterChild " << this << " " << name_
      << ": Created new child policy handler " << lb_policy.get();

  grpc_pollset_set_add_pollset_set(
      lb_policy->interested_parties(),
      xds_cluster_manager_policy_->interested_parties());
  return lb_policy;
}

absl::Status XdsClusterManagerLb::ClusterChild::UpdateLocked(
    RefCountedPtr<LoadBalancingPolicy::Config> config,
    const absl::StatusOr<std::shared_ptr<EndpointAddressesIterator>>& addresses,
    const ChannelArgs& args) {
  if (xds_cluster_manager_policy_->shutting_down_) return absl::OkStatus();

  if (delayed_removal_timer_handle_.has_value() &&
      xds_cluster_manager_policy_->channel_control_helper()
          ->GetEventEngine()
          ->Cancel(*delayed_removal_timer_handle_)) {
    delayed_removal_timer_handle_.reset();
  }

  if (child_policy_ == nullptr) {
    child_policy_ = CreateChildPolicyLocked(args);
  }

  UpdateArgs update_args;
  update_args.config = std::move(config);
  update_args.addresses = addresses;
  update_args.args = args;

  GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
      << "[xds_cluster_manager_lb " << xds_cluster_manager_policy_.get()
      << "] ClusterChild " << this << " " << name_
      << ": Updating child policy handler " << child_policy_.get();
  return child_policy_->UpdateLocked(std::move(update_args));
}

void XdsClusterManagerLb::ClusterChild::ExitIdleLocked() {
  child_policy_->ExitIdleLocked();
}

void XdsClusterManagerLb::ClusterChild::ResetBackoffLocked() {
  child_policy_->ResetBackoffLocked();
}

void XdsClusterManagerLb::ClusterChild::DeactivateLocked() {

  if (delayed_removal_timer_handle_.has_value()) return;

  delayed_removal_timer_handle_ =
      xds_cluster_manager_policy_->channel_control_helper()
          ->GetEventEngine()
          ->RunAfter(
              kChildRetentionInterval,
              [self = Ref(DEBUG_LOCATION, "ClusterChild+timer")]() mutable {
                ExecCtx exec_ctx;
                auto* self_ptr = self.get();
                self_ptr->xds_cluster_manager_policy_->work_serializer()->Run(
                    [self = std::move(self)]() {
                      self->OnDelayedRemovalTimerLocked();
                    });
              });
}

void XdsClusterManagerLb::ClusterChild::OnDelayedRemovalTimerLocked() {
  delayed_removal_timer_handle_.reset();
  if (!shutdown_) {
    xds_cluster_manager_policy_->children_.erase(name_);
  }
}

void XdsClusterManagerLb::ClusterChild::Helper::UpdateState(
    grpc_connectivity_state state, const absl::Status& status,
    RefCountedPtr<SubchannelPicker> picker) {
  GRPC_TRACE_LOG(xds_cluster_manager_lb, INFO)
      << "[xds_cluster_manager_lb "
      << xds_cluster_manager_child_->xds_cluster_manager_policy_.get()
      << "] child " << xds_cluster_manager_child_->name_
      << ": received update: state=" << ConnectivityStateName(state) << " ("
      << status << ") picker=" << picker.get();
  if (xds_cluster_manager_child_->xds_cluster_manager_policy_->shutting_down_) {
    return;
  }

  xds_cluster_manager_child_->picker_ = std::move(picker);

  if (xds_cluster_manager_child_->connectivity_state_ !=
          GRPC_CHANNEL_TRANSIENT_FAILURE ||
      state == GRPC_CHANNEL_READY) {
    xds_cluster_manager_child_->connectivity_state_ = state;
  }

  xds_cluster_manager_child_->xds_cluster_manager_policy_->UpdateStateLocked();
}

const JsonLoaderInterface* XdsClusterManagerLbConfig::Child::JsonLoader(
    const JsonArgs&) {
  // Note: The "childPolicy" field requires custom processing, so

  static const auto* loader = JsonObjectLoader<Child>().Finish();
  return loader;
}

void XdsClusterManagerLbConfig::Child::JsonPostLoad(const Json& json,
                                                    const JsonArgs&,
                                                    ValidationErrors* errors) {
  ValidationErrors::ScopedField field(errors, ".childPolicy");
  auto it = json.object().find("childPolicy");
  if (it == json.object().end()) {
    errors->AddError("field not present");
    return;
  }
  auto lb_config =
      CoreConfiguration::Get().lb_policy_registry().ParseLoadBalancingConfig(
          it->second);
  if (!lb_config.ok()) {
    errors->AddError(lb_config.status().message());
    return;
  }
  config = std::move(*lb_config);
}

const JsonLoaderInterface* XdsClusterManagerLbConfig::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<XdsClusterManagerLbConfig>()
          .Field("children", &XdsClusterManagerLbConfig::cluster_map_)
          .Finish();
  return loader;
}

class XdsClusterManagerLbFactory final : public LoadBalancingPolicyFactory {
 public:
  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args args) const override {
    return MakeOrphanable<XdsClusterManagerLb>(std::move(args));
  }

  absl::string_view name() const override { return kXdsClusterManager; }

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& json) const override {
    return LoadFromJson<RefCountedPtr<XdsClusterManagerLbConfig>>(
        json, JsonArgs(),
        "errors validating xds_cluster_manager LB policy config");
  }
};

}

void RegisterXdsClusterManagerLbPolicy(CoreConfiguration::Builder* builder) {
  builder->lb_policy_registry()->RegisterLoadBalancingPolicyFactory(
      std::make_unique<XdsClusterManagerLbFactory>());
}

}
