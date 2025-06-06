Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/xds/grpc/xds_http_rbac_filter.h"

#include <grpc/support/json.h>
#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <string>
#include <utility>
#include <variant>

#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "envoy/config/core/v3/address.upb.h"
#include "envoy/config/rbac/v3/rbac.upb.h"
#include "envoy/config/route/v3/route_components.upb.h"
#include "envoy/extensions/filters/http/rbac/v3/rbac.upb.h"
#include "envoy/extensions/filters/http/rbac/v3/rbac.upbdefs.h"
#include "envoy/type/matcher/v3/metadata.upb.h"
#include "envoy/type/matcher/v3/path.upb.h"
#include "envoy/type/matcher/v3/regex.upb.h"
#include "envoy/type/matcher/v3/string.upb.h"
#include "envoy/type/v3/range.upb.h"
#include "google/protobuf/wrappers.upb.h"
#include "src/core/ext/filters/rbac/rbac_filter.h"
#include "src/core/ext/filters/rbac/rbac_service_config_parser.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/env.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/string.h"
#include "src/core/util/upb_utils.h"
#include "src/core/xds/grpc/xds_audit_logger_registry.h"
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"
#include "src/core/xds/grpc/xds_common_types_parser.h"
#include "src/core/xds/xds_client/xds_client.h"
#include "upb/base/string_view.h"
#include "upb/message/array.h"
#include "upb/message/map.h"

