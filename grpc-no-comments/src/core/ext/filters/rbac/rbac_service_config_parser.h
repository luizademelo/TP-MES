
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_RBAC_RBAC_SERVICE_CONFIG_PARSER_H
#define GRPC_SRC_CORE_EXT_FILTERS_RBAC_RBAC_SERVICE_CONFIG_PARSER_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/security/authorization/grpc_authorization_engine.h"
#include "src/core/lib/security/authorization/rbac_policy.h"
#include "src/core/service_config/service_config_parser.h"
#include "src/core/util/json/json.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

#define GRPC_ARG_PARSE_RBAC_METHOD_CONFIG \
  "grpc.internal.parse_rbac_method_config"

class RbacMethodParsedConfig : public ServiceConfigParser::ParsedConfig {
 public:
  explicit RbacMethodParsedConfig(std::vector<Rbac> rbac_policies) {
    for (auto& rbac_policy : rbac_policies) {
      authorization_engines_.emplace_back(std::move(rbac_policy));
    }
  }

  const GrpcAuthorizationEngine* authorization_engine(size_t index) const {
    if (index >= authorization_engines_.size()) {
      return nullptr;
    }
    return &authorization_engines_[index];
  }

 private:
  std::vector<GrpcAuthorizationEngine> authorization_engines_;
};

class RbacServiceConfigParser : public ServiceConfigParser::Parser {
 public:
  absl::string_view name() const override { return parser_name(); }

  std::unique_ptr<ServiceConfigParser::ParsedConfig> ParsePerMethodParams(
      const ChannelArgs& args, const Json& json,
      ValidationErrors* errors) override;

  static size_t ParserIndex();

  static void Register(CoreConfiguration::Builder* builder);

 private:
  static absl::string_view parser_name() { return "rbac"; }
};

}

#endif
