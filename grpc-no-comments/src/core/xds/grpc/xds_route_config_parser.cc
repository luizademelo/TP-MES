
// Copyright 2018 gRPC authors.

#include "src/core/xds/grpc/xds_route_config_parser.h"

#include <grpc/status.h>
#include <stddef.h>
#include <stdint.h>

#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "envoy/config/core/v3/base.upb.h"
#include "envoy/config/core/v3/extension.upb.h"
#include "envoy/config/route/v3/route.upb.h"
#include "envoy/config/route/v3/route.upbdefs.h"
#include "envoy/config/route/v3/route_components.upb.h"
#include "envoy/type/matcher/v3/regex.upb.h"
#include "envoy/type/matcher/v3/string.upb.h"
#include "envoy/type/v3/percent.upb.h"
#include "envoy/type/v3/range.upb.h"
#include "google/protobuf/any.upb.h"
#include "google/protobuf/duration.upb.h"
#include "google/protobuf/wrappers.upb.h"
#include "re2/re2.h"
#include "src/core/call/status_util.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/env.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/match.h"
#include "src/core/util/matchers.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/string.h"
#include "src/core/util/time.h"
#include "src/core/util/upb_utils.h"
#include "src/core/xds/grpc/xds_cluster_specifier_plugin.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_common_types_parser.h"
#include "src/core/xds/grpc/xds_http_filter.h"
#include "src/core/xds/grpc/xds_http_filter_registry.h"
#include "src/core/xds/grpc/xds_routing.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "upb/base/string_view.h"
#include "upb/message/map.h"
#include "upb/text/encode.h"

