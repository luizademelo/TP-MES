
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_FAULT_INJECTION_FAULT_INJECTION_SERVICE_CONFIG_PARSER_H
#define GRPC_SRC_CORE_EXT_FILTERS_FAULT_INJECTION_FAULT_INJECTION_SERVICE_CONFIG_PARSER_H

#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <limits>
#include <memory>
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

#define GRPC_ARG_PARSE_FAULT_INJECTION_METHOD_CONFIG \
  "grpc.internal.parse_fault_injection_method_config"

namespace grpc_core {

class FaultInjectionMethodParsedConfig
    : public ServiceConfigParser::ParsedConfig {
 public:
  struct FaultInjectionPolicy {
    grpc_status_code abort_code = GRPC_STATUS_OK;
    std::string abort_message = "Fault injected";
    std::string abort_code_header;
    std::string abort_percentage_header;
    uint32_t abort_percentage_numerator = 0;
    uint32_t abort_percentage_denominator = 100;

    Duration delay;
    std::string delay_header;
    std::string delay_percentage_header;
    uint32_t delay_percentage_numerator = 0;
    uint32_t delay_percentage_denominator = 100;

    uint32_t max_faults = std::numeric_limits<uint32_t>::max();

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
    void JsonPostLoad(const Json& json, const JsonArgs&,
                      ValidationErrors* errors);
  };

  const FaultInjectionPolicy* fault_injection_policy(size_t index) const {
    if (index >= fault_injection_policies_.size()) {
      return nullptr;
    }
    return &fault_injection_policies_[index];
  }

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);

 private:
  std::vector<FaultInjectionPolicy> fault_injection_policies_;
};

class FaultInjectionServiceConfigParser final
    : public ServiceConfigParser::Parser {
 public:
  absl::string_view name() const override { return parser_name(); }

  std::unique_ptr<ServiceConfigParser::ParsedConfig> ParsePerMethodParams(
      const ChannelArgs& args, const Json& json,
      ValidationErrors* errors) override;

  static size_t ParserIndex();

  static void Register(CoreConfiguration::Builder* builder);

 private:
  static absl::string_view parser_name() { return "fault_injection"; }
};

}

#endif
