
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_CHILD_POLICY_HANDLER_H
#define GRPC_SRC_CORE_LOAD_BALANCING_CHILD_POLICY_HANDLER_H
#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class ChildPolicyHandler : public LoadBalancingPolicy {
 public:
  ChildPolicyHandler(Args args, TraceFlag* tracer)
      : LoadBalancingPolicy(std::move(args)), tracer_(tracer) {}

  absl::string_view name() const override { return "child_policy_handler"; }

  absl::Status UpdateLocked(UpdateArgs args) override;
  void ExitIdleLocked() override;
  void ResetBackoffLocked() override;

  virtual bool ConfigChangeRequiresNewPolicyInstance(
      LoadBalancingPolicy::Config* old_config,
      LoadBalancingPolicy::Config* new_config) const;

  virtual OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      absl::string_view name, LoadBalancingPolicy::Args args) const;

 private:
  class Helper;

  void ShutdownLocked() override;

  OrphanablePtr<LoadBalancingPolicy> CreateChildPolicy(
      absl::string_view child_policy_name, const ChannelArgs& args);

  TraceFlag* tracer_;

  bool shutting_down_ = false;

  RefCountedPtr<LoadBalancingPolicy::Config> current_config_;

  OrphanablePtr<LoadBalancingPolicy> child_policy_;
  OrphanablePtr<LoadBalancingPolicy> pending_child_policy_;
};

}

#endif