namespace grpc_core {

bool XdsRlsEnabled() {
  auto value = GetEnv("GRPC_EXPERIMENTAL_XDS_RLS_LB");
  if (!value.has_value()) return true;
  bool parsed_value;
  bool parse_succeeded = gpr_parse_bool_value(value->c_str(), &parsed_value);
  return parse_succeeded && parsed_value;
}

namespace {

XdsRouteConfigResource::ClusterSpecifierPluginMap ClusterSpecifierPluginParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_route_v3_RouteConfiguration* route_config,
    ValidationErrors* errors) {
  XdsRouteConfigResource::ClusterSpecifierPluginMap
      cluster_specifier_plugin_map;
  const auto& cluster_specifier_plugin_registry =
      DownCast<const GrpcXdsBootstrap&>(context.client->bootstrap())
          .cluster_specifier_plugin_registry();
  size_t num_cluster_specifier_plugins;
  const envoy_config_route_v3_ClusterSpecifierPlugin* const*
      cluster_specifier_plugin =
          envoy_config_route_v3_RouteConfiguration_cluster_specifier_plugins(
              route_config, &num_cluster_specifier_plugins);
  for (size_t i = 0; i < num_cluster_specifier_plugins; ++i) {
    bool is_optional = envoy_config_route_v3_ClusterSpecifierPlugin_is_optional(
        cluster_specifier_plugin[i]);
    ValidationErrors::ScopedField field(
        errors, absl::StrCat(".cluster_specifier_plugins[", i, "].extension"));
    const envoy_config_core_v3_TypedExtensionConfig* typed_extension_config =
        envoy_config_route_v3_ClusterSpecifierPlugin_extension(
            cluster_specifier_plugin[i]);
    if (typed_extension_config == nullptr) {
      errors->AddError("field not present");
      continue;
    }
    std::string name = UpbStringToStdString(
        envoy_config_core_v3_TypedExtensionConfig_name(typed_extension_config));
    if (cluster_specifier_plugin_map.find(name) !=
        cluster_specifier_plugin_map.end()) {
      ValidationErrors::ScopedField field(errors, ".name");
      errors->AddError(absl::StrCat("duplicate name \"", name, "\""));
    } else {

      cluster_specifier_plugin_map[name] = "<sentinel>";
    }
    ValidationErrors::ScopedField field2(errors, ".typed_config");
    const google_protobuf_Any* any =
        envoy_config_core_v3_TypedExtensionConfig_typed_config(
            typed_extension_config);
    auto extension = ExtractXdsExtension(context, any, errors);
    if (!extension.has_value()) continue;
    const XdsClusterSpecifierPluginImpl* cluster_specifier_plugin_impl =
        cluster_specifier_plugin_registry.GetPluginForType(extension->type);
    if (cluster_specifier_plugin_impl == nullptr) {
      if (is_optional) {

        cluster_specifier_plugin_map[std::move(name)] = "";
      } else {

        errors->AddError("unsupported ClusterSpecifierPlugin type");
      }
      continue;
    }
    const size_t original_error_size = errors->size();
    Json lb_policy_config =
        cluster_specifier_plugin_impl->GenerateLoadBalancingPolicyConfig(
            std::move(*extension), context.arena, context.symtab, errors);
    if (errors->size() != original_error_size) continue;
    auto config =
        CoreConfiguration::Get().lb_policy_registry().ParseLoadBalancingConfig(
            lb_policy_config);
    if (!config.ok()) {
      errors->AddError(absl::StrCat(
          "ClusterSpecifierPlugin returned invalid LB policy config: ",
          config.status().message()));
    } else {
      cluster_specifier_plugin_map[std::move(name)] =
          JsonDump(lb_policy_config);
    }
  }
  return cluster_specifier_plugin_map;
}

std::optional<StringMatcher> RoutePathMatchParse(
    const envoy_config_route_v3_RouteMatch* match, ValidationErrors* errors) {
  bool case_sensitive =
      ParseBoolValue(envoy_config_route_v3_RouteMatch_case_sensitive(match),
                     true);
  StringMatcher::Type type;
  std::string match_string;
  if (envoy_config_route_v3_RouteMatch_has_prefix(match)) {
    absl::string_view prefix =
        UpbStringToAbsl(envoy_config_route_v3_RouteMatch_prefix(match));

    if (!prefix.empty()) {

      if (prefix[0] != '/') return std::nullopt;
      std::vector<absl::string_view> prefix_elements =
          absl::StrSplit(prefix.substr(1), absl::MaxSplits('/', 2));

      if (prefix_elements.size() > 2) return std::nullopt;

      if (prefix_elements.size() == 2 && prefix_elements[0].empty()) {
        return std::nullopt;
      }
    }
    type = StringMatcher::Type::kPrefix;
    match_string = std::string(prefix);
  } else if (envoy_config_route_v3_RouteMatch_has_path(match)) {
    absl::string_view path =
        UpbStringToAbsl(envoy_config_route_v3_RouteMatch_path(match));

    if (path.empty()) return std::nullopt;

    if (path[0] != '/') return std::nullopt;
    std::vector<absl::string_view> path_elements =
        absl::StrSplit(path.substr(1), absl::MaxSplits('/', 2));

    if (path_elements.size() != 2) return std::nullopt;

    if (path_elements[0].empty()) return std::nullopt;

    if (path_elements[1].empty()) return std::nullopt;
    type = StringMatcher::Type::kExact;
    match_string = std::string(path);
  } else if (envoy_config_route_v3_RouteMatch_has_safe_regex(match)) {
    const envoy_type_matcher_v3_RegexMatcher* regex_matcher =
        envoy_config_route_v3_RouteMatch_safe_regex(match);
    CHECK_NE(regex_matcher, nullptr);
    type = StringMatcher::Type::kSafeRegex;
    match_string = UpbStringToStdString(
        envoy_type_matcher_v3_RegexMatcher_regex(regex_matcher));
  } else {
    errors->AddError("invalid path specifier");
    return std::nullopt;
  }
  absl::StatusOr<StringMatcher> string_matcher =
      StringMatcher::Create(type, match_string, case_sensitive);
  if (!string_matcher.ok()) {
    errors->AddError(absl::StrCat("error creating path matcher: ",
                                  string_matcher.status().message()));
    return std::nullopt;
  }
  return std::move(*string_matcher);
}

void RouteHeaderMatchersParse(const envoy_config_route_v3_RouteMatch* match,
                              XdsRouteConfigResource::Route* route,
                              ValidationErrors* errors) {
  size_t size;
  const envoy_config_route_v3_HeaderMatcher* const* headers =
      envoy_config_route_v3_RouteMatch_headers(match, &size);
  for (size_t i = 0; i < size; ++i) {
    ValidationErrors::ScopedField field(errors,
                                        absl::StrCat(".headers[", i, "]"));
    const envoy_config_route_v3_HeaderMatcher* header = headers[i];
    CHECK_NE(header, nullptr);
    const std::string name =
        UpbStringToStdString(envoy_config_route_v3_HeaderMatcher_name(header));
    HeaderMatcher::Type type;
    std::string match_string;
    int64_t range_start = 0;
    int64_t range_end = 0;
    bool present_match = false;
    bool case_sensitive = true;
    if (envoy_config_route_v3_HeaderMatcher_has_exact_match(header)) {
      type = HeaderMatcher::Type::kExact;
      match_string = UpbStringToStdString(
          envoy_config_route_v3_HeaderMatcher_exact_match(header));
    } else if (envoy_config_route_v3_HeaderMatcher_has_prefix_match(header)) {
      type = HeaderMatcher::Type::kPrefix;
      match_string = UpbStringToStdString(
          envoy_config_route_v3_HeaderMatcher_prefix_match(header));
    } else if (envoy_config_route_v3_HeaderMatcher_has_suffix_match(header)) {
      type = HeaderMatcher::Type::kSuffix;
      match_string = UpbStringToStdString(
          envoy_config_route_v3_HeaderMatcher_suffix_match(header));
    } else if (envoy_config_route_v3_HeaderMatcher_has_contains_match(header)) {
      type = HeaderMatcher::Type::kContains;
      match_string = UpbStringToStdString(
          envoy_config_route_v3_HeaderMatcher_contains_match(header));
    } else if (envoy_config_route_v3_HeaderMatcher_has_safe_regex_match(
                   header)) {
      const envoy_type_matcher_v3_RegexMatcher* regex_matcher =
          envoy_config_route_v3_HeaderMatcher_safe_regex_match(header);
      CHECK_NE(regex_matcher, nullptr);
      type = HeaderMatcher::Type::kSafeRegex;
      match_string = UpbStringToStdString(
          envoy_type_matcher_v3_RegexMatcher_regex(regex_matcher));
    } else if (envoy_config_route_v3_HeaderMatcher_has_range_match(header)) {
      type = HeaderMatcher::Type::kRange;
      const envoy_type_v3_Int64Range* range_matcher =
          envoy_config_route_v3_HeaderMatcher_range_match(header);
      CHECK_NE(range_matcher, nullptr);
      range_start = envoy_type_v3_Int64Range_start(range_matcher);
      range_end = envoy_type_v3_Int64Range_end(range_matcher);
    } else if (envoy_config_route_v3_HeaderMatcher_has_present_match(header)) {
      type = HeaderMatcher::Type::kPresent;
      present_match = envoy_config_route_v3_HeaderMatcher_present_match(header);
    } else if (envoy_config_route_v3_HeaderMatcher_has_string_match(header)) {
      ValidationErrors::ScopedField field(errors, ".string_match");
      const auto* matcher =
          envoy_config_route_v3_HeaderMatcher_string_match(header);
      CHECK_NE(matcher, nullptr);
      if (envoy_type_matcher_v3_StringMatcher_has_exact(matcher)) {
        type = HeaderMatcher::Type::kExact;
        match_string = UpbStringToStdString(
            envoy_type_matcher_v3_StringMatcher_exact(matcher));
      } else if (envoy_type_matcher_v3_StringMatcher_has_prefix(matcher)) {
        type = HeaderMatcher::Type::kPrefix;
        match_string = UpbStringToStdString(
            envoy_type_matcher_v3_StringMatcher_prefix(matcher));
      } else if (envoy_type_matcher_v3_StringMatcher_has_suffix(matcher)) {
        type = HeaderMatcher::Type::kSuffix;
        match_string = UpbStringToStdString(
            envoy_type_matcher_v3_StringMatcher_suffix(matcher));
      } else if (envoy_type_matcher_v3_StringMatcher_has_contains(matcher)) {
        type = HeaderMatcher::Type::kContains;
        match_string = UpbStringToStdString(
            envoy_type_matcher_v3_StringMatcher_contains(matcher));
      } else if (envoy_type_matcher_v3_StringMatcher_has_safe_regex(matcher)) {
        type = HeaderMatcher::Type::kSafeRegex;
        const auto* regex_matcher =
            envoy_type_matcher_v3_StringMatcher_safe_regex(matcher);
        CHECK_NE(regex_matcher, nullptr);
        match_string = UpbStringToStdString(
            envoy_type_matcher_v3_RegexMatcher_regex(regex_matcher));
      } else {
        errors->AddError("invalid string matcher");
        continue;
      }
      case_sensitive =
          !envoy_type_matcher_v3_StringMatcher_ignore_case(matcher);
    } else {
      errors->AddError("invalid header matcher");
      continue;
    }
    bool invert_match =
        envoy_config_route_v3_HeaderMatcher_invert_match(header);
    absl::StatusOr<HeaderMatcher> header_matcher =
        HeaderMatcher::Create(name, type, match_string, range_start, range_end,
                              present_match, invert_match, case_sensitive);
    if (!header_matcher.ok()) {
      errors->AddError(absl::StrCat("cannot create header matcher: ",
                                    header_matcher.status().message()));
    } else {
      route->matchers.header_matchers.emplace_back(std::move(*header_matcher));
    }
  }
}

void RouteRuntimeFractionParse(const envoy_config_route_v3_RouteMatch* match,
                               XdsRouteConfigResource::Route* route,
                               ValidationErrors* errors) {
  const envoy_config_core_v3_RuntimeFractionalPercent* runtime_fraction =
      envoy_config_route_v3_RouteMatch_runtime_fraction(match);
  if (runtime_fraction != nullptr) {
    const envoy_type_v3_FractionalPercent* fraction =
        envoy_config_core_v3_RuntimeFractionalPercent_default_value(
            runtime_fraction);
    if (fraction != nullptr) {
      uint32_t numerator = envoy_type_v3_FractionalPercent_numerator(fraction);
      const uint32_t denominator =
          envoy_type_v3_FractionalPercent_denominator(fraction);

      switch (denominator) {
        case envoy_type_v3_FractionalPercent_HUNDRED:
          numerator *= 10000;
          break;
        case envoy_type_v3_FractionalPercent_TEN_THOUSAND:
          numerator *= 100;
          break;
        case envoy_type_v3_FractionalPercent_MILLION:
          break;
        default: {
          ValidationErrors::ScopedField field(
              errors, ".runtime_fraction.default_value.denominator");
          errors->AddError("unknown denominator type");
          return;
        }
      }
      route->matchers.fraction_per_million = numerator;
    }
  }
}

template <typename ParentType>
XdsRouteConfigResource::TypedPerFilterConfig ParseTypedPerFilterConfig(
    const XdsResourceType::DecodeContext& context, const ParentType* parent,
    bool (*upb_next_func)(const ParentType*, upb_StringView*,
                          const struct google_protobuf_Any**, size_t* iter),
    ValidationErrors* errors) {
  XdsRouteConfigResource::TypedPerFilterConfig typed_per_filter_config;
  size_t filter_it = kUpb_Map_Begin;
  upb_StringView key_view;
  const struct google_protobuf_Any* any;
  while (upb_next_func(parent, &key_view, &any, &filter_it)) {
    absl::string_view key = UpbStringToAbsl(key_view);
    ValidationErrors::ScopedField field(errors, absl::StrCat("[", key, "]"));
    if (key.empty()) errors->AddError("filter name must be non-empty");
    auto extension = ExtractXdsExtension(context, any, errors);
    if (!extension.has_value()) continue;
    auto* extension_to_use = &*extension;
    std::optional<XdsExtension> nested_extension;
    bool is_optional = false;
    if (extension->type == "envoy.config.route.v3.FilterConfig") {
      absl::string_view* serialized_config =
          std::get_if<absl::string_view>(&extension->value);
      if (serialized_config == nullptr) {
        errors->AddError("could not parse FilterConfig");
        continue;
      }
      const auto* filter_config = envoy_config_route_v3_FilterConfig_parse(
          serialized_config->data(), serialized_config->size(), context.arena);
      if (filter_config == nullptr) {
        errors->AddError("could not parse FilterConfig");
        continue;
      }
      is_optional =
          envoy_config_route_v3_FilterConfig_is_optional(filter_config);
      any = envoy_config_route_v3_FilterConfig_config(filter_config);
      extension->validation_fields.emplace_back(errors, ".config");
      nested_extension = ExtractXdsExtension(context, any, errors);
      if (!nested_extension.has_value()) continue;
      extension_to_use = &*nested_extension;
    }
    const auto& http_filter_registry =
        DownCast<const GrpcXdsBootstrap&>(context.client->bootstrap())
            .http_filter_registry();
    const XdsHttpFilterImpl* filter_impl =
        http_filter_registry.GetFilterForType(extension_to_use->type);
    if (filter_impl == nullptr) {
      if (!is_optional) errors->AddError("unsupported filter type");
      continue;
    }
    std::optional<XdsHttpFilterImpl::FilterConfig> filter_config =
        filter_impl->GenerateFilterConfigOverride(
            key, context, std::move(*extension_to_use), errors);
    if (filter_config.has_value()) {
      typed_per_filter_config[std::string(key)] = std::move(*filter_config);
    }
  }
  return typed_per_filter_config;
}

XdsRouteConfigResource::RetryPolicy RetryPolicyParse(
    const envoy_config_route_v3_RetryPolicy* retry_policy_proto,
    ValidationErrors* errors) {
  XdsRouteConfigResource::RetryPolicy retry_policy;
  auto retry_on = UpbStringToStdString(
      envoy_config_route_v3_RetryPolicy_retry_on(retry_policy_proto));
  std::vector<absl::string_view> codes = absl::StrSplit(retry_on, ',');
  for (const auto& code : codes) {
    if (code == "cancelled") {
      retry_policy.retry_on.Add(GRPC_STATUS_CANCELLED);
    } else if (code == "deadline-exceeded") {
      retry_policy.retry_on.Add(GRPC_STATUS_DEADLINE_EXCEEDED);
    } else if (code == "internal") {
      retry_policy.retry_on.Add(GRPC_STATUS_INTERNAL);
    } else if (code == "resource-exhausted") {
      retry_policy.retry_on.Add(GRPC_STATUS_RESOURCE_EXHAUSTED);
    } else if (code == "unavailable") {
      retry_policy.retry_on.Add(GRPC_STATUS_UNAVAILABLE);
    } else {
      if (GRPC_TRACE_FLAG_ENABLED(xds_client)) {
        LOG(INFO) << "Unsupported retry_on policy " << code;
      }
    }
  }
  retry_policy.num_retries =
      ParseUInt32Value(
          envoy_config_route_v3_RetryPolicy_num_retries(retry_policy_proto))
          .value_or(1);
  if (retry_policy.num_retries == 0) {
    ValidationErrors::ScopedField field(errors, ".num_retries");
    errors->AddError("must be greater than 0");
  }
  const envoy_config_route_v3_RetryPolicy_RetryBackOff* backoff =
      envoy_config_route_v3_RetryPolicy_retry_back_off(retry_policy_proto);
  if (backoff != nullptr) {
    ValidationErrors::ScopedField field(errors, ".retry_back_off");
    {
      ValidationErrors::ScopedField field(errors, ".base_interval");
      const google_protobuf_Duration* base_interval =
          envoy_config_route_v3_RetryPolicy_RetryBackOff_base_interval(backoff);
      if (base_interval == nullptr) {
        errors->AddError("field not present");
      } else {
        retry_policy.retry_back_off.base_interval =
            ParseDuration(base_interval, errors);
      }
    }
    {
      ValidationErrors::ScopedField field(errors, ".max_interval");
      const google_protobuf_Duration* max_interval =
          envoy_config_route_v3_RetryPolicy_RetryBackOff_max_interval(backoff);
      Duration max;
      if (max_interval != nullptr) {
        max = ParseDuration(max_interval, errors);
      } else {

        max = 10 * retry_policy.retry_back_off.base_interval;
      }
      retry_policy.retry_back_off.max_interval = max;
    }
  } else {
    retry_policy.retry_back_off.base_interval = Duration::Milliseconds(25);
    retry_policy.retry_back_off.max_interval = Duration::Milliseconds(250);
  }
  return retry_policy;
}

std::optional<XdsRouteConfigResource::Route::RouteAction> RouteActionParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_route_v3_RouteAction* route_action_proto,
    const std::map<std::string ,
                   std::string >&
        cluster_specifier_plugin_map,
    ValidationErrors* errors) {
  XdsRouteConfigResource::Route::RouteAction route_action;

  const auto* max_stream_duration =
      envoy_config_route_v3_RouteAction_max_stream_duration(route_action_proto);
  if (max_stream_duration != nullptr) {
    ValidationErrors::ScopedField field(errors, ".max_stream_duration");
    if (const google_protobuf_Duration* duration =
            envoy_config_route_v3_RouteAction_MaxStreamDuration_grpc_timeout_header_max(
                max_stream_duration);
        duration != nullptr) {
      ValidationErrors::ScopedField field(errors, ".grpc_timeout_header_max");
      route_action.max_stream_duration = ParseDuration(duration, errors);
    } else if (
        duration =
            envoy_config_route_v3_RouteAction_MaxStreamDuration_max_stream_duration(
                max_stream_duration);
        duration != nullptr) {
      ValidationErrors::ScopedField field(errors, ".max_stream_duration");
      route_action.max_stream_duration = ParseDuration(duration, errors);
    }
  }

  size_t size = 0;
  const envoy_config_route_v3_RouteAction_HashPolicy* const* hash_policies =
      envoy_config_route_v3_RouteAction_hash_policy(route_action_proto, &size);
  for (size_t i = 0; i < size; ++i) {
    ValidationErrors::ScopedField field(errors,
                                        absl::StrCat(".hash_policy[", i, "]"));
    const auto* hash_policy = hash_policies[i];
    XdsRouteConfigResource::Route::RouteAction::HashPolicy policy;
    policy.terminal =
        envoy_config_route_v3_RouteAction_HashPolicy_terminal(hash_policy);
    const envoy_config_route_v3_RouteAction_HashPolicy_Header* header;
    const envoy_config_route_v3_RouteAction_HashPolicy_FilterState*
        filter_state;
    if ((header = envoy_config_route_v3_RouteAction_HashPolicy_header(
             hash_policy)) != nullptr) {

      ValidationErrors::ScopedField field(errors, ".header");
      XdsRouteConfigResource::Route::RouteAction::HashPolicy::Header
          header_policy;
      header_policy.header_name = UpbStringToStdString(
          envoy_config_route_v3_RouteAction_HashPolicy_Header_header_name(
              header));
      if (header_policy.header_name.empty()) {
        ValidationErrors::ScopedField field(errors, ".header_name");
        errors->AddError("must be non-empty");
      }

      const auto* regex_rewrite =
          envoy_config_route_v3_RouteAction_HashPolicy_Header_regex_rewrite(
              header);
      if (regex_rewrite != nullptr) {
        ValidationErrors::ScopedField field(errors, ".regex_rewrite.pattern");
        const auto* pattern =
            envoy_type_matcher_v3_RegexMatchAndSubstitute_pattern(
                regex_rewrite);
        if (pattern == nullptr) {
          errors->AddError("field not present");
          continue;
        }
        ValidationErrors::ScopedField field2(errors, ".regex");
        std::string regex = UpbStringToStdString(
            envoy_type_matcher_v3_RegexMatcher_regex(pattern));
        if (regex.empty()) {
          errors->AddError("field not present");
          continue;
        }
        RE2::Options options;
        header_policy.regex = std::make_unique<RE2>(regex, options);
        if (!header_policy.regex->ok()) {
          errors->AddError(absl::StrCat("errors compiling regex: ",
                                        header_policy.regex->error()));
          continue;
        }
        header_policy.regex_substitution = UpbStringToStdString(
            envoy_type_matcher_v3_RegexMatchAndSubstitute_substitution(
                regex_rewrite));
      }
      policy.policy = std::move(header_policy);
    } else if ((filter_state =
                    envoy_config_route_v3_RouteAction_HashPolicy_filter_state(
                        hash_policy)) != nullptr) {

      std::string key = UpbStringToStdString(
          envoy_config_route_v3_RouteAction_HashPolicy_FilterState_key(
              filter_state));
      if (key != "io.grpc.channel_id") continue;
      policy.policy =
          XdsRouteConfigResource::Route::RouteAction::HashPolicy::ChannelId();
    } else {

      continue;
    }
    route_action.hash_policies.emplace_back(std::move(policy));
  }

  const envoy_config_route_v3_RetryPolicy* retry_policy =
      envoy_config_route_v3_RouteAction_retry_policy(route_action_proto);
  if (retry_policy != nullptr) {
    ValidationErrors::ScopedField field(errors, ".retry_policy");
    route_action.retry_policy = RetryPolicyParse(retry_policy, errors);
  }

  if (DownCast<const GrpcXdsServer&>(context.server).TrustedXdsServer()) {
    route_action.auto_host_rewrite =
        ParseBoolValue(envoy_config_route_v3_RouteAction_auto_host_rewrite(
            route_action_proto));
  }

  if (envoy_config_route_v3_RouteAction_has_cluster(route_action_proto)) {

    std::string cluster_name = UpbStringToStdString(
        envoy_config_route_v3_RouteAction_cluster(route_action_proto));
    if (cluster_name.empty()) {
      ValidationErrors::ScopedField field(errors, ".cluster");
      errors->AddError("must be non-empty");
    }
    route_action.action =
        XdsRouteConfigResource::Route::RouteAction::ClusterName{
            std::move(cluster_name)};
  } else if (envoy_config_route_v3_RouteAction_has_weighted_clusters(
                 route_action_proto)) {

    ValidationErrors::ScopedField field(errors, ".weighted_clusters");
    const envoy_config_route_v3_WeightedCluster* weighted_clusters_proto =
        envoy_config_route_v3_RouteAction_weighted_clusters(route_action_proto);
    CHECK_NE(weighted_clusters_proto, nullptr);
    std::vector<XdsRouteConfigResource::Route::RouteAction::ClusterWeight>
        action_weighted_clusters;
    uint64_t total_weight = 0;
    size_t clusters_size;
    const envoy_config_route_v3_WeightedCluster_ClusterWeight* const* clusters =
        envoy_config_route_v3_WeightedCluster_clusters(weighted_clusters_proto,
                                                       &clusters_size);
    for (size_t i = 0; i < clusters_size; ++i) {
      ValidationErrors::ScopedField field(errors,
                                          absl::StrCat(".clusters[", i, "]"));
      const auto* cluster_proto = clusters[i];
      XdsRouteConfigResource::Route::RouteAction::ClusterWeight cluster;

      {
        ValidationErrors::ScopedField field(errors, ".typed_per_filter_config");
        cluster.typed_per_filter_config = ParseTypedPerFilterConfig<
            envoy_config_route_v3_WeightedCluster_ClusterWeight>(
            context, cluster_proto,
            envoy_config_route_v3_WeightedCluster_ClusterWeight_typed_per_filter_config_next,
            errors);
      }

      cluster.name = UpbStringToStdString(
          envoy_config_route_v3_WeightedCluster_ClusterWeight_name(
              cluster_proto));
      if (cluster.name.empty()) {
        ValidationErrors::ScopedField field(errors, ".name");
        errors->AddError("must be non-empty");
      }

      auto weight = ParseUInt32Value(
          envoy_config_route_v3_WeightedCluster_ClusterWeight_weight(
              cluster_proto));
      if (!weight.has_value()) {
        ValidationErrors::ScopedField field(errors, ".weight");
        errors->AddError("field not present");
      } else {
        cluster.weight = *weight;
        if (cluster.weight == 0) continue;
        total_weight += cluster.weight;
      }

      action_weighted_clusters.emplace_back(std::move(cluster));
    }
    if (action_weighted_clusters.empty()) {
      errors->AddError("no valid clusters specified");
    } else if (total_weight > std::numeric_limits<uint32_t>::max()) {
      errors->AddError("sum of cluster weights exceeds uint32 max");
    }
    route_action.action = std::move(action_weighted_clusters);
  } else if (XdsRlsEnabled() &&
             envoy_config_route_v3_RouteAction_has_cluster_specifier_plugin(
                 route_action_proto)) {

    ValidationErrors::ScopedField field(errors, ".cluster_specifier_plugin");
    std::string plugin_name = UpbStringToStdString(
        envoy_config_route_v3_RouteAction_cluster_specifier_plugin(
            route_action_proto));
    if (plugin_name.empty()) {
      errors->AddError("must be non-empty");
      return std::nullopt;
    }
    auto it = cluster_specifier_plugin_map.find(plugin_name);
    if (it == cluster_specifier_plugin_map.end()) {
      errors->AddError(absl::StrCat("unknown cluster specifier plugin name \"",
                                    plugin_name, "\""));
    } else {

      if (it->second.empty()) return std::nullopt;
    }
    route_action.action =
        XdsRouteConfigResource::Route::RouteAction::ClusterSpecifierPluginName{
            std::move(plugin_name)};
  } else {

    return std::nullopt;
  }
  return route_action;
}

