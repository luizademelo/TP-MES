
// Copyright 2024 gRPC authors.

#include "src/core/ext/filters/gcp_authentication/gcp_authentication_service_config_parser.h"

#include <grpc/support/port_platform.h>

#include <optional>
#include <vector>

#include "src/core/lib/channel/channel_args.h"

namespace grpc_core {

const JsonLoaderInterface* GcpAuthenticationParsedConfig::Config::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<Config>()
          .Field("filter_instance_name", &Config::filter_instance_name)
          .OptionalField("cache_size", &Config::cache_size)
          .Finish();
  return loader;
}

void GcpAuthenticationParsedConfig::Config::JsonPostLoad(
    const Json&, const JsonArgs&, ValidationErrors* errors) {
  if (cache_size == 0) {
    ValidationErrors::ScopedField field(errors, ".cache_size");
    errors->AddError("must be non-zero");
  }
}

const JsonLoaderInterface* GcpAuthenticationParsedConfig::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<GcpAuthenticationParsedConfig>()
          .OptionalField("gcp_authentication",
                         &GcpAuthenticationParsedConfig::configs_)
          .Finish();
  return loader;
}

std::unique_ptr<ServiceConfigParser::ParsedConfig>
GcpAuthenticationServiceConfigParser::ParseGlobalParams(
    const ChannelArgs& args, const Json& json, ValidationErrors* errors) {

  if (!args.GetBool(GRPC_ARG_PARSE_GCP_AUTHENTICATION_METHOD_CONFIG)
           .value_or(false)) {
    return nullptr;
  }

  return LoadFromJson<std::unique_ptr<GcpAuthenticationParsedConfig>>(
      json, JsonArgs(), errors);
}

void GcpAuthenticationServiceConfigParser::Register(
    CoreConfiguration::Builder* builder) {
  builder->service_config_parser()->RegisterParser(
      std::make_unique<GcpAuthenticationServiceConfigParser>());
}

size_t GcpAuthenticationServiceConfigParser::ParserIndex() {
  return CoreConfiguration::Get().service_config_parser().GetParserIndex(
      parser_name());
}

}
