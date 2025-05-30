
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_LB_POLICY_REGISTRY_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_LB_POLICY_REGISTRY_H

#include <grpc/support/port_platform.h>

#include <map>
#include <memory>

#include "absl/strings/string_view.h"
#include "envoy/config/cluster/v3/cluster.upb.h"
#include "src/core/util/json/json.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/xds_client/xds_resource_type.h"

namespace grpc_core {

class XdsLbPolicyRegistry final {
 public:
  class ConfigFactory {
   public:
    virtual ~ConfigFactory() = default;
    virtual Json::Object ConvertXdsLbPolicyConfig(
        const XdsLbPolicyRegistry* registry,
        const XdsResourceType::DecodeContext& context,
        absl::string_view configuration, ValidationErrors* errors,
        int recursion_depth) = 0;
    virtual absl::string_view type() = 0;
  };

  XdsLbPolicyRegistry();

  Json::Array ConvertXdsLbPolicyConfig(
      const XdsResourceType::DecodeContext& context,
      const envoy_config_cluster_v3_LoadBalancingPolicy* lb_policy,
      ValidationErrors* errors, int recursion_depth = 0) const;

 private:

  std::map<absl::string_view ,
           std::unique_ptr<ConfigFactory>>
      policy_config_factories_;
};

}

#endif
