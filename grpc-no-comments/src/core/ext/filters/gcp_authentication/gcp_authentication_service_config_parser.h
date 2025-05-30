
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_GCP_AUTHENTICATION_GCP_AUTHENTICATION_SERVICE_CONFIG_PARSER_H
#define GRPC_SRC_CORE_EXT_FILTERS_GCP_AUTHENTICATION_GCP_AUTHENTICATION_SERVICE_CONFIG_PARSER_H

#include <stddef.h>

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/service_config/service_config_parser.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/validation_errors.h"

#define GRPC_ARG_PARSE_GCP_AUTHENTICATION_METHOD_CONFIG \
  "grpc.internal.parse_gcp_authentication_method_config"

namespace grpc_core {

class GcpAuthenticationParsedConfig : public ServiceConfigParser::ParsedConfig {
 public:
  struct Config {
    std::string filter_instance_name;
    uint64_t cache_size = 10;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
    void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors);
  };

  const Config* GetConfig(size_t index) const {
    if (index >= configs_.size()) return nullptr;
    return &configs_[index];
  }

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);

 private:
  std::vector<Config> configs_;
};

class GcpAuthenticationServiceConfigParser final
    : public ServiceConfigParser::Parser {
 public:
  absl::string_view name() const override { return parser_name(); }
  std::unique_ptr<ServiceConfigParser::ParsedConfig> ParseGlobalParams(
      const ChannelArgs& args, const Json& json,
      ValidationErrors* errors) override;

  static size_t ParserIndex();

  static void Register(CoreConfiguration::Builder* builder);

 private:
  static absl::string_view parser_name() { return "gcp_auth"; }
};

}

#endif
