
// Copyright 2021 gRPC authors.

#include "src/core/xds/grpc/xds_http_fault_filter.h"

#include <grpc/status.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <string>
#include <utility>
#include <variant>

#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "envoy/extensions/filters/common/fault/v3/fault.upb.h"
#include "envoy/extensions/filters/http/fault/v3/fault.upb.h"
#include "envoy/extensions/filters/http/fault/v3/fault.upbdefs.h"
#include "envoy/type/v3/percent.upb.h"
#include "google/protobuf/wrappers.upb.h"
#include "src/core/call/status_util.h"
#include "src/core/ext/filters/fault_injection/fault_injection_filter.h"
#include "src/core/ext/filters/fault_injection/fault_injection_service_config_parser.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/transport/status_conversion.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/time.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_common_types_parser.h"
#include "src/core/xds/grpc/xds_http_filter.h"

namespace grpc_core {

namespace {

uint32_t GetDenominator(const envoy_type_v3_FractionalPercent* fraction) {
  if (fraction != nullptr) {
    const auto denominator =
        static_cast<envoy_type_v3_FractionalPercent_DenominatorType>(
            envoy_type_v3_FractionalPercent_denominator(fraction));
    switch (denominator) {
      case envoy_type_v3_FractionalPercent_MILLION:
        return 1000000;
      case envoy_type_v3_FractionalPercent_TEN_THOUSAND:
        return 10000;
      case envoy_type_v3_FractionalPercent_HUNDRED:
      default:
        return 100;
    }
  }

  return 100;
}

}

absl::string_view XdsHttpFaultFilter::ConfigProtoName() const {
  return "envoy.extensions.filters.http.fault.v3.HTTPFault";
}

absl::string_view XdsHttpFaultFilter::OverrideConfigProtoName() const {
  return "";
}

void XdsHttpFaultFilter::PopulateSymtab(upb_DefPool* symtab) const {
  envoy_extensions_filters_http_fault_v3_HTTPFault_getmsgdef(symtab);
}

std::optional<XdsHttpFilterImpl::FilterConfig>
XdsHttpFaultFilter::GenerateFilterConfig(
    absl::string_view ,
    const XdsResourceType::DecodeContext& context, XdsExtension extension,
    ValidationErrors* errors) const {
  absl::string_view* serialized_filter_config =
      std::get_if<absl::string_view>(&extension.value);
  if (serialized_filter_config == nullptr) {
    errors->AddError("could not parse fault injection filter config");
    return std::nullopt;
  }
  auto* http_fault = envoy_extensions_filters_http_fault_v3_HTTPFault_parse(
      serialized_filter_config->data(), serialized_filter_config->size(),
      context.arena);
  if (http_fault == nullptr) {
    errors->AddError("could not parse fault injection filter config");
    return std::nullopt;
  }

  Json::Object fault_injection_policy_json;

  const auto* fault_abort =
      envoy_extensions_filters_http_fault_v3_HTTPFault_abort(http_fault);
  if (fault_abort != nullptr) {
    ValidationErrors::ScopedField field(errors, ".abort");
    grpc_status_code abort_grpc_status_code = GRPC_STATUS_OK;

    if (int abort_grpc_status_code_raw =
            envoy_extensions_filters_http_fault_v3_FaultAbort_grpc_status(
                fault_abort);
        abort_grpc_status_code_raw != 0) {
      if (!grpc_status_code_from_int(abort_grpc_status_code_raw,
                                     &abort_grpc_status_code)) {
        ValidationErrors::ScopedField field(errors, ".grpc_status");
        errors->AddError(absl::StrCat("invalid gRPC status code: ",
                                      abort_grpc_status_code_raw));
      }
    } else if (
        int abort_http_status_code =
            envoy_extensions_filters_http_fault_v3_FaultAbort_http_status(
                fault_abort);
        abort_http_status_code != 0 && abort_http_status_code != 200) {
      abort_grpc_status_code =
          grpc_http2_status_to_grpc_status(abort_http_status_code);
    }

    fault_injection_policy_json["abortCode"] =
        Json::FromString(grpc_status_code_to_string(abort_grpc_status_code));

    if (envoy_extensions_filters_http_fault_v3_FaultAbort_has_header_abort(
            fault_abort)) {
      fault_injection_policy_json["abortCodeHeader"] =
          Json::FromString("x-envoy-fault-abort-grpc-request");
      fault_injection_policy_json["abortPercentageHeader"] =
          Json::FromString("x-envoy-fault-abort-percentage");
    }

    auto* percent =
        envoy_extensions_filters_http_fault_v3_FaultAbort_percentage(
            fault_abort);
    if (percent != nullptr) {
      fault_injection_policy_json["abortPercentageNumerator"] =
          Json::FromNumber(envoy_type_v3_FractionalPercent_numerator(percent));
      fault_injection_policy_json["abortPercentageDenominator"] =
          Json::FromNumber(GetDenominator(percent));
    }
  }

  const auto* fault_delay =
      envoy_extensions_filters_http_fault_v3_HTTPFault_delay(http_fault);
  if (fault_delay != nullptr) {
    ValidationErrors::ScopedField field(errors, ".delay");

    const auto* delay_duration =
        envoy_extensions_filters_common_fault_v3_FaultDelay_fixed_delay(
            fault_delay);
    if (delay_duration != nullptr) {
      ValidationErrors::ScopedField field(errors, ".fixed_delay");
      Duration duration = ParseDuration(delay_duration, errors);
      fault_injection_policy_json["delay"] =
          Json::FromString(duration.ToJsonString());
    }

    if (envoy_extensions_filters_common_fault_v3_FaultDelay_has_header_delay(
            fault_delay)) {
      fault_injection_policy_json["delayHeader"] =
          Json::FromString("x-envoy-fault-delay-request");
      fault_injection_policy_json["delayPercentageHeader"] =
          Json::FromString("x-envoy-fault-delay-request-percentage");
    }

    auto* percent =
        envoy_extensions_filters_common_fault_v3_FaultDelay_percentage(
            fault_delay);
    if (percent != nullptr) {
      fault_injection_policy_json["delayPercentageNumerator"] =
          Json::FromNumber(envoy_type_v3_FractionalPercent_numerator(percent));
      fault_injection_policy_json["delayPercentageDenominator"] =
          Json::FromNumber(GetDenominator(percent));
    }
  }

  auto max_fault_wrapper = ParseUInt32Value(
      envoy_extensions_filters_http_fault_v3_HTTPFault_max_active_faults(
          http_fault));
  if (max_fault_wrapper.has_value()) {
    fault_injection_policy_json["maxFaults"] =
        Json::FromNumber(*max_fault_wrapper);
  }
  return FilterConfig{ConfigProtoName(),
                      Json::FromObject(std::move(fault_injection_policy_json))};
}

std::optional<XdsHttpFilterImpl::FilterConfig>
XdsHttpFaultFilter::GenerateFilterConfigOverride(
    absl::string_view instance_name,
    const XdsResourceType::DecodeContext& context, XdsExtension extension,
    ValidationErrors* errors) const {

  return GenerateFilterConfig(instance_name, context, std::move(extension),
                              errors);
}

void XdsHttpFaultFilter::AddFilter(InterceptionChainBuilder& builder) const {
  builder.Add<FaultInjectionFilter>();
}

const grpc_channel_filter* XdsHttpFaultFilter::channel_filter() const {
  return &FaultInjectionFilter::kFilter;
}

ChannelArgs XdsHttpFaultFilter::ModifyChannelArgs(
    const ChannelArgs& args) const {
  return args.Set(GRPC_ARG_PARSE_FAULT_INJECTION_METHOD_CONFIG, 1);
}

absl::StatusOr<XdsHttpFilterImpl::ServiceConfigJsonEntry>
XdsHttpFaultFilter::GenerateMethodConfig(
    const FilterConfig& hcm_filter_config,
    const FilterConfig* filter_config_override) const {
  Json policy_json = filter_config_override != nullptr
                         ? filter_config_override->config
                         : hcm_filter_config.config;

  return ServiceConfigJsonEntry{"faultInjectionPolicy", JsonDump(policy_json)};
}

absl::StatusOr<XdsHttpFilterImpl::ServiceConfigJsonEntry>
XdsHttpFaultFilter::GenerateServiceConfig(
    const FilterConfig& ) const {
  return ServiceConfigJsonEntry{"", ""};
}

}
