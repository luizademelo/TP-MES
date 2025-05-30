
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_LB_POLICY_FACTORY_H
#define GRPC_SRC_CORE_LOAD_BALANCING_LB_POLICY_FACTORY_H

#include <grpc/support/port_platform.h>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/util/json/json.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class LoadBalancingPolicyFactory {
 public:
  virtual ~LoadBalancingPolicyFactory() {}

  virtual OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args) const = 0;

  virtual absl::string_view name() const = 0;

  virtual absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& json) const = 0;
};

}

#endif
