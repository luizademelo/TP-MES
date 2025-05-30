
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_DELEGATING_HELPER_H
#define GRPC_SRC_CORE_LOAD_BALANCING_DELEGATING_HELPER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class LoadBalancingPolicy::DelegatingChannelControlHelper
    : public LoadBalancingPolicy::ChannelControlHelper {
 public:
  RefCountedPtr<SubchannelInterface> CreateSubchannel(
      const grpc_resolved_address& address, const ChannelArgs& per_address_args,
      const ChannelArgs& args) override {
    return parent_helper()->CreateSubchannel(address, per_address_args, args);
  }

  void UpdateState(grpc_connectivity_state state, const absl::Status& status,
                   RefCountedPtr<SubchannelPicker> picker) override {
    parent_helper()->UpdateState(state, status, std::move(picker));
  }

  void RequestReresolution() override {
    parent_helper()->RequestReresolution();
  }

  absl::string_view GetTarget() override {
    return parent_helper()->GetTarget();
  }

  absl::string_view GetAuthority() override {
    return parent_helper()->GetAuthority();
  }

  RefCountedPtr<grpc_channel_credentials> GetChannelCredentials() override {
    return parent_helper()->GetChannelCredentials();
  }

  RefCountedPtr<grpc_channel_credentials> GetUnsafeChannelCredentials()
      override {
    return parent_helper()->GetUnsafeChannelCredentials();
  }

  grpc_event_engine::experimental::EventEngine* GetEventEngine() override {
    return parent_helper()->GetEventEngine();
  }

  GlobalStatsPluginRegistry::StatsPluginGroup& GetStatsPluginGroup() override {
    return parent_helper()->GetStatsPluginGroup();
  }

  void AddTraceEvent(TraceSeverity severity,
                     absl::string_view message) override {
    parent_helper()->AddTraceEvent(severity, message);
  }

 private:

  virtual ChannelControlHelper* parent_helper() const = 0;
};

template <typename ParentPolicy>
class LoadBalancingPolicy::ParentOwningDelegatingChannelControlHelper
    : public LoadBalancingPolicy::DelegatingChannelControlHelper {
 public:
  explicit ParentOwningDelegatingChannelControlHelper(
      RefCountedPtr<ParentPolicy> parent)
      : parent_(std::move(parent)) {}

  ~ParentOwningDelegatingChannelControlHelper() override {
    parent_.reset(DEBUG_LOCATION, "Helper");
  }

 protected:
  ParentPolicy* parent() const {
    return static_cast<ParentPolicy*>(parent_.get());
  }

  ChannelControlHelper* parent_helper() const override {
    return parent_->channel_control_helper();
  }

 private:
  RefCountedPtr<LoadBalancingPolicy> parent_;
};

}

#endif
