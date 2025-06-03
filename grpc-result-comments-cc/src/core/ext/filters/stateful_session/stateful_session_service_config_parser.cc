Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#include "src/core/ext/filters/stateful_session/stateful_session_service_config_parser.h"

#include <grpc/support/port_platform.h>

#include <optional>
#include <vector>

#include "src/core/lib/channel/channel_args.h"

namespace grpc_core {

// Implementation of JsonLoader for CookieConfig structure
// Defines how to parse JSON fields into CookieConfig members
const JsonLoaderInterface*
StatefulSessionMethodParsedConfig::CookieConfig::JsonLoader(const JsonArgs&) {
  // Static JSON loader configuration for CookieConfig:
  // - Optional "name" field mapped to CookieConfig::name
  // - Optional "path" field mapped to CookieConfig::path
  // - Optional "ttl" field mapped to CookieConfig::ttl
  static const auto* loader = JsonObjectLoader<CookieConfig>()
                                  .OptionalField("name", &CookieConfig::name)
                                  .OptionalField("path", &CookieConfig::path)
                                  .OptionalField("ttl", &CookieConfig::ttl)
                                  .Finish();
  return loader;
}

// Post-load validation for CookieConfig JSON parsing
void StatefulSessionMethodParsedConfig::CookieConfig::JsonPostLoad(
    const Json&, const JsonArgs&, ValidationErrors* errors) {
  // Validate that if name is provided, it's not empty
  if (name.has_value() && name->empty()) {
    ValidationErrors::ScopedField field(errors, ".name");
    errors->AddError("must be non-empty");
  }
}

// Implementation of JsonLoader for StatefulSessionMethodParsedConfig
const JsonLoaderInterface* StatefulSessionMethodParsedConfig::JsonLoader(
    const JsonArgs&) {
  // Static JSON loader configuration for StatefulSessionMethodParsedConfig:
  // - Optional "stateful_session" field mapped to configs_ member
  static const auto* loader =
      JsonObjectLoader<StatefulSessionMethodParsedConfig>()
          .OptionalField("stateful_session",
                         &StatefulSessionMethodParsedConfig::configs_)
          .Finish();
  return loader;
}

// Parses per-method parameters from JSON configuration
std::unique_ptr<ServiceConfigParser::ParsedConfig>
StatefulSessionServiceConfigParser::ParsePerMethodParams(
    const ChannelArgs& args, const Json& json, ValidationErrors* errors) {
  // Only parse if stateful session method config parsing is enabled in channel args
  if (!args.GetBool(GRPC_ARG_PARSE_STATEFUL_SESSION_METHOD_CONFIG)
           .value_or(false)) {
    return nullptr;
  }

  // Load and parse the JSON configuration into a StatefulSessionMethodParsedConfig
  return LoadFromJson<std::unique_ptr<StatefulSessionMethodParsedConfig>>(
      json, JsonArgs(), errors);
}

// Registers the StatefulSessionServiceConfigParser with the core configuration
void StatefulSessionServiceConfigParser::Register(
    CoreConfiguration::Builder* builder) {
  builder->service_config_parser()->RegisterParser(
      std::make_unique<StatefulSessionServiceConfigParser>());
}

// Returns the parser index for this service config parser
size_t StatefulSessionServiceConfigParser::ParserIndex() {
  return CoreConfiguration::Get().service_config_parser().GetParserIndex(
      parser_name());
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each class and method
2. The JSON parsing configuration for CookieConfig and StatefulSessionMethodParsedConfig
3. The validation logic for cookie names
4. The conditional parsing based on channel arguments
5. The registration mechanism for the service config parser
6. The index retrieval functionality

The comments are kept concise while providing enough context to understand the code's functionality and purpose.