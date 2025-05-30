
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_RLS_RLS_H
#define GRPC_SRC_CORE_LOAD_BALANCING_RLS_RLS_H

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "src/core/load_balancing/lb_policy.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/time.h"
#include "src/core/util/validation_errors.h"

#define GRPC_ARG_TEST_ONLY_RLS_INSTANCE_ID "grpc.test-only.rls.instance_id"

namespace grpc_core {

class RlsLbConfig final : public LoadBalancingPolicy::Config {
 public:
  static constexpr Duration kMaxMaxAge = Duration::Minutes(5);

  struct KeyBuilder {
    std::map<std::string , std::vector<std::string >>
        header_keys;
    std::string host_key;
    std::string service_key;
    std::string method_key;
    std::map<std::string , std::string > constant_keys;
  };
  using KeyBuilderMap = std::unordered_map<std::string , KeyBuilder>;

  RlsLbConfig() = default;

  RlsLbConfig(const RlsLbConfig&) = delete;
  RlsLbConfig& operator=(const RlsLbConfig&) = delete;

  RlsLbConfig(RlsLbConfig&& other) = delete;
  RlsLbConfig& operator=(RlsLbConfig&& other) = delete;

  static absl::string_view Name() { return "rls_experimental"; }

  absl::string_view name() const override { return Name(); }

  const KeyBuilderMap& key_builder_map() const {
    return route_lookup_config_.key_builder_map;
  }
  const std::string& lookup_service() const {
    return route_lookup_config_.lookup_service;
  }
  Duration lookup_service_timeout() const {
    return route_lookup_config_.lookup_service_timeout;
  }
  Duration max_age() const { return route_lookup_config_.max_age; }
  Duration stale_age() const { return route_lookup_config_.stale_age; }
  int64_t cache_size_bytes() const {
    return route_lookup_config_.cache_size_bytes;
  }
  const std::string& default_target() const {
    return route_lookup_config_.default_target;
  }
  const std::string& rls_channel_service_config() const {
    return rls_channel_service_config_;
  }
  const Json& child_policy_config() const { return child_policy_config_; }
  const std::string& child_policy_config_target_field_name() const {
    return child_policy_config_target_field_name_;
  }
  RefCountedPtr<LoadBalancingPolicy::Config>
  default_child_policy_parsed_config() const {
    return default_child_policy_parsed_config_;
  }

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
  void JsonPostLoad(const Json& json, const JsonArgs&,
                    ValidationErrors* errors);

 private:
  struct RouteLookupConfig {
    KeyBuilderMap key_builder_map;
    std::string lookup_service;
    Duration lookup_service_timeout = Duration::Seconds(10);
    Duration max_age = kMaxMaxAge;
    Duration stale_age = kMaxMaxAge;
    int64_t cache_size_bytes = 0;
    std::string default_target;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
    void JsonPostLoad(const Json& json, const JsonArgs& args,
                      ValidationErrors* errors);
  };

  RouteLookupConfig route_lookup_config_;
  std::string rls_channel_service_config_;
  Json child_policy_config_;
  std::string child_policy_config_target_field_name_;
  RefCountedPtr<LoadBalancingPolicy::Config>
      default_child_policy_parsed_config_;
};

}

#endif
