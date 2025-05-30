
// Copyright 2018 gRPC authors.

#include "src/core/load_balancing/child_policy_handler.h"

#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/load_balancing/delegating_helper.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/util/debug_location.h"

namespace grpc_core {

class ChildPolicyHandler::Helper final
    : public LoadBalancingPolicy::ParentOwningDelegatingChannelControlHelper<
          ChildPolicyHandler> {
 public:
  explicit Helper(RefCountedPtr<ChildPolicyHandler> parent)
      : ParentOwningDelegatingChannelControlHelper(std::move(parent)) {}

  RefCountedPtr<SubchannelInterface> CreateSubchannel(
      const grpc_resolved_address& address, const ChannelArgs& per_address_args,
      const ChannelArgs& args) override {
    if (parent()->shutting_down_) return nullptr;
    if (!CalledByCurrentChild() && !CalledByPendingChild()) return nullptr;
    return parent()->channel_control_helper()->CreateSubchannel(
        address, per_address_args, args);
  }

  void UpdateState(grpc_connectivity_state state, const absl::Status& status,
                   RefCountedPtr<SubchannelPicker> picker) override {
    if (parent()->shutting_down_) return;

    if (CalledByPendingChild()) {
      if (GRPC_TRACE_FLAG_ENABLED_OBJ(*(parent()->tracer_))) {
        LOG(INFO) << "[child_policy_handler " << parent() << "] helper " << this
                  << ": pending child policy " << child_
                  << " reports state=" << ConnectivityStateName(state) << " ("
                  << status << ")";
      }
      if (state == GRPC_CHANNEL_CONNECTING) return;
      grpc_pollset_set_del_pollset_set(
          parent()->child_policy_->interested_parties(),
          parent()->interested_parties());
      parent()->child_policy_ = std::move(parent()->pending_child_policy_);
    } else if (!CalledByCurrentChild()) {

      return;
    }
    parent()->channel_control_helper()->UpdateState(state, status,
                                                    std::move(picker));
  }

  void RequestReresolution() override {
    if (parent()->shutting_down_) return;

    const LoadBalancingPolicy* latest_child_policy =
        parent()->pending_child_policy_ != nullptr
            ? parent()->pending_child_policy_.get()
            : parent()->child_policy_.get();
    if (child_ != latest_child_policy) return;
    if (GRPC_TRACE_FLAG_ENABLED_OBJ(*(parent()->tracer_))) {
      LOG(INFO) << "[child_policy_handler " << parent()
                << "] requesting re-resolution";
    }
    parent()->channel_control_helper()->RequestReresolution();
  }

  void AddTraceEvent(TraceSeverity severity,
                     absl::string_view message) override {
    if (parent()->shutting_down_) return;
    if (!CalledByPendingChild() && !CalledByCurrentChild()) return;
    parent()->channel_control_helper()->AddTraceEvent(severity, message);
  }

  void set_child(LoadBalancingPolicy* child) { child_ = child; }

 private:
  bool CalledByPendingChild() const {
    CHECK_NE(child_, nullptr);
    return child_ == parent()->pending_child_policy_.get();
  }

  bool CalledByCurrentChild() const {
    CHECK_NE(child_, nullptr);
    return child_ == parent()->child_policy_.get();
  };

  LoadBalancingPolicy* child_ = nullptr;
};

void ChildPolicyHandler::ShutdownLocked() {
  if (GRPC_TRACE_FLAG_ENABLED_OBJ(*tracer_)) {
    LOG(INFO) << "[child_policy_handler " << this << "] shutting down";
  }
  shutting_down_ = true;
  if (child_policy_ != nullptr) {
    if (GRPC_TRACE_FLAG_ENABLED_OBJ(*tracer_)) {
      LOG(INFO) << "[child_policy_handler " << this
                << "] shutting down lb_policy " << child_policy_.get();
    }
    grpc_pollset_set_del_pollset_set(child_policy_->interested_parties(),
                                     interested_parties());
    child_policy_.reset();
  }
  if (pending_child_policy_ != nullptr) {
    if (GRPC_TRACE_FLAG_ENABLED_OBJ(*tracer_)) {
      LOG(INFO) << "[child_policy_handler " << this
                << "] shutting down pending lb_policy "
                << pending_child_policy_.get();
    }
    grpc_pollset_set_del_pollset_set(
        pending_child_policy_->interested_parties(), interested_parties());
    pending_child_policy_.reset();
  }
}

absl::Status ChildPolicyHandler::UpdateLocked(UpdateArgs args) {

  const bool create_policy =

      child_policy_ == nullptr ||

      ConfigChangeRequiresNewPolicyInstance(current_config_.get(),
                                            args.config.get());
  current_config_ = args.config;
  LoadBalancingPolicy* policy_to_update = nullptr;
  if (create_policy) {

    if (GRPC_TRACE_FLAG_ENABLED_OBJ(*tracer_)) {
      LOG(INFO) << "[child_policy_handler " << this << "] creating new "
                << (child_policy_ == nullptr ? "" : "pending ")
                << "child policy " << args.config->name();
    }
    auto& lb_policy =
        child_policy_ == nullptr ? child_policy_ : pending_child_policy_;
    lb_policy = CreateChildPolicy(args.config->name(), args.args);
    policy_to_update = lb_policy.get();
  } else {

    policy_to_update = pending_child_policy_ != nullptr
                           ? pending_child_policy_.get()
                           : child_policy_.get();
  }
  CHECK_NE(policy_to_update, nullptr);

  if (GRPC_TRACE_FLAG_ENABLED_OBJ(*tracer_)) {
    LOG(INFO) << "[child_policy_handler " << this << "] updating "
              << (policy_to_update == pending_child_policy_.get() ? "pending "
                                                                  : "")
              << "child policy " << policy_to_update;
  }
  return policy_to_update->UpdateLocked(std::move(args));
}

void ChildPolicyHandler::ExitIdleLocked() {
  if (child_policy_ != nullptr) {
    child_policy_->ExitIdleLocked();
    if (pending_child_policy_ != nullptr) {
      pending_child_policy_->ExitIdleLocked();
    }
  }
}

void ChildPolicyHandler::ResetBackoffLocked() {
  if (child_policy_ != nullptr) {
    child_policy_->ResetBackoffLocked();
    if (pending_child_policy_ != nullptr) {
      pending_child_policy_->ResetBackoffLocked();
    }
  }
}

OrphanablePtr<LoadBalancingPolicy> ChildPolicyHandler::CreateChildPolicy(
    absl::string_view child_policy_name, const ChannelArgs& args) {
  Helper* helper =
      new Helper(RefAsSubclass<ChildPolicyHandler>(DEBUG_LOCATION, "Helper"));
  LoadBalancingPolicy::Args lb_policy_args;
  lb_policy_args.work_serializer = work_serializer();
  lb_policy_args.channel_control_helper =
      std::unique_ptr<ChannelControlHelper>(helper);
  lb_policy_args.args = args;
  OrphanablePtr<LoadBalancingPolicy> lb_policy =
      CreateLoadBalancingPolicy(child_policy_name, std::move(lb_policy_args));
  if (GPR_UNLIKELY(lb_policy == nullptr)) {
    LOG(ERROR) << "could not create LB policy \"" << child_policy_name << "\"";
    return nullptr;
  }
  helper->set_child(lb_policy.get());
  if (GRPC_TRACE_FLAG_ENABLED_OBJ(*tracer_)) {
    LOG(INFO) << "[child_policy_handler " << this
              << "] created new LB policy \"" << child_policy_name << "\" ("
              << lb_policy.get() << ")";
  }
  channel_control_helper()->AddTraceEvent(
      ChannelControlHelper::TRACE_INFO,
      absl::StrCat("Created new LB policy \"", child_policy_name, "\""));
  grpc_pollset_set_add_pollset_set(lb_policy->interested_parties(),
                                   interested_parties());
  return lb_policy;
}

bool ChildPolicyHandler::ConfigChangeRequiresNewPolicyInstance(
    LoadBalancingPolicy::Config* old_config,
    LoadBalancingPolicy::Config* new_config) const {
  return old_config->name() != new_config->name();
}

OrphanablePtr<LoadBalancingPolicy>
ChildPolicyHandler::CreateLoadBalancingPolicy(
    absl::string_view name, LoadBalancingPolicy::Args args) const {
  return CoreConfiguration::Get()
      .lb_policy_registry()
      .CreateLoadBalancingPolicy(name, std::move(args));
}

}
