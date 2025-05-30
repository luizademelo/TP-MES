
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_STATEFUL_SESSION_STATEFUL_SESSION_SERVICE_CONFIG_PARSER_H
#define GRPC_SRC_CORE_EXT_FILTERS_STATEFUL_SESSION_STATEFUL_SESSION_SERVICE_CONFIG_PARSER_H

#include <grpc/support/port_platform.h>
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
#include "src/core/util/time.h"
#include "src/core/util/validation_errors.h"

#define GRPC_ARG_PARSE_STATEFUL_SESSION_METHOD_CONFIG \
  "grpc.internal.parse_stateful_session_method_config"

namespace grpc_core {

class StatefulSessionMethodParsedConfig
    : public ServiceConfigParser::ParsedConfig {
 public:
  struct CookieConfig {
    std::optional<std::string> name;
    std::string path;
    Duration ttl;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
    void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors);
  };

  const CookieConfig* GetConfig(size_t index) const {
    if (index >= configs_.size()) return nullptr;
    return &configs_[index];
  }

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);

 private:
  std::vector<CookieConfig> configs_;
};

class StatefulSessionServiceConfigParser final
    : public ServiceConfigParser::Parser {
 public:
  absl::string_view name() const override { return parser_name(); }

  std::unique_ptr<ServiceConfigParser::ParsedConfig> ParsePerMethodParams(
      const ChannelArgs& args, const Json& json,
      ValidationErrors* errors) override;

  static size_t ParserIndex();

  static void Register(CoreConfiguration::Builder* builder);

 private:
  static absl::string_view parser_name() { return "stateful_session"; }
};

}

#endif
