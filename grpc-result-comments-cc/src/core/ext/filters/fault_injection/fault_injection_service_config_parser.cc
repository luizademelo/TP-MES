Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/ext/filters/fault_injection/fault_injection_service_config_parser.h"

#include <grpc/support/port_platform.h>

#include <optional>
#include <vector>

#include "src/core/call/status_util.h"
#include "src/core/lib/channel/channel_args.h"

namespace grpc_core {

// JsonLoader implementation for FaultInjectionPolicy
// Defines how to parse JSON fields into FaultInjectionPolicy members
const JsonLoaderInterface*
FaultInjectionMethodParsedConfig::FaultInjectionPolicy::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<FaultInjectionPolicy>()
          // Optional fields for abort configuration
          .OptionalField("abortMessage", &FaultInjectionPolicy::abort_message)
          .OptionalField("abortCodeHeader",
                         &FaultInjectionPolicy::abort_code_header)
          .OptionalField("abortPercentageHeader",
                         &FaultInjectionPolicy::abort_percentage_header)
          .OptionalField("abortPercentageNumerator",
                         &FaultInjectionPolicy::abort_percentage_numerator)
          .OptionalField("abortPercentageDenominator",
                         &FaultInjectionPolicy::abort_percentage_denominator)
          // Optional fields for delay configuration
          .OptionalField("delay", &FaultInjectionPolicy::delay)
          .OptionalField("delayHeader", &FaultInjectionPolicy::delay_header)
          .OptionalField("delayPercentageHeader",
                         &FaultInjectionPolicy::delay_percentage_header)
          .OptionalField("delayPercentageNumerator",
                         &FaultInjectionPolicy::delay_percentage_numerator)
          .OptionalField("delayPercentageDenominator",
                         &FaultInjectionPolicy::delay_percentage_denominator)
          // Optional field for maximum faults
          .OptionalField("maxFaults", &FaultInjectionPolicy::max_faults)
          .Finish();
  return loader;
}

// Post-load validation for FaultInjectionPolicy
// Validates the parsed JSON configuration and reports any errors
void FaultInjectionMethodParsedConfig::FaultInjectionPolicy::JsonPostLoad(
    const Json& json, const JsonArgs& args, ValidationErrors* errors) {
  // Parse and validate abort code if present
  auto abort_code_string = LoadJsonObjectField<std::string>(
      json.object(), args, "abortCode", errors, false);
  if (abort_code_string.has_value() &&
      !grpc_status_code_from_string(abort_code_string->c_str(), &abort_code)) {
    ValidationErrors::ScopedField field(errors, ".abortCode");
    errors->AddError("failed to parse status code");
  }

  // Validate abort percentage denominator is one of allowed values
  if (abort_percentage_denominator != 100 &&
      abort_percentage_denominator != 10000 &&
      abort_percentage_denominator != 1000000) {
    ValidationErrors::ScopedField field(errors, ".abortPercentageDenominator");
    errors->AddError("must be one of 100, 10000, or 1000000");
  }

  // Validate delay percentage denominator is one of allowed values
  if (delay_percentage_denominator != 100 &&
      delay_percentage_denominator != 10000 &&
      delay_percentage_denominator != 1000000) {
    ValidationErrors::ScopedField field(errors, ".delayPercentageDenominator");
    errors->AddError("must be one of 100, 10000, or 1000000");
  }
}

// JsonLoader implementation for FaultInjectionMethodParsedConfig
const JsonLoaderInterface* FaultInjectionMethodParsedConfig::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<FaultInjectionMethodParsedConfig>()
          // Optional field for fault injection policies
          .OptionalField(
              "faultInjectionPolicy",
              &FaultInjectionMethodParsedConfig::fault_injection_policies_)
          .Finish();
  return loader;
}

// Parses fault injection parameters from JSON configuration
// Returns nullptr if fault injection parsing is disabled in channel args
std::unique_ptr<ServiceConfigParser::ParsedConfig>
FaultInjectionServiceConfigParser::ParsePerMethodParams(
    const ChannelArgs& args, const Json& json, ValidationErrors* errors) {
  // Check if fault injection parsing is enabled in channel args
  if (!args.GetBool(GRPC_ARG_PARSE_FAULT_INJECTION_METHOD_CONFIG)
           .value_or(false)) {
    return nullptr;
  }

  // Load and return the parsed configuration
  return LoadFromJson<std::unique_ptr<FaultInjectionMethodParsedConfig>>(
      json, JsonArgs(), errors);
}

// Registers the fault injection parser with the core configuration
void FaultInjectionServiceConfigParser::Register(
    CoreConfiguration::Builder* builder) {
  builder->service_config_parser()->RegisterParser(
      std::make_unique<FaultInjectionServiceConfigParser>());
}

// Returns the parser index for fault injection configuration
size_t FaultInjectionServiceConfigParser::ParserIndex() {
  return CoreConfiguration::Get().service_config_parser().GetParserIndex(
      parser_name());
}

}  // namespace grpc_core
```

The comments added explain:
1. The purpose of each method and class
2. The JSON parsing configuration for fault injection policies
3. The validation logic for the parsed values
4. The registration and lookup mechanisms for the parser
5. The conditional parsing based on channel arguments
6. The structure of the fault injection configuration

The comments are concise yet provide enough information for future maintainers to understand the code's functionality and purpose.