std::optional<XdsRouteConfigResource::Route> ParseRoute(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_route_v3_Route* route_proto,
    const std::optional<XdsRouteConfigResource::RetryPolicy>&
        virtual_host_retry_policy,
    const XdsRouteConfigResource::ClusterSpecifierPluginMap&
        cluster_specifier_plugin_map,
    std::set<absl::string_view>* cluster_specifier_plugins_not_seen,
    ValidationErrors* errors) {
  XdsRouteConfigResource::Route route;

  {
    ValidationErrors::ScopedField field(errors, ".match");
    const auto* match = envoy_config_route_v3_Route_match(route_proto);
    if (match == nullptr) {
      errors->AddError("field not present");
      return std::nullopt;
    }

    size_t query_parameters_size;
    static_cast<void>(envoy_config_route_v3_RouteMatch_query_parameters(
        match, &query_parameters_size));
    if (query_parameters_size > 0) return std::nullopt;

    auto path_matcher = RoutePathMatchParse(match, errors);
    if (!path_matcher.has_value()) return std::nullopt;
    route.matchers.path_matcher = std::move(*path_matcher);
    RouteHeaderMatchersParse(match, &route, errors);
    RouteRuntimeFractionParse(match, &route, errors);
  }

  const envoy_config_route_v3_RouteAction* route_action_proto =
      envoy_config_route_v3_Route_route(route_proto);
  if (route_action_proto != nullptr) {
    ValidationErrors::ScopedField field(errors, ".route");
    auto route_action = RouteActionParse(context, route_action_proto,
                                         cluster_specifier_plugin_map, errors);
    if (!route_action.has_value()) return std::nullopt;

    if (!route_action->retry_policy.has_value()) {
      route_action->retry_policy = virtual_host_retry_policy;
    }

    auto* cluster_specifier_action = std::get_if<
        XdsRouteConfigResource::Route::RouteAction::ClusterSpecifierPluginName>(
        &route_action->action);
    if (cluster_specifier_action != nullptr) {
      cluster_specifier_plugins_not_seen->erase(
          cluster_specifier_action->cluster_specifier_plugin_name);
    }
    route.action = std::move(*route_action);
  } else if (envoy_config_route_v3_Route_has_non_forwarding_action(
                 route_proto)) {
    route.action = XdsRouteConfigResource::Route::NonForwardingAction();
  } else {

  }

  {
    ValidationErrors::ScopedField field(errors, ".typed_per_filter_config");
    route.typed_per_filter_config =
        ParseTypedPerFilterConfig<envoy_config_route_v3_Route>(
            context, route_proto,
            envoy_config_route_v3_Route_typed_per_filter_config_next, errors);
  }
  return route;
}

}

