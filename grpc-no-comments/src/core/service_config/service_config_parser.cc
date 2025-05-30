
// Copyright 2015 gRPC authors.

#include "src/core/service_config/service_config_parser.h"

#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <string>

#include "absl/log/log.h"

namespace grpc_core {

ServiceConfigParser ServiceConfigParser::Builder::Build() {
  return ServiceConfigParser(std::move(registered_parsers_));
}

void ServiceConfigParser::Builder::RegisterParser(
    std::unique_ptr<Parser> parser) {
  for (const auto& registered_parser : registered_parsers_) {
    if (registered_parser->name() == parser->name()) {
      LOG(ERROR) << "Parser with name '" << parser->name()
                 << "' already registered";

      abort();
    }
  }
  registered_parsers_.emplace_back(std::move(parser));
}

ServiceConfigParser::ParsedConfigVector
ServiceConfigParser::ParseGlobalParameters(const ChannelArgs& args,
                                           const Json& json,
                                           ValidationErrors* errors) const {
  ParsedConfigVector parsed_global_configs;
  for (auto& parser : registered_parsers_) {
    parsed_global_configs.push_back(
        parser->ParseGlobalParams(args, json, errors));
  }
  return parsed_global_configs;
}

ServiceConfigParser::ParsedConfigVector
ServiceConfigParser::ParsePerMethodParameters(const ChannelArgs& args,
                                              const Json& json,
                                              ValidationErrors* errors) const {
  ParsedConfigVector parsed_method_configs;
  for (auto& parser : registered_parsers_) {
    parsed_method_configs.push_back(
        parser->ParsePerMethodParams(args, json, errors));
  }
  return parsed_method_configs;
}

size_t ServiceConfigParser::GetParserIndex(absl::string_view name) const {
  for (size_t i = 0; i < registered_parsers_.size(); ++i) {
    if (registered_parsers_[i]->name() == name) return i;
  }
  return -1;
}

}
