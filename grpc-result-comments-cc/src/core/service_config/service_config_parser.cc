Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/service_config/service_config_parser.h"
#include <grpc/support/port_platform.h>
#include <stdlib.h>
#include <string>
#include "absl/log/log.h"

namespace grpc_core {

// Builds and returns a ServiceConfigParser instance by moving the registered parsers
// from the Builder to the new ServiceConfigParser instance.
ServiceConfigParser ServiceConfigParser::Builder::Build() {
  return ServiceConfigParser(std::move(registered_parsers_));
}

// Registers a new parser with the Builder. Ensures parser names are unique.
// If a parser with the same name already exists, logs an error and aborts.
// Otherwise, adds the parser to the list of registered parsers.
void ServiceConfigParser::Builder::RegisterParser(
    std::unique_ptr<Parser> parser) {
  // Check for existing parser with same name
  for (const auto& registered_parser : registered_parsers_) {
    if (registered_parser->name() == parser->name()) {
      LOG(ERROR) << "Parser with name '" << parser->name()
                 << "' already registered";
      abort();  // Terminate program on duplicate parser name
    }
  }
  // Add the new parser to registered parsers
  registered_parsers_.emplace_back(std::move(parser));
}

// Parses global parameters from JSON configuration using all registered parsers.
// Returns a vector of parsed configurations, one from each parser.
// Args:
//   args: Channel arguments
//   json: JSON configuration to parse
//   errors: ValidationErrors object to record any parsing errors
ServiceConfigParser::ParsedConfigVector
ServiceConfigParser::ParseGlobalParameters(const ChannelArgs& args,
                                           const Json& json,
                                           ValidationErrors* errors) const {
  ParsedConfigVector parsed_global_configs;
  // Process JSON through each registered parser
  for (auto& parser : registered_parsers_) {
    parsed_global_configs.push_back(
        parser->ParseGlobalParams(args, json, errors));
  }
  return parsed_global_configs;
}

// Parses per-method parameters from JSON configuration using all registered parsers.
// Returns a vector of parsed configurations, one from each parser.
// Args:
//   args: Channel arguments
//   json: JSON configuration to parse
//   errors: ValidationErrors object to record any parsing errors
ServiceConfigParser::ParsedConfigVector
ServiceConfigParser::ParsePerMethodParameters(const ChannelArgs& args,
                                              const Json& json,
                                              ValidationErrors* errors) const {
  ParsedConfigVector parsed_method_configs;
  // Process JSON through each registered parser
  for (auto& parser : registered_parsers_) {
    parsed_method_configs.push_back(
        parser->ParsePerMethodParams(args, json, errors));
  }
  return parsed_method_configs;
}

// Finds and returns the index of a parser by name.
// Returns -1 if no parser with the given name is found.
// Args:
//   name: Name of the parser to find
size_t ServiceConfigParser::GetParserIndex(absl::string_view name) const {
  for (size_t i = 0; i < registered_parsers_.size(); ++i) {
    if (registered_parsers_[i]->name() == name) return i;
  }
  return -1;  // Return -1 if parser not found
}

}  // namespace grpc_core
```

Key improvements made:
1. Added detailed function-level comments explaining purpose and behavior
2. Added parameter documentation for key methods
3. Added comments for important logic blocks
4. Explained return values
5. Noted error handling behavior
6. Maintained consistent comment style
7. Added namespace closing comment
8. Explained the purpose of the abort() call
9. Clarified the movement semantics in Build()

The comments now provide clear explanations of what each method does, its parameters, return values, and any special behaviors or constraints.