std::shared_ptr<const XdsRouteConfigResource> XdsRouteConfigResourceParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_route_v3_RouteConfiguration* route_config,
    ValidationErrors* errors) {
  auto rds_update = std::make_shared<XdsRouteConfigResource>();

  if (XdsRlsEnabled()) {
    rds_update->cluster_specifier_plugin_map =
        ClusterSpecifierPluginParse(context, route_config, errors);
  }

  std::set<absl::string_view> cluster_specifier_plugins_not_seen;
  for (auto& [name, _] : rds_update->cluster_specifier_plugin_map) {
    cluster_specifier_plugins_not_seen.emplace(name);
  }

  size_t num_virtual_hosts;
  const envoy_config_route_v3_VirtualHost* const* virtual_hosts =
      envoy_config_route_v3_RouteConfiguration_virtual_hosts(
          route_config, &num_virtual_hosts);
  for (size_t i = 0; i < num_virtual_hosts; ++i) {
    ValidationErrors::ScopedField field(
        errors, absl::StrCat(".virtual_hosts[", i, "]"));
    rds_update->virtual_hosts.emplace_back();
    XdsRouteConfigResource::VirtualHost& vhost =
        rds_update->virtual_hosts.back();

    size_t domain_size;
    upb_StringView const* domains = envoy_config_route_v3_VirtualHost_domains(
        virtual_hosts[i], &domain_size);
    for (size_t j = 0; j < domain_size; ++j) {
      std::string domain_pattern = UpbStringToStdString(domains[j]);
      if (!XdsRouting::IsValidDomainPattern(domain_pattern)) {
        ValidationErrors::ScopedField field(errors,
                                            absl::StrCat(".domains[", j, "]"));
        errors->AddError(
            absl::StrCat("invalid domain pattern \"", domain_pattern, "\""));
      }
      vhost.domains.emplace_back(std::move(domain_pattern));
    }
    if (vhost.domains.empty()) {
      ValidationErrors::ScopedField field(errors, ".domains");
      errors->AddError("must be non-empty");
    }

    {
      ValidationErrors::ScopedField field(errors, ".typed_per_filter_config");
      vhost.typed_per_filter_config =
          ParseTypedPerFilterConfig<envoy_config_route_v3_VirtualHost>(
              context, virtual_hosts[i],
              envoy_config_route_v3_VirtualHost_typed_per_filter_config_next,
              errors);
    }

    std::optional<XdsRouteConfigResource::RetryPolicy>
        virtual_host_retry_policy;
    const envoy_config_route_v3_RetryPolicy* retry_policy =
        envoy_config_route_v3_VirtualHost_retry_policy(virtual_hosts[i]);
    if (retry_policy != nullptr) {
      ValidationErrors::ScopedField field(errors, ".retry_policy");
      virtual_host_retry_policy = RetryPolicyParse(retry_policy, errors);
    }

    ValidationErrors::ScopedField field2(errors, ".routes");
    size_t num_routes;
    const envoy_config_route_v3_Route* const* routes =
        envoy_config_route_v3_VirtualHost_routes(virtual_hosts[i], &num_routes);
    for (size_t j = 0; j < num_routes; ++j) {
      ValidationErrors::ScopedField field(errors, absl::StrCat("[", j, "]"));
      auto route = ParseRoute(context, routes[j], virtual_host_retry_policy,
                              rds_update->cluster_specifier_plugin_map,
                              &cluster_specifier_plugins_not_seen, errors);
      if (route.has_value()) vhost.routes.emplace_back(std::move(*route));
    }
  }

  for (auto& unused_plugin : cluster_specifier_plugins_not_seen) {
    rds_update->cluster_specifier_plugin_map.erase(std::string(unused_plugin));
  }
  return rds_update;
}

