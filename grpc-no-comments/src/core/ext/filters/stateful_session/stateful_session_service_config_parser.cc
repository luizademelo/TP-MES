
// Copyright 2022 gRPC authors.

#include "src/core/ext/filters/stateful_session/stateful_session_service_config_parser.h"

#include <grpc/support/port_platform.h>

#include <optional>
#include <vector>

#include "src/core/lib/channel/channel_args.h"

namespace grpc_core {

const JsonLoaderInterface*
StatefulSessionMethodParsedConfig::CookieConfig::JsonLoader(const JsonArgs&) {
  static const auto* loader = JsonObjectLoader<CookieConfig>()
                                  .OptionalField("name", &CookieConfig::name)
                                  .OptionalField("path", &CookieConfig::path)
                                  .OptionalField("ttl", &CookieConfig::ttl)
                                  .Finish();
  return loader;
}

void StatefulSessionMethodParsedConfig::CookieConfig::JsonPostLoad(
    const Json&, const JsonArgs&, ValidationErrors* errors) {

  if (name.has_value() && name->empty()) {
    ValidationErrors::ScopedField field(errors, ".name");
    errors->AddError("must be non-empty");
  }
}

const JsonLoaderInterface* StatefulSessionMethodParsedConfig::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<StatefulSessionMethodParsedConfig>()
          .OptionalField("stateful_session",
                         &StatefulSessionMethodParsedConfig::configs_)
          .Finish();
  return loader;
}

std::unique_ptr<ServiceConfigParser::ParsedConfig>
StatefulSessionServiceConfigParser::ParsePerMethodParams(
    const ChannelArgs& args, const Json& json, ValidationErrors* errors) {

  if (!args.GetBool(GRPC_ARG_PARSE_STATEFUL_SESSION_METHOD_CONFIG)
           .value_or(false)) {
    return nullptr;
  }

  return LoadFromJson<std::unique_ptr<StatefulSessionMethodParsedConfig>>(
      json, JsonArgs(), errors);
}

void StatefulSessionServiceConfigParser::Register(
    CoreConfiguration::Builder* builder) {
  builder->service_config_parser()->RegisterParser(
      std::make_unique<StatefulSessionServiceConfigParser>());
}

size_t StatefulSessionServiceConfigParser::ParserIndex() {
  return CoreConfiguration::Get().service_config_parser().GetParserIndex(
      parser_name());
}

}
