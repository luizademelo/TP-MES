
// Copyright 2021 gRPC authors.

#include "src/core/ext/filters/rbac/rbac_service_config_parser.h"

#include <grpc/grpc_audit_logging.h>
#include <grpc/support/port_platform.h>

#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/security/authorization/audit_logging.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/matchers.h"

namespace grpc_core {

namespace {

using experimental::AuditLoggerFactory;
using experimental::AuditLoggerRegistry;

struct RbacConfig {

  struct RbacPolicy {

    struct Rules {

      struct Policy {

        struct CidrRange {
          Rbac::CidrRange cidr_range;

          static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
          void JsonPostLoad(const Json& json, const JsonArgs& args,
                            ValidationErrors* errors);
        };

        struct SafeRegexMatch {
          std::string regex;

          static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
        };

        struct HeaderMatch {

          struct RangeMatch {
            int64_t start;
            int64_t end;

            static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
          };

          HeaderMatcher matcher;

          static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
          void JsonPostLoad(const Json& json, const JsonArgs& args,
                            ValidationErrors* errors);
        };

        struct StringMatch {
          StringMatcher matcher;

          static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
          void JsonPostLoad(const Json& json, const JsonArgs& args,
                            ValidationErrors* errors);
        };

        struct PathMatch {
          StringMatch path;

          static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
        };

        struct Metadata {
          bool invert = false;

          static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
        };

        struct Permission {

          struct PermissionList {
            std::vector<Permission> rules;

            PermissionList() = default;
            PermissionList(const PermissionList&) = delete;
            PermissionList& operator=(const PermissionList&) = delete;
            PermissionList(PermissionList&&) = default;
            PermissionList& operator=(PermissionList&&) = default;

            static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
          };

          std::unique_ptr<Rbac::Permission> permission;

          Permission() = default;
          Permission(const Permission&) = delete;
          Permission& operator=(const Permission&) = delete;
          Permission(Permission&&) = default;
          Permission& operator=(Permission&&) = default;

          static std::vector<std::unique_ptr<Rbac::Permission>>
          MakeRbacPermissionList(std::vector<Permission> permission_list);
          static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
          void JsonPostLoad(const Json& json, const JsonArgs& args,
                            ValidationErrors* errors);
        };

        struct Principal {

          struct PrincipalList {
            std::vector<Principal> ids;

            PrincipalList() = default;
            PrincipalList(const PrincipalList&) = delete;
            PrincipalList& operator=(const PrincipalList&) = delete;
            PrincipalList(PrincipalList&&) = default;
            PrincipalList& operator=(PrincipalList&&) = default;

            static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
          };

          struct Authenticated {
            std::optional<StringMatch> principal_name;

            static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
          };

          std::unique_ptr<Rbac::Principal> principal;

          Principal() = default;
          Principal(const Principal&) = delete;
          Principal& operator=(const Principal&) = delete;
          Principal(Principal&&) = default;
          Principal& operator=(Principal&&) = default;

          static std::vector<std::unique_ptr<Rbac::Principal>>
          MakeRbacPrincipalList(std::vector<Principal> principal_list);
          static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
          void JsonPostLoad(const Json& json, const JsonArgs& args,
                            ValidationErrors* errors);
        };

        std::vector<Permission> permissions;
        std::vector<Principal> principals;

        Policy() = default;
        Policy(const Policy&) = delete;
        Policy& operator=(const Policy&) = delete;
        Policy(Policy&&) = default;
        Policy& operator=(Policy&&) = default;

        Rbac::Policy TakeAsRbacPolicy();
        static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
      };

      struct AuditLogger {
        std::string name;
        Json::Object config;

        AuditLogger() = default;
        AuditLogger(const AuditLogger&) = delete;
        AuditLogger& operator=(const AuditLogger&) = delete;
        AuditLogger(AuditLogger&&) = default;
        AuditLogger& operator=(AuditLogger&&) = default;

