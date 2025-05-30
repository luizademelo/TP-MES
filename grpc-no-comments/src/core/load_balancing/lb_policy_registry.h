
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_LB_POLICY_REGISTRY_H
#define GRPC_SRC_CORE_LOAD_BALANCING_LB_POLICY_REGISTRY_H

#include <grpc/support/port_platform.h>

#include <map>
#include <memory>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_factory.h"
#include "src/core/util/json/json.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class LoadBalancingPolicyRegistry final {
 public:

  class Builder final {
   public:

    void RegisterLoadBalancingPolicyFactory(
        std::unique_ptr<LoadBalancingPolicyFactory> factory);

    LoadBalancingPolicyRegistry Build();

   private:
    std::map<absl::string_view, std::unique_ptr<LoadBalancingPolicyFactory>>
        factories_;
  };

  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      absl::string_view name, LoadBalancingPolicy::Args args) const;

  bool LoadBalancingPolicyExists(absl::string_view name,
                                 bool* requires_config) const;

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& json) const;

 private:
  LoadBalancingPolicyFactory* GetLoadBalancingPolicyFactory(
      absl::string_view name) const;
  absl::StatusOr<Json::Object::const_iterator> ParseLoadBalancingConfigHelper(
      const Json& lb_config_array) const;

  std::map<absl::string_view, std::unique_ptr<LoadBalancingPolicyFactory>>
      factories_;
};

}

#endif
