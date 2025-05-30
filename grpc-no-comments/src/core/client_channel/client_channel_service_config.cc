
// Copyright 2018 gRPC authors.

#include "src/core/client_channel/client_channel_service_config.h"

#include <grpc/support/port_platform.h>

#include <map>
#include <optional>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/ascii.h"
#include "absl/strings/str_cat.h"
#include "src/core/load_balancing/lb_policy_registry.h"

#define MAX_MAX_RETRY_ATTEMPTS 5

namespace grpc_core {
namespace internal {

const JsonLoaderInterface*
ClientChannelGlobalParsedConfig::HealthCheckConfig::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<HealthCheckConfig>()
          .OptionalField("serviceName", &HealthCheckConfig::service_name)
          .Finish();
  return loader;
}

const JsonLoaderInterface* ClientChannelGlobalParsedConfig::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<ClientChannelGlobalParsedConfig>()
          // Note: "loadBalancingConfig" requires special handling, so

          .OptionalField(
              "loadBalancingPolicy",
              &ClientChannelGlobalParsedConfig::parsed_deprecated_lb_policy_)
          .OptionalField("healthCheckConfig",
                         &ClientChannelGlobalParsedConfig::health_check_config_)
          .Finish();
  return loader;
}

void ClientChannelGlobalParsedConfig::JsonPostLoad(const Json& json,
                                                   const JsonArgs&,
                                                   ValidationErrors* errors) {
  const auto& lb_policy_registry =
      CoreConfiguration::Get().lb_policy_registry();

  {
    ValidationErrors::ScopedField field(errors, ".loadBalancingConfig");
    auto it = json.object().find("loadBalancingConfig");
    if (it != json.object().end()) {
      auto config = lb_policy_registry.ParseLoadBalancingConfig(it->second);
      if (!config.ok()) {
        errors->AddError(config.status().message());
      } else {
        parsed_lb_config_ = std::move(*config);
      }
    }
  }

  if (!parsed_deprecated_lb_policy_.empty()) {
    ValidationErrors::ScopedField field(errors, ".loadBalancingPolicy");

    absl::AsciiStrToLower(&parsed_deprecated_lb_policy_);
    bool requires_config = false;
    if (!lb_policy_registry.LoadBalancingPolicyExists(
            parsed_deprecated_lb_policy_, &requires_config)) {
      errors->AddError(absl::StrCat("unknown LB policy \"",
                                    parsed_deprecated_lb_policy_, "\""));
    } else if (requires_config) {
      errors->AddError(absl::StrCat(
          "LB policy \"", parsed_deprecated_lb_policy_,
          "\" requires a config. Please use loadBalancingConfig instead."));
    }
  }
}

const JsonLoaderInterface* ClientChannelMethodParsedConfig::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<ClientChannelMethodParsedConfig>()
          .OptionalField("timeout", &ClientChannelMethodParsedConfig::timeout_)
          .OptionalField("waitForReady",
                         &ClientChannelMethodParsedConfig::wait_for_ready_)
          .Finish();
  return loader;
}

size_t ClientChannelServiceConfigParser::ParserIndex() {
  return CoreConfiguration::Get().service_config_parser().GetParserIndex(
      parser_name());
}

void ClientChannelServiceConfigParser::Register(
    CoreConfiguration::Builder* builder) {
  builder->service_config_parser()->RegisterParser(
      std::make_unique<ClientChannelServiceConfigParser>());
}

std::unique_ptr<ServiceConfigParser::ParsedConfig>
ClientChannelServiceConfigParser::ParseGlobalParams(const ChannelArgs& ,
                                                    const Json& json,
                                                    ValidationErrors* errors) {
  return LoadFromJson<std::unique_ptr<ClientChannelGlobalParsedConfig>>(
      json, JsonArgs(), errors);
}

std::unique_ptr<ServiceConfigParser::ParsedConfig>
ClientChannelServiceConfigParser::ParsePerMethodParams(
    const ChannelArgs& , const Json& json, ValidationErrors* errors) {
  return LoadFromJson<std::unique_ptr<ClientChannelMethodParsedConfig>>(
      json, JsonArgs(), errors);
}

}
}
