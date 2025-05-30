
// Copyright 2015 gRPC authors.

#include "src/core/load_balancing/lb_policy_registry.h"

#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "src/core/load_balancing/lb_policy.h"

namespace grpc_core {

void LoadBalancingPolicyRegistry::Builder::RegisterLoadBalancingPolicyFactory(
    std::unique_ptr<LoadBalancingPolicyFactory> factory) {
  VLOG(2) << "registering LB policy factory for \"" << factory->name() << "\"";
  CHECK(factories_.find(factory->name()) == factories_.end());
  factories_.emplace(factory->name(), std::move(factory));
}

LoadBalancingPolicyRegistry LoadBalancingPolicyRegistry::Builder::Build() {
  LoadBalancingPolicyRegistry out;
  out.factories_ = std::move(factories_);
  return out;
}

LoadBalancingPolicyFactory*
LoadBalancingPolicyRegistry::GetLoadBalancingPolicyFactory(
    absl::string_view name) const {
  auto it = factories_.find(name);
  if (it == factories_.end()) return nullptr;
  return it->second.get();
}

OrphanablePtr<LoadBalancingPolicy>
LoadBalancingPolicyRegistry::CreateLoadBalancingPolicy(
    absl::string_view name, LoadBalancingPolicy::Args args) const {

  LoadBalancingPolicyFactory* factory = GetLoadBalancingPolicyFactory(name);
  if (factory == nullptr) return nullptr;

  return factory->CreateLoadBalancingPolicy(std::move(args));
}

bool LoadBalancingPolicyRegistry::LoadBalancingPolicyExists(
    absl::string_view name, bool* requires_config) const {
  auto* factory = GetLoadBalancingPolicyFactory(name);
  if (factory == nullptr) return false;

  if (requires_config != nullptr) {
    auto config = factory->ParseLoadBalancingConfig(Json::FromObject({}));
    *requires_config = !config.ok();
  }
  return true;
}

absl::StatusOr<Json::Object::const_iterator>
LoadBalancingPolicyRegistry::ParseLoadBalancingConfigHelper(
    const Json& lb_config_array) const {
  if (lb_config_array.type() != Json::Type::kArray) {
    return absl::InvalidArgumentError("type should be array");
  }

  std::vector<absl::string_view> policies_tried;
  for (const Json& lb_config : lb_config_array.array()) {
    if (lb_config.type() != Json::Type::kObject) {
      return absl::InvalidArgumentError("child entry should be of type object");
    }
    if (lb_config.object().empty()) {
      return absl::InvalidArgumentError("no policy found in child entry");
    }
    if (lb_config.object().size() > 1) {
      return absl::InvalidArgumentError("oneOf violation");
    }
    auto it = lb_config.object().begin();
    auto& [policy_name, config] = *it;
    if (config.type() != Json::Type::kObject) {
      return absl::InvalidArgumentError("child entry should be of type object");
    }

    if (LoadBalancingPolicyRegistry::LoadBalancingPolicyExists(policy_name,
                                                               nullptr)) {
      return it;
    }
    policies_tried.push_back(policy_name);
  }
  return absl::FailedPreconditionError(absl::StrCat(
      "No known policies in list: ", absl::StrJoin(policies_tried, " ")));
}

absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
LoadBalancingPolicyRegistry::ParseLoadBalancingConfig(const Json& json) const {
  auto policy = ParseLoadBalancingConfigHelper(json);
  if (!policy.ok()) return policy.status();
  auto& [policy_name, config] = **policy;

  LoadBalancingPolicyFactory* factory =
      GetLoadBalancingPolicyFactory(policy_name);
  if (factory == nullptr) {
    return absl::FailedPreconditionError(
        absl::StrFormat("Factory not found for policy \"%s\"", policy_name));
  }

  return factory->ParseLoadBalancingConfig(config);
}

}