namespace {

void MaybeLogRouteConfiguration(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_route_v3_RouteConfiguration* route_config) {
  if (GRPC_TRACE_FLAG_ENABLED(xds_client) && ABSL_VLOG_IS_ON(2)) {
    const upb_MessageDef* msg_type =
        envoy_config_route_v3_RouteConfiguration_getmsgdef(context.symtab);
    char buf[10240];
    upb_TextEncode(reinterpret_cast<const upb_Message*>(route_config), msg_type,
                   nullptr, 0, buf, sizeof(buf));
    VLOG(2) << "[xds_client " << context.client
            << "] RouteConfiguration: " << buf;
  }
}

}

XdsResourceType::DecodeResult XdsRouteConfigResourceType::Decode(
    const XdsResourceType::DecodeContext& context,
    absl::string_view serialized_resource) const {
  DecodeResult result;

  auto* resource = envoy_config_route_v3_RouteConfiguration_parse(
      serialized_resource.data(), serialized_resource.size(), context.arena);
  if (resource == nullptr) {
    result.resource =
        absl::InvalidArgumentError("Can't parse RouteConfiguration resource.");
    return result;
  }
  MaybeLogRouteConfiguration(context, resource);

  result.name = UpbStringToStdString(
      envoy_config_route_v3_RouteConfiguration_name(resource));
  ValidationErrors errors;
  auto rds_update = XdsRouteConfigResourceParse(context, resource, &errors);
  if (!errors.ok()) {
    absl::Status status =
        errors.status(absl::StatusCode::kInvalidArgument,
                      "errors validating RouteConfiguration resource");
    if (GRPC_TRACE_FLAG_ENABLED(xds_client)) {
      LOG(ERROR) << "[xds_client " << context.client
                 << "] invalid RouteConfiguration " << *result.name << ": "
                 << status;
    }
    result.resource = std::move(status);
  } else {
    if (GRPC_TRACE_FLAG_ENABLED(xds_client)) {
      LOG(INFO) << "[xds_client " << context.client
                << "] parsed RouteConfiguration " << *result.name << ": "
                << rds_update->ToString();
    }
    result.resource = std::move(rds_update);
  }
  return result;
}

}