        static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
        void JsonPostLoad(const Json&, const JsonArgs&,
                          ValidationErrors* errors);
      };

      int action = static_cast<int>(Rbac::Action::kDeny);
      std::map<std::string, Policy> policies;

      Rbac::AuditCondition audit_condition = Rbac::AuditCondition::kNone;
      std::vector<std::unique_ptr<AuditLoggerFactory::Config>> logger_configs;

      Rules() {}
      Rules(const Rules&) = delete;
      Rules& operator=(const Rules&) = delete;
      Rules(Rules&&) = default;
      Rules& operator=(Rules&&) = default;

      Rbac TakeAsRbac();
      static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
      void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors);
    };

    std::optional<Rules> rules;

    Rbac TakeAsRbac();
    static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
  };

  std::vector<RbacPolicy> rbac_policies;

  std::vector<Rbac> TakeAsRbacList();
  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
};

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::CidrRange::JsonLoader(const JsonArgs&) {

  static const auto* loader = JsonObjectLoader<CidrRange>().Finish();
  return loader;
}

void RbacConfig::RbacPolicy::Rules::Policy::CidrRange::JsonPostLoad(
    const Json& json, const JsonArgs& args, ValidationErrors* errors) {
  auto address_prefix = LoadJsonObjectField<std::string>(
      json.object(), args, "addressPrefix", errors);
  auto prefix_len =
      LoadJsonObjectField<uint32_t>(json.object(), args, "prefixLen", errors,
                                    false);
  cidr_range =
      Rbac::CidrRange(address_prefix.value_or(""), prefix_len.value_or(0));
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::SafeRegexMatch::JsonLoader(
    const JsonArgs&) {
  static const auto* loader = JsonObjectLoader<SafeRegexMatch>()
                                  .Field("regex", &SafeRegexMatch::regex)
                                  .Finish();
  return loader;
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::HeaderMatch::RangeMatch::JsonLoader(
    const JsonArgs&) {
  static const auto* loader = JsonObjectLoader<RangeMatch>()
                                  .Field("start", &RangeMatch::start)
                                  .Field("end", &RangeMatch::end)
                                  .Finish();
  return loader;
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::HeaderMatch::JsonLoader(
    const JsonArgs&) {

  static const auto* loader = JsonObjectLoader<HeaderMatch>().Finish();
  return loader;
}

void RbacConfig::RbacPolicy::Rules::Policy::HeaderMatch::JsonPostLoad(
    const Json& json, const JsonArgs& args, ValidationErrors* errors) {
  const size_t original_error_size = errors->size();
  std::string name =
      LoadJsonObjectField<std::string>(json.object(), args, "name", errors)
          .value_or("");
  bool invert_match =
      LoadJsonObjectField<bool>(json.object(), args, "invertMatch", errors,
                                false)
          .value_or(false);
  auto set_header_matcher = [&](absl::StatusOr<HeaderMatcher> header_matcher) {
    if (header_matcher.ok()) {
      matcher = *header_matcher;
    } else {
      errors->AddError(header_matcher.status().message());
    }
  };
  auto check_match = [&](absl::string_view field_name,
                         HeaderMatcher::Type type) {
    auto match = LoadJsonObjectField<std::string>(json.object(), args,
                                                  field_name, errors,
                                                  false);
    if (match.has_value()) {
      set_header_matcher(
          HeaderMatcher::Create(name, type, *match, 0, 0, false, invert_match));
      return true;
    }
    return false;
  };
  if (check_match("exactMatch", HeaderMatcher::Type::kExact) ||
      check_match("prefixMatch", HeaderMatcher::Type::kPrefix) ||
      check_match("suffixMatch", HeaderMatcher::Type::kSuffix) ||
      check_match("containsMatch", HeaderMatcher::Type::kContains)) {
    return;
  }
  auto present_match =
      LoadJsonObjectField<bool>(json.object(), args, "presentMatch", errors,
                                false);
  if (present_match.has_value()) {
    set_header_matcher(
        HeaderMatcher::Create(name, HeaderMatcher::Type::kPresent, "", 0, 0,
                              *present_match, invert_match));
    return;
  }
  auto regex_match = LoadJsonObjectField<SafeRegexMatch>(
      json.object(), args, "safeRegexMatch", errors,
      false);
  if (regex_match.has_value()) {
    set_header_matcher(
        HeaderMatcher::Create(name, HeaderMatcher::Type::kSafeRegex,
                              regex_match->regex, 0, 0, false, invert_match));
    return;
  }
  auto range_match =
      LoadJsonObjectField<RangeMatch>(json.object(), args, "rangeMatch", errors,
                                      false);
  if (range_match.has_value()) {
    set_header_matcher(HeaderMatcher::Create(name, HeaderMatcher::Type::kRange,
                                             "", range_match->start,
                                             range_match->end, invert_match));
    return;
  }
  auto string_match = LoadJsonObjectField<StringMatch>(
      json.object(), args, "stringMatch", errors, false);
  if (string_match.has_value()) {
    matcher = HeaderMatcher::CreateFromStringMatcher(
        name, std::move(string_match->matcher), invert_match);
    return;
  }
  if (errors->size() == original_error_size) {
    errors->AddError("no valid matcher found");
  }
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::StringMatch::JsonLoader(
    const JsonArgs&) {

  static const auto* loader = JsonObjectLoader<StringMatch>().Finish();
  return loader;
}

void RbacConfig::RbacPolicy::Rules::Policy::StringMatch::JsonPostLoad(
    const Json& json, const JsonArgs& args, ValidationErrors* errors) {
  const size_t original_error_size = errors->size();
  bool ignore_case =
      LoadJsonObjectField<bool>(json.object(), args, "ignoreCase", errors,
                                false)
          .value_or(false);
  auto set_string_matcher = [&](absl::StatusOr<StringMatcher> string_matcher) {
    if (string_matcher.ok()) {
      matcher = *string_matcher;
    } else {
      errors->AddError(string_matcher.status().message());
    }
  };
  auto check_match = [&](absl::string_view field_name,
                         StringMatcher::Type type) {
    auto match = LoadJsonObjectField<std::string>(json.object(), args,
                                                  field_name, errors,
                                                  false);
    if (match.has_value()) {
      set_string_matcher(
          StringMatcher::Create(type, *match, !ignore_case));
      return true;
    }
    return false;
  };
  if (check_match("exact", StringMatcher::Type::kExact) ||
      check_match("prefix", StringMatcher::Type::kPrefix) ||
      check_match("suffix", StringMatcher::Type::kSuffix) ||
      check_match("contains", StringMatcher::Type::kContains)) {
    return;
  }
  auto regex_match = LoadJsonObjectField<SafeRegexMatch>(json.object(), args,
                                                         "safeRegex", errors,
                                                         false);
  if (regex_match.has_value()) {
    set_string_matcher(StringMatcher::Create(StringMatcher::Type::kSafeRegex,
                                             regex_match->regex));
    return;
  }
  if (errors->size() == original_error_size) {
    errors->AddError("no valid matcher found");
  }
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::PathMatch::JsonLoader(const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<PathMatch>().Field("path", &PathMatch::path).Finish();
  return loader;
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::Metadata::JsonLoader(const JsonArgs&) {
  static const auto* loader = JsonObjectLoader<Metadata>()
                                  .OptionalField("invert", &Metadata::invert)
                                  .Finish();
  return loader;
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::Permission::PermissionList::JsonLoader(
    const JsonArgs&) {
  static const auto* loader = JsonObjectLoader<PermissionList>()
                                  .Field("rules", &PermissionList::rules)
                                  .Finish();
  return loader;
}

std::vector<std::unique_ptr<Rbac::Permission>>
RbacConfig::RbacPolicy::Rules::Policy::Permission::MakeRbacPermissionList(
    std::vector<Permission> permission_list) {
  std::vector<std::unique_ptr<Rbac::Permission>> permissions;
  permissions.reserve(permission_list.size());
  for (auto& rule : permission_list) {
    permissions.emplace_back(std::move(rule.permission));
  }
  return permissions;
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::Permission::JsonLoader(const JsonArgs&) {

  static const auto* loader = JsonObjectLoader<Permission>().Finish();
  return loader;
}

void RbacConfig::RbacPolicy::Rules::Policy::Permission::JsonPostLoad(
    const Json& json, const JsonArgs& args, ValidationErrors* errors) {
  const size_t original_error_size = errors->size();
  auto any = LoadJsonObjectField<bool>(json.object(), args, "any", errors,
                                       false);
  if (any.has_value()) {
    permission = std::make_unique<Rbac::Permission>(
        Rbac::Permission::MakeAnyPermission());
    return;
  }
  auto header =
      LoadJsonObjectField<HeaderMatch>(json.object(), args, "header", errors,
                                       false);
  if (header.has_value()) {
    permission = std::make_unique<Rbac::Permission>(
        Rbac::Permission::MakeHeaderPermission(std::move(header->matcher)));
    return;
  }
  auto url_path =
      LoadJsonObjectField<PathMatch>(json.object(), args, "urlPath", errors,
                                     false);
  if (url_path.has_value()) {
    permission = std::make_unique<Rbac::Permission>(
        Rbac::Permission::MakePathPermission(url_path->path.matcher));
    return;
  }
  auto destination_ip = LoadJsonObjectField<CidrRange>(json.object(), args,
                                                       "destinationIp", errors,
                                                       false);
  if (destination_ip.has_value()) {
    permission = std::make_unique<Rbac::Permission>(
        Rbac::Permission::MakeDestIpPermission(
            std::move(destination_ip->cidr_range)));
    return;
  }
  auto destination_port = LoadJsonObjectField<uint32_t>(
      json.object(), args, "destinationPort", errors,
      false);
  if (destination_port.has_value()) {
    permission = std::make_unique<Rbac::Permission>(
        Rbac::Permission::MakeDestPortPermission(*destination_port));
    return;
  }
  auto metadata =
      LoadJsonObjectField<Metadata>(json.object(), args, "metadata", errors,
                                    false);
  if (metadata.has_value()) {
    permission = std::make_unique<Rbac::Permission>(
        Rbac::Permission::MakeMetadataPermission(metadata->invert));
    return;
  }
  auto requested_server_name = LoadJsonObjectField<StringMatch>(
      json.object(), args, "requestedServerName", errors,
      false);
  if (requested_server_name.has_value()) {
    permission = std::make_unique<Rbac::Permission>(
        Rbac::Permission::MakeReqServerNamePermission(
            std::move(requested_server_name->matcher)));
    return;
  }
  auto rules = LoadJsonObjectField<PermissionList>(json.object(), args,
                                                   "andRules", errors,
                                                   false);
  if (rules.has_value()) {
    permission =
        std::make_unique<Rbac::Permission>(Rbac::Permission::MakeAndPermission(
            MakeRbacPermissionList(std::move(rules->rules))));
    return;
  }
  rules = LoadJsonObjectField<PermissionList>(json.object(), args, "orRules",
                                              errors,
                                              false);
  if (rules.has_value()) {
    permission =
        std::make_unique<Rbac::Permission>(Rbac::Permission::MakeOrPermission(
            MakeRbacPermissionList(std::move(rules->rules))));
    return;
  }
  auto not_rule =
      LoadJsonObjectField<Permission>(json.object(), args, "notRule", errors,
                                      false);
  if (not_rule.has_value()) {
    permission = std::make_unique<Rbac::Permission>(
        Rbac::Permission::MakeNotPermission(std::move(*not_rule->permission)));
    return;
  }
  if (errors->size() == original_error_size) {
    errors->AddError("no valid rule found");
  }
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::Principal::PrincipalList::JsonLoader(
    const JsonArgs&) {
  static const auto* loader = JsonObjectLoader<PrincipalList>()
                                  .Field("ids", &PrincipalList::ids)
                                  .Finish();
  return loader;
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::Principal::Authenticated::JsonLoader(
    const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<Authenticated>()
          .OptionalField("principalName", &Authenticated::principal_name)
          .Finish();
  return loader;
}

std::vector<std::unique_ptr<Rbac::Principal>>
RbacConfig::RbacPolicy::Rules::Policy::Principal::MakeRbacPrincipalList(
    std::vector<Principal> principal_list) {
  std::vector<std::unique_ptr<Rbac::Principal>> principals;
  principals.reserve(principal_list.size());
  for (auto& id : principal_list) {
    principals.emplace_back(std::move(id.principal));
  }
  return principals;
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::Policy::Principal::JsonLoader(const JsonArgs&) {

  static const auto* loader = JsonObjectLoader<Principal>().Finish();
  return loader;
}

void RbacConfig::RbacPolicy::Rules::Policy::Principal::JsonPostLoad(
    const Json& json, const JsonArgs& args, ValidationErrors* errors) {
  const size_t original_error_size = errors->size();
  auto any = LoadJsonObjectField<bool>(json.object(), args, "any", errors,
                                       false);
  if (any.has_value()) {
    principal =
        std::make_unique<Rbac::Principal>(Rbac::Principal::MakeAnyPrincipal());
    return;
  }
  auto authenticated = LoadJsonObjectField<Authenticated>(
      json.object(), args, "authenticated", errors,
      false);
  if (authenticated.has_value()) {
    if (authenticated->principal_name.has_value()) {
      principal = std::make_unique<Rbac::Principal>(
          Rbac::Principal::MakeAuthenticatedPrincipal(
              std::move(authenticated->principal_name->matcher)));
    } else {

      principal = std::make_unique<Rbac::Principal>(
          Rbac::Principal::MakeAnyPrincipal());
    }
    return;
  }
  auto cidr_range =
      LoadJsonObjectField<CidrRange>(json.object(), args, "sourceIp", errors,
                                     false);
  if (cidr_range.has_value()) {
    principal = std::make_unique<Rbac::Principal>(
        Rbac::Principal::MakeSourceIpPrincipal(
            std::move(cidr_range->cidr_range)));
    return;
  }
  cidr_range = LoadJsonObjectField<CidrRange>(json.object(), args,
                                              "directRemoteIp", errors,
                                              false);
  if (cidr_range.has_value()) {
    principal = std::make_unique<Rbac::Principal>(
        Rbac::Principal::MakeDirectRemoteIpPrincipal(
            std::move(cidr_range->cidr_range)));
    return;
  }
  cidr_range =
      LoadJsonObjectField<CidrRange>(json.object(), args, "remoteIp", errors,
                                     false);
  if (cidr_range.has_value()) {
    principal = std::make_unique<Rbac::Principal>(
        Rbac::Principal::MakeRemoteIpPrincipal(
            std::move(cidr_range->cidr_range)));
    return;
  }
  auto header =
      LoadJsonObjectField<HeaderMatch>(json.object(), args, "header", errors,
                                       false);
  if (header.has_value()) {
    principal = std::make_unique<Rbac::Principal>(
        Rbac::Principal::MakeHeaderPrincipal(std::move(header->matcher)));
    return;
  }
  auto url_path =
      LoadJsonObjectField<PathMatch>(json.object(), args, "urlPath", errors,
                                     false);
  if (url_path.has_value()) {
    principal = std::make_unique<Rbac::Principal>(
        Rbac::Principal::MakePathPrincipal(std::move(url_path->path.matcher)));
    return;
  }
  auto metadata =
      LoadJsonObjectField<Metadata>(json.object(), args, "metadata", errors,
                                    false);
  if (metadata.has_value()) {
    principal = std::make_unique<Rbac::Principal>(
        Rbac::Principal::MakeMetadataPrincipal(metadata->invert));
    return;
  }
  auto ids =
      LoadJsonObjectField<PrincipalList>(json.object(), args, "andIds", errors,
                                         false);
  if (ids.has_value()) {
    principal =
        std::make_unique<Rbac::Principal>(Rbac::Principal::MakeAndPrincipal(
            MakeRbacPrincipalList(std::move(ids->ids))));
    return;
  }
  ids = LoadJsonObjectField<PrincipalList>(json.object(), args, "orIds", errors,
                                           false);
  if (ids.has_value()) {
    principal =
        std::make_unique<Rbac::Principal>(Rbac::Principal::MakeOrPrincipal(
            MakeRbacPrincipalList(std::move(ids->ids))));
    return;
  }
  auto not_rule =
      LoadJsonObjectField<Principal>(json.object(), args, "notId", errors,
                                     false);
  if (not_rule.has_value()) {
    principal = std::make_unique<Rbac::Principal>(
        Rbac::Principal::MakeNotPrincipal(std::move(*not_rule->principal)));
    return;
  }
  if (errors->size() == original_error_size) {
    errors->AddError("no valid id found");
  }
}

Rbac::Policy RbacConfig::RbacPolicy::Rules::Policy::TakeAsRbacPolicy() {
  Rbac::Policy policy;
  policy.permissions = Rbac::Permission::MakeOrPermission(
      Permission::MakeRbacPermissionList(std::move(permissions)));
  policy.principals = Rbac::Principal::MakeOrPrincipal(
      Principal::MakeRbacPrincipalList(std::move(principals)));
  return policy;
}

const JsonLoaderInterface* RbacConfig::RbacPolicy::Rules::Policy::JsonLoader(
    const JsonArgs&) {
  static const auto* loader = JsonObjectLoader<Policy>()
                                  .Field("permissions", &Policy::permissions)
                                  .Field("principals", &Policy::principals)
                                  .Finish();
  return loader;
}

const JsonLoaderInterface*
RbacConfig::RbacPolicy::Rules::AuditLogger::JsonLoader(const JsonArgs&) {

  static const auto* loader = JsonObjectLoader<AuditLogger>().Finish();
  return loader;
}

void RbacConfig::RbacPolicy::Rules::AuditLogger::JsonPostLoad(
    const Json& json, const JsonArgs& args, ValidationErrors* errors) {

  if (json.object().size() != 1) {
    errors->AddError("audit logger should have exactly one field");
    return;
  }
  name = json.object().begin()->first;
  auto config_or =
      LoadJsonObjectField<Json::Object>(json.object(), args, name, errors);
  if (config_or.has_value()) {
    config = std::move(*config_or);
  }
}

Rbac RbacConfig::RbacPolicy::Rules::TakeAsRbac() {
  Rbac rbac;
  rbac.action = static_cast<Rbac::Action>(action);
  rbac.audit_condition = audit_condition;
  for (auto& p : policies) {
    rbac.policies.emplace(p.first, p.second.TakeAsRbacPolicy());
  }
  rbac.logger_configs = std::move(logger_configs);
  return rbac;
}

const JsonLoaderInterface* RbacConfig::RbacPolicy::Rules::JsonLoader(
    const JsonArgs&) {

  static const auto* loader = JsonObjectLoader<Rules>()
                                  .Field("action", &Rules::action)
                                  .OptionalField("policies", &Rules::policies)
                                  .Finish();
  return loader;
}

void RbacConfig::RbacPolicy::Rules::JsonPostLoad(const Json& json,
                                                 const JsonArgs& args,
                                                 ValidationErrors* errors) {

  auto rbac_action = static_cast<Rbac::Action>(action);
  if (rbac_action != Rbac::Action::kAllow &&
      rbac_action != Rbac::Action::kDeny) {
    ValidationErrors::ScopedField field(errors, ".action");
    errors->AddError(absl::StrCat("unknown action ", rbac_action));
  }

  auto condition = LoadJsonObjectField<int>(json.object(), args,
                                            "audit_condition", errors, false);
  if (condition.has_value()) {
    switch (*condition) {
      case static_cast<int>(Rbac::AuditCondition::kNone):
      case static_cast<int>(Rbac::AuditCondition::kOnAllow):
      case static_cast<int>(Rbac::AuditCondition::kOnDeny):
      case static_cast<int>(Rbac::AuditCondition::kOnDenyAndAllow):
        audit_condition = static_cast<Rbac::AuditCondition>(*condition);
        break;
      default: {
        ValidationErrors::ScopedField field(errors, ".audit_condition");
        errors->AddError("unknown audit condition");
      }
    }
  }

  auto configs = LoadJsonObjectField<std::vector<AuditLogger>>(
      json.object(), args, "audit_loggers", errors, false);
  if (configs.has_value()) {
    for (size_t i = 0; i < configs->size(); ++i) {
      auto& logger = (*configs)[i];
      auto config = AuditLoggerRegistry::ParseConfig(
          logger.name, Json::FromObject(std::move(logger.config)));
      if (!config.ok()) {
        ValidationErrors::ScopedField field(
            errors, absl::StrCat(".audit_loggers[", i, "]"));
        errors->AddError(config.status().message());
        continue;
      }
      logger_configs.push_back(std::move(*config));
    }
  }
}

Rbac RbacConfig::RbacPolicy::TakeAsRbac() {
  if (!rules.has_value()) {

    return Rbac("", Rbac::Action::kDeny, {});
  }
  return rules->TakeAsRbac();
}

const JsonLoaderInterface* RbacConfig::RbacPolicy::JsonLoader(const JsonArgs&) {
  static const auto* loader = JsonObjectLoader<RbacPolicy>()
                                  .OptionalField("rules", &RbacPolicy::rules)
                                  .Finish();
  return loader;
}

std::vector<Rbac> RbacConfig::TakeAsRbacList() {
  std::vector<Rbac> rbac_list;
  rbac_list.reserve(rbac_policies.size());
  for (auto& rbac_policy : rbac_policies) {
    rbac_list.emplace_back(rbac_policy.TakeAsRbac());
  }
  return rbac_list;
}

const JsonLoaderInterface* RbacConfig::JsonLoader(const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<RbacConfig>()
          .Field("rbacPolicy", &RbacConfig::rbac_policies)
          .Finish();
  return loader;
}

}

std::unique_ptr<ServiceConfigParser::ParsedConfig>
RbacServiceConfigParser::ParsePerMethodParams(const ChannelArgs& args,
                                              const Json& json,
                                              ValidationErrors* errors) {

  if (!args.GetBool(GRPC_ARG_PARSE_RBAC_METHOD_CONFIG).value_or(false)) {
    return nullptr;
  }
  auto rbac_config = LoadFromJson<RbacConfig>(json, JsonArgs(), errors);
  std::vector<Rbac> rbac_policies = rbac_config.TakeAsRbacList();
  if (rbac_policies.empty()) return nullptr;
  return std::make_unique<RbacMethodParsedConfig>(std::move(rbac_policies));
}

void RbacServiceConfigParser::Register(CoreConfiguration::Builder* builder) {
  builder->service_config_parser()->RegisterParser(
      std::make_unique<RbacServiceConfigParser>());
}

size_t RbacServiceConfigParser::ParserIndex() {
  return CoreConfiguration::Get().service_config_parser().GetParserIndex(
      parser_name());
}

}