namespace grpc_core {

namespace {

// Checks if RBAC audit logging is enabled via environment variable
bool XdsRbacAuditLoggingEnabled() {
  auto value = GetEnv("GRPC_EXPERIMENTAL_XDS_RBAC_AUDIT_LOGGING");
  if (!value.has_value()) return false;
  bool parsed_value;
  bool parse_succeeded = gpr_parse_bool_value(value->c_str(), &parsed_value);
  return parse_succeeded && parsed_value;
}

// Converts a RegexMatcher proto message to JSON format
Json ParseRegexMatcherToJson(
    const envoy_type_matcher_v3_RegexMatcher* regex_matcher) {
  return Json::FromObject(
      {{"regex",
        Json::FromString(UpbStringToStdString(
            envoy_type_matcher_v3_RegexMatcher_regex(regex_matcher)))}});
}

// Converts an Int64Range proto message to JSON format
Json ParseInt64RangeToJson(const envoy_type_v3_Int64Range* range) {
  return Json::FromObject(
      {{"start", Json::FromNumber(envoy_type_v3_Int64Range_start(range))},
       {"end", Json::FromNumber(envoy_type_v3_Int64Range_end(range))}});
}

// Converts a StringMatcher proto message to JSON format
Json ParseStringMatcherToJson(
    const envoy_type_matcher_v3_StringMatcher* matcher,
    ValidationErrors* errors) {
  Json::Object json;
  // Handle different matching types (exact, prefix, suffix, regex, contains)
  if (envoy_type_matcher_v3_StringMatcher_has_exact(matcher)) {
    json.emplace("exact",
                 Json::FromString(UpbStringToStdString(
                     envoy_type_matcher_v3_StringMatcher_exact(matcher))));
  } else if (envoy_type_matcher_v3_StringMatcher_has_prefix(matcher)) {
    json.emplace("prefix",
                 Json::FromString(UpbStringToStdString(
                     envoy_type_matcher_v3_StringMatcher_prefix(matcher))));
  } else if (envoy_type_matcher_v3_StringMatcher_has_suffix(matcher)) {
    json.emplace("suffix",
                 Json::FromString(UpbStringToStdString(
                     envoy_type_matcher_v3_StringMatcher_suffix(matcher))));
  } else if (envoy_type_matcher_v3_StringMatcher_has_safe_regex(matcher)) {
    json.emplace("safeRegex",
                 ParseRegexMatcherToJson(
                     envoy_type_matcher_v3_StringMatcher_safe_regex(matcher)));
  } else if (envoy_type_matcher_v3_StringMatcher_has_contains(matcher)) {
    json.emplace("contains",
                 Json::FromString(UpbStringToStdString(
                     envoy_type_matcher_v3_StringMatcher_contains(matcher))));
  } else {
    errors->AddError("invalid match pattern");
  }
  // Add ignore_case flag
  json.emplace(
      "ignoreCase",
      Json::FromBool(envoy_type_matcher_v3_StringMatcher_ignore_case(matcher)));
  return Json::FromObject(std::move(json));
}

// Converts a HeaderMatcher proto message to JSON format
Json ParseHeaderMatcherToJson(const envoy_config_route_v3_HeaderMatcher* header,
                              ValidationErrors* errors) {
  Json::Object header_json;
  {
    // Validate and add header name
    ValidationErrors::ScopedField field(errors, ".name");
    std::string name =
        UpbStringToStdString(envoy_config_route_v3_HeaderMatcher_name(header));
    if (name == ":scheme") {
      errors->AddError("':scheme' not allowed in header");
    } else if (absl::StartsWith(name, "grpc-")) {
      errors->AddError("'grpc-' prefixes not allowed in header");
    }
    header_json.emplace("name", Json::FromString(std::move(name)));
  }
  // Handle different header matching types
  if (envoy_config_route_v3_HeaderMatcher_has_exact_match(header)) {
    header_json.emplace(
        "exactMatch",
        Json::FromString(UpbStringToStdString(
            envoy_config_route_v3_HeaderMatcher_exact_match(header))));
  } else if (envoy_config_route_v3_HeaderMatcher_has_safe_regex_match(header)) {
    header_json.emplace(
        "safeRegexMatch",
        ParseRegexMatcherToJson(
            envoy_config_route_v3_HeaderMatcher_safe_regex_match(header)));
  } else if (envoy_config_route_v3_HeaderMatcher_has_range_match(header)) {
    header_json.emplace(
        "rangeMatch",
        ParseInt64RangeToJson(
            envoy_config_route_v3_HeaderMatcher_range_match(header)));
  } else if (envoy_config_route_v3_HeaderMatcher_has_present_match(header)) {
    header_json.emplace(
        "presentMatch",
        Json::FromBool(
            envoy_config_route_v3_HeaderMatcher_present_match(header)));
  } else if (envoy_config_route_v3_HeaderMatcher_has_prefix_match(header)) {
    header_json.emplace(
        "prefixMatch",
        Json::FromString(UpbStringToStdString(
            envoy_config_route_v3_HeaderMatcher_prefix_match(header))));
  } else if (envoy_config_route_v3_HeaderMatcher_has_suffix_match(header)) {
    header_json.emplace(
        "suffixMatch",
        Json::FromString(UpbStringToStdString(
            envoy_config_route_v3_HeaderMatcher_suffix_match(header))));
  } else if (envoy_config_route_v3_HeaderMatcher_has_contains_match(header)) {
    header_json.emplace(
        "containsMatch",
        Json::FromString(UpbStringToStdString(
            envoy_config_route_v3_HeaderMatcher_contains_match(header))));
  } else if (envoy_config_route_v3_HeaderMatcher_has_string_match(header)) {
    header_json.emplace(
        "stringMatch",
        ParseStringMatcherToJson(
            envoy_config_route_v3_HeaderMatcher_string_match(header), errors));
  } else {
    errors->AddError("invalid route header matcher specified");
  }
  // Add invert_match flag
  header_json.emplace(
      "invertMatch",
      Json::FromBool(envoy_config_route_v3_HeaderMatcher_invert_match(header)));
  return Json::FromObject(std::move(header_json));
}

// Converts a PathMatcher proto message to JSON format
Json ParsePathMatcherToJson(const envoy_type_matcher_v3_PathMatcher* matcher,
                            ValidationErrors* errors) {
  ValidationErrors::ScopedField field(errors, ".path");
  const auto* path = envoy_type_matcher_v3_PathMatcher_path(matcher);
  if (path == nullptr) {
    errors->AddError("field not present");
    return Json();
  }
  Json path_json = ParseStringMatcherToJson(path, errors);
  return Json::FromObject({{"path", std::move(path_json)}});
}

// Converts a CidrRange proto message to JSON format
Json ParseCidrRangeToJson(const envoy_config_core_v3_CidrRange* range) {
  Json::Object json;
  json.emplace("addressPrefix",
               Json::FromString(UpbStringToStdString(
                   envoy_config_core_v3_CidrRange_address_prefix(range))));
  auto prefix_len =
      ParseUInt32Value(envoy_config_core_v3_CidrRange_prefix_len(range));
  if (prefix_len.has_value()) {
    json.emplace("prefixLen", Json::FromNumber(*prefix_len));
  }
  return Json::FromObject(std::move(json));
}

// Converts a MetadataMatcher proto message to JSON format
Json ParseMetadataMatcherToJson(
    const envoy_type_matcher_v3_MetadataMatcher* metadata_matcher) {
  return Json::FromObject({
      {"invert", Json::FromBool(envoy_type_matcher_v3_MetadataMatcher_invert(
                     metadata_matcher))},
  });
}

// Converts a Permission proto message to JSON format
Json ParsePermissionToJson(const envoy_config_rbac_v3_Permission* permission,
                           ValidationErrors* errors) {
  Json::Object permission_json;

  // Helper lambda to parse permission sets (AND/OR rules)
  auto parse_permission_set_to_json =
      [errors](const envoy_config_rbac_v3_Permission_Set* set) -> Json {
    Json::Array rules_json;
    size_t size;
    const envoy_config_rbac_v3_Permission* const* rules =
        envoy_config_rbac_v3_Permission_Set_rules(set, &size);
    for (size_t i = 0; i < size; ++i) {
      ValidationErrors::ScopedField field(errors,
                                          absl::StrCat(".rules[", i, "]"));
      Json permission_json = ParsePermissionToJson(rules[i], errors);
      rules_json.emplace_back(std::move(permission_json));
    }
    return Json::FromObject(
        {{"rules", Json::FromArray(std::move(rules_json))}});
  };

  // Handle different permission types
  if (envoy_config_rbac_v3_Permission_has_and_rules(permission)) {
    ValidationErrors::ScopedField field(errors, ".and_permission");
    const auto* and_rules =
        envoy_config_rbac_v3_Permission_and_rules(permission);
    Json permission_set_json = parse_permission_set_to_json(and_rules);
    permission_json.emplace("andRules", std::move(permission_set_json));
  } else if (envoy_config_rbac_v3_Permission_has_or_rules(permission)) {
    ValidationErrors::ScopedField field(errors, ".or_permission");
    const auto* or_rules = envoy_config_rbac_v3_Permission_or_rules(permission);
    Json permission_set_json = parse_permission_set_to_json(or_rules);
    permission_json.emplace("orRules", std::move(permission_set_json));
  } else if (envoy_config_rbac_v3_Permission_has_any(permission)) {
    permission_json.emplace(
        "any", Json::FromBool(envoy_config_rbac_v3_Permission_any(permission)));
  } else if (envoy_config_rbac_v3_Permission_has_header(permission)) {
    ValidationErrors::ScopedField field(errors, ".header");
    Json header_json = ParseHeaderMatcherToJson(
        envoy_config_rbac_v3_Permission_header(permission), errors);
    permission_json.emplace("header", std::move(header_json));
  } else if (envoy_config_rbac_v3_Permission_has_url_path(permission)) {
    ValidationErrors::ScopedField field(errors, ".url_path");
    Json url_path_json = ParsePathMatcherToJson(
        envoy_config_rbac_v3_Permission_url_path(permission), errors);
    permission_json.emplace("urlPath", std::move(url_path_json));
  } else if (envoy_config_rbac_v3_Permission_has_destination_ip(permission)) {
    permission_json.emplace(
        "destinationIp",
        ParseCidrRangeToJson(
            envoy_config_rbac_v3_Permission_destination_ip(permission)));
  } else if (envoy_config_rbac_v3_Permission_has_destination_port(permission)) {
    permission_json.emplace(
        "destinationPort",
        Json::FromNumber(
            envoy_config_rbac_v3_Permission_destination_port(permission)));
  } else if (envoy_config_rbac_v3_Permission_has_metadata(permission)) {
    permission_json.emplace(
        "metadata", ParseMetadataMatcherToJson(
                        envoy_config_rbac_v3_Permission_metadata(permission)));
  } else if (envoy_config_rbac_v3_Permission_has_not_rule(permission)) {
    ValidationErrors::ScopedField field(errors, ".not_rule");
    Json not_rule_json = ParsePermissionToJson(
        envoy_config_rbac_v3_Permission_not_rule(permission), errors);
    permission_json.emplace("notRule", std::move(not_rule_json));
  } else if (envoy_config_rbac_v3_Permission_has_requested_server_name(
                 permission)) {
    ValidationErrors::ScopedField field(errors, ".requested_server_name");
    Json requested_server_name_json = ParseStringMatcherToJson(
        envoy_config_rbac_v3_Permission_requested_server_name(permission),
        errors);
    permission_json.emplace("requestedServerName",
                            std::move(requested_server_name_json));
  } else {
    errors->AddError("invalid rule");
  }
  return Json::FromObject(std::move(permission_json));
}

// Converts a Principal proto message to JSON format
Json ParsePrincipalToJson(const envoy_config_rbac_v3_Principal* principal,
                          ValidationErrors* errors) {
  Json::Object principal_json;

  // Helper lambda to parse principal sets (AND/OR rules)
  auto parse_principal_set_to_json =
      [errors](const envoy_config_rbac_v3_Principal_Set* set) -> Json {
    Json::Array ids_json;
    size_t size;
    const envoy_config_rbac_v3_Principal* const* ids =
        envoy_config_rbac_v3_Principal_Set_ids(set, &size);
    for (size_t i = 0; i < size; ++i) {
      ValidationErrors::ScopedField field(errors,
                                          absl::StrCat(".ids[", i, "]"));
      Json principal_json = ParsePrincipalToJson(ids[i], errors);
      ids_json.emplace_back(std::move(principal_json));
    }
    return Json::FromObject({{"ids", Json::FromArray(std::move(ids_json))}});
  };

  // Handle different principal types
  if (envoy_config_rbac_v3_Principal_has_and_ids(principal)) {
    ValidationErrors::ScopedField field(errors, ".and_ids");
    const auto* and_rules = envoy_config_rbac_v3_Principal_and_ids(principal);
    Json principal_set_json = parse_principal_set_to_json(and_rules);
    principal_json.emplace("andIds", std::move(principal_set_json));
  } else if (envoy_config_rbac_v3_Principal_has_or_ids(principal)) {
    ValidationErrors::ScopedField field(errors, ".or_ids");
    const auto* or_rules = envoy_config_rbac_v3_Principal_or_ids(principal);
    Json principal_set_json = parse_principal_set_to_json(or_rules);
    principal_json.emplace("orIds", std::move(principal_set_json));
  } else if (envoy_config_rbac_v3_Principal_has_any(principal)) {
    principal_json.emplace(
        "any", Json::FromBool(envoy_config_rbac_v3_Principal_any(principal)));
  } else if (envoy_config_rbac_v3_Principal_has_authenticated(principal)) {
    Json::Object authenticated_json;
    const auto* principal_name =
        envoy_config_rbac_v3_Principal_Authenticated_principal_name(
            envoy_config_rbac_v3_Principal_authenticated(principal));
    if (principal_name != nullptr) {
      ValidationErrors::ScopedField field(errors,
                                          ".authenticated.principal_name");
      Json principal_name_json =
          ParseStringMatcherToJson(principal_name, errors);
      authenticated_json["principalName"] = std::move(principal_name_json);
    }
    principal_json["authenticated"] =
        Json::FromObject(std::move(authenticated_json));
  } else if (envoy_config_rbac_v3_Principal_has_source_ip(principal)) {
    principal_json.emplace(
        "sourceIp", ParseCidrRangeToJson(
                        envoy_config_rbac_v3_Principal_source_ip(principal)));
  } else if (envoy_config_rbac_v3_Principal_has_direct_