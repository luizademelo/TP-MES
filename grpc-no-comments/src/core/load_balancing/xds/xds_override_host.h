
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_XDS_XDS_OVERRIDE_HOST_H
#define GRPC_SRC_CORE_LOAD_BALANCING_XDS_XDS_OVERRIDE_HOST_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

class XdsOverrideHostLbConfig final : public LoadBalancingPolicy::Config {
 public:
  XdsOverrideHostLbConfig() = default;

  XdsOverrideHostLbConfig(const XdsOverrideHostLbConfig&) = delete;
  XdsOverrideHostLbConfig& operator=(const XdsOverrideHostLbConfig&) = delete;

  XdsOverrideHostLbConfig(XdsOverrideHostLbConfig&& other) = delete;
  XdsOverrideHostLbConfig& operator=(XdsOverrideHostLbConfig&& other) = delete;

  static absl::string_view Name() { return "xds_override_host_experimental"; }

  absl::string_view name() const override { return Name(); }

  const std::string& cluster_name() const { return cluster_name_; }
  RefCountedPtr<LoadBalancingPolicy::Config> child_config() const {
    return child_config_;
  }

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
  void JsonPostLoad(const Json& json, const JsonArgs&,
                    ValidationErrors* errors);

 private:
  std::string cluster_name_;
  RefCountedPtr<LoadBalancingPolicy::Config> child_config_;
};

}
#endif
