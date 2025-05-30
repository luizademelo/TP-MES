
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_SERVICE_CONFIG_SERVICE_CONFIG_PARSER_H
#define GRPC_SRC_CORE_SERVICE_CONFIG_SERVICE_CONFIG_PARSER_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/json/json.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

class ServiceConfigParser {
 public:

  class ParsedConfig {
   public:
    virtual ~ParsedConfig() = default;
  };

  class Parser {
   public:
    virtual ~Parser() = default;

    virtual absl::string_view name() const = 0;

    virtual std::unique_ptr<ParsedConfig> ParseGlobalParams(
        const ChannelArgs& , const Json& ,
        ValidationErrors* ) {
      return nullptr;
    }

    virtual std::unique_ptr<ParsedConfig> ParsePerMethodParams(
        const ChannelArgs& , const Json& ,
        ValidationErrors* ) {
      return nullptr;
    }
  };

  using ServiceConfigParserList = std::vector<std::unique_ptr<Parser>>;
  using ParsedConfigVector = std::vector<std::unique_ptr<ParsedConfig>>;

  class Builder final {
   public:

    void RegisterParser(std::unique_ptr<Parser> parser);

    ServiceConfigParser Build();

   private:
    ServiceConfigParserList registered_parsers_;
  };

  ParsedConfigVector ParseGlobalParameters(const ChannelArgs& args,
                                           const Json& json,
                                           ValidationErrors* errors) const;

  ParsedConfigVector ParsePerMethodParameters(const ChannelArgs& args,
                                              const Json& json,
                                              ValidationErrors* errors) const;

  size_t GetParserIndex(absl::string_view name) const;

 private:
  explicit ServiceConfigParser(ServiceConfigParserList registered_parsers)
      : registered_parsers_(std::move(registered_parsers)) {}
  ServiceConfigParserList registered_parsers_;
};

}

#endif
