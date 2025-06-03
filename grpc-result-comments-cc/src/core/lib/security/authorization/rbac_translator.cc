Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/lib/security/authorization/rbac_translator.h"

#include <grpc/grpc_audit_logging.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "src/core/lib/security/authorization/audit_logging.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/matchers.h"
#include "src/core/util/useful.h"

namespace grpc_core {

namespace {

using experimental::AuditLoggerRegistry;

// Determines the type of string matcher based on the input value pattern.
// Returns the appropriate matcher string and sets the type parameter.
// Patterns:
//   "*" becomes a regex matching ".+"
//   "*prefix" becomes a suffix matcher
//   "suffix*" becomes a prefix matcher
//   exact matches otherwise
absl::string_view GetMatcherType(absl::string_view value,
                                 StringMatcher::Type* type) {
  if (value == "*") {
    *type = StringMatcher::Type::kSafeRegex;
    return ".+";
  } else if (absl::StartsWith(value, "*")) {
    *type = StringMatcher::Type::kSuffix;
    return absl::StripPrefix(value, "*");
  } else if (absl::EndsWith(value, "*")) {
    *type = StringMatcher::Type::kPrefix;
    return absl::StripSuffix(value, "*");
  }
  *type = StringMatcher::Type::kExact;
  return value;
}

// Creates a StringMatcher for the given value using GetMatcherType
// to determine the matching pattern type.
absl::StatusOr<StringMatcher> GetStringMatcher(absl::string_view value) {
  StringMatcher::Type type;
  absl::string_view matcher = GetMatcherType(value, &type);
  return StringMatcher::Create(type, matcher);
}

// Creates a HeaderMatcher for the given header name and value.
// Uses GetMatcherType to determine the matching pattern type.
absl::StatusOr<HeaderMatcher> GetHeaderMatcher(absl::string_view name,
                                               absl::string_view value) {
  StringMatcher::Type type;
  absl::string_view matcher = GetMatcherType(value, &type);
  return HeaderMatcher::Create(name, static_cast<HeaderMatcher::Type>(type),
                               matcher);
}

// Checks if the given header is in the list of unsupported headers.
// These headers are typically related to HTTP connection management.
bool IsUnsupportedHeader(absl::string_view header_name) {
  static const char* const kUnsupportedHeaders[] = {"host",
                                                    "connection",
                                                    "keep-alive",
                                                    "proxy-authenticate",
                                                    "proxy-authorization",
                                                    "te",
                                                    "trailer",
                                                    "transfer-encoding",
                                                    "upgrade"};
  for (size_t i = 0; i < GPR_ARRAY_SIZE(kUnsupportedHeaders); ++i) {
    if (absl::EqualsIgnoreCase(header_name, kUnsupportedHeaders[i])) {
      return true;
    }
  }
  return false;
}

// Parses a JSON array of principals into a Principal object.
// Each principal in the array should be a string that can be converted to a StringMatcher.
absl::StatusOr<Rbac::Principal> ParsePrincipalsArray(const Json& json) {
  std::vector<std::unique_ptr<Rbac::Principal>> principal_names;
  for (size_t i = 0; i < json.array().size(); ++i) {
    const Json& child = json.array().at(i);
    if (child.type() != Json::Type::kString) {
      return absl::InvalidArgumentError(
          absl::StrCat("\"principals\" ", i, ": is not a string."));
    }
    auto matcher_or = GetStringMatcher(child.string());
    if (!matcher_or.ok()) {
      return absl::Status(matcher_or.status().code(),
                          absl::StrCat("\"principals\" ", i, ": ",
                                       matcher_or.status().message()));
    }
    principal_names.push_back(std::make_unique<Rbac::Principal>(
        Rbac::Principal::MakeAuthenticatedPrincipal(
            std::move(matcher_or.value()))));
  }
  return Rbac::Principal::MakeOrPrincipal(std::move(principal_names));
}

// Parses the "peer" object in the policy which contains principal information.
absl::StatusOr<Rbac::Principal> ParsePeer(const Json& json) {
  std::vector<std::unique_ptr<Rbac::Principal>> peer;
  for (const auto& object : json.object()) {
    if (object.first == "principals") {
      if (object.second.type() != Json::Type::kArray) {
        return absl::InvalidArgumentError("\"principals\" is not an array.");
      }
      auto principal_names_or = ParsePrincipalsArray(object.second);
      if (!principal_names_or.ok()) return principal_names_or.status();
      if (!principal_names_or.value().principals.empty()) {
        peer.push_back(std::make_unique<Rbac::Principal>(
            std::move(principal_names_or.value())));
      }
    } else {
      return absl::InvalidArgumentError(absl::StrFormat(
          "policy contains unknown field \"%s\" in \"source\".", object.first));
    }
  }
  if (peer.empty()) {
    return Rbac::Principal::MakeAnyPrincipal();
  }
  return Rbac::Principal::MakeAndPrincipal(std::move(peer));
}

// Parses an array of header values into a Permission object.
// Each value in the array should be a string that can be converted to a HeaderMatcher.
absl::StatusOr<Rbac::Permission> ParseHeaderValues(
    const Json& json, absl::string_view header_name) {
  if (json.array().empty()) {
    return absl::InvalidArgumentError("\"values\" list is empty.");
  }
  std::vector<std::unique_ptr<Rbac::Permission>> values;
  for (size_t i = 0; i < json.array().size(); ++i) {
    const Json& child = json.array().at(i);
    if (child.type() != Json::Type::kString) {
      return absl::InvalidArgumentError(
          absl::StrCat("\"values\" ", i, ": is not a string."));
    }
    auto matcher_or = GetHeaderMatcher(header_name, child.string());
    if (!matcher_or.ok()) {
      return absl::Status(
          matcher_or.status().code(),
          absl::StrCat("\"values\" ", i, ": ", matcher_or.status().message()));
    }
    values.push_back(std::make_unique<Rbac::Permission>(
        Rbac::Permission::MakeHeaderPermission(std::move(matcher_or.value()))));
  }
  return Rbac::Permission::MakeOrPermission(std::move(values));
}

// Parses a header object containing "key" and "values" fields into a Permission.
absl::StatusOr<Rbac::Permission> ParseHeaders(const Json& json) {
  absl::string_view key;
  const Json* values = nullptr;
  for (const auto& object : json.object()) {
    if (object.first == "key") {
      if (object.second.type() != Json::Type::kString) {
        return absl::InvalidArgumentError("\"key\" is not a string.");
      }
      key = object.second.string();
      if (absl::StartsWith(key, ":") || absl::StartsWith(key, "grpc-") ||
          IsUnsupportedHeader(key)) {
        return absl::InvalidArgumentError(
            absl::StrFormat("Unsupported \"key\" %s.", key));
      }
    } else if (object.first == "values") {
      if (object.second.type() != Json::Type::kArray) {
        return absl::InvalidArgumentError("\"values\" is not an array.");
      }
      values = &object.second;
    } else {
      return absl::InvalidArgumentError(absl::StrFormat(
          "policy contains unknown field \"%s\".", object.first));
    }
  }
  if (key.empty()) {
    return absl::InvalidArgumentError("\"key\" is not present.");
  }
  if (values == nullptr) {
    return absl::InvalidArgumentError("\"values\" is not present.");
  }
  return ParseHeaderValues(*values, key);
}

// Parses an array of header objects into a Permission.
absl::StatusOr<Rbac::Permission> ParseHeadersArray(const Json& json) {
  std::vector<std::unique_ptr<Rbac::Permission>> headers;
  for (size_t i = 0; i < json.array().size(); ++i) {
    const Json& child = json.array().at(i);
    if (child.type() != Json::Type::kObject) {
      return absl::InvalidArgumentError(
          absl::StrCat("\"headers\" ", i, ": is not an object."));
    }
    auto headers_or = ParseHeaders(child);
    if (!headers_or.ok()) {
      return absl::Status(
          headers_or.status().code(),
          absl::StrCat("\"headers\" ", i, ": ", headers_or.status().message()));
    }
    headers.push_back(
        std::make_unique<Rbac::Permission>(std::move(headers_or.value())));
  }
  return Rbac::Permission::MakeAndPermission(std::move(headers));
}

// Parses an array of path strings into a Permission.
absl::StatusOr<Rbac::Permission> ParsePathsArray(const Json& json) {
  std::vector<std::unique_ptr<Rbac::Permission>> paths;
  for (size_t i = 0; i < json.array().size(); ++i) {
    const Json& child = json.array().at(i);
    if (child.type() != Json::Type::kString) {
      return absl::InvalidArgumentError(
          absl::StrCat("\"paths\" ", i, ": is not a string."));
    }
    auto matcher_or = GetStringMatcher(child.string());
    if (!matcher_or.ok()) {
      return absl::Status(
          matcher_or.status().code(),
          absl::StrCat("\"paths\" ", i, ": ", matcher_or.status().message()));
    }
    paths.push_back(std::make_unique<Rbac::Permission>(
        Rbac::Permission::MakePathPermission(std::move(matcher_or.value()))));
  }
  return Rbac::Permission::MakeOrPermission(std::move(paths));
}

// Parses the "request" object which contains paths and headers permissions.
absl::StatusOr<Rbac::Permission> ParseRequest(const Json& json) {
  std::vector<std::unique_ptr<Rbac::Permission>> request;
  for (const auto& object : json.object()) {
    if (object.first == "paths") {
      if (object.second.type() != Json::Type::kArray) {
        return absl::InvalidArgumentError("\"paths\" is not an array.");
      }
      auto paths_or = ParsePathsArray(object.second);
      if (!paths_or.ok()) return paths_or.status();
      if (!paths_or.value().permissions.empty()) {
        request.push_back(
            std::make_unique<Rbac::Permission>(std::move(paths_or.value())));
      }
    } else if (object.first == "headers") {
      if (object.second.type() != Json::Type::kArray) {
        return absl::InvalidArgumentError("\"headers\" is not an array.");
      }
      auto headers_or = ParseHeadersArray(object.second);
      if (!headers_or.ok()) return headers_or.status();
      if (!headers_or.value().permissions.empty()) {
        request.push_back(
            std::make_unique<Rbac::Permission>(std::move(headers_or.value())));
      }
    } else {
      return absl::InvalidArgumentError(absl::StrFormat(
          "policy contains unknown field \"%s\" in \"request\".",
          object.first));
    }
  }
  if (request.empty()) {
    return Rbac::Permission::MakeAnyPermission();
  }
  return Rbac::Permission::MakeAndPermission(std::move(request));
}

// Parses a single rule (policy) from the JSON input.
// Extracts the policy name, source (principals), and request (permissions).
absl::StatusOr<Rbac::Policy> ParseRule(const Json& json,
                                       std::string* policy_name) {
  std::optional<Rbac::Principal> principals;
  std::optional<Rbac::Permission> permissions;
  for (const auto& object : json.object()) {
    if (object.first == "name") {
      if (object.second.type() != Json::Type::kString) {
        return absl::InvalidArgumentError(
            absl::StrCat("\"name\" is not a string."));
      }
      *policy_name = object.second.string();
    } else if (object.first == "source") {
      if (object.second.type() != Json::Type::kObject) {
        return absl::InvalidArgumentError("\"source\" is not an object.");
      }
      auto peer_or = ParsePeer(object.second);
      if (!peer_or.ok()) return peer_or.status();
      principals = std::move(*peer_or);
    } else if (object.first == "request") {
      if (object.second.type() != Json::Type::kObject) {
        return absl::InvalidArgumentError("\"request\" is not an object.");
      }
      auto request_or = ParseRequest(object.second);
      if (!request_or.ok()) return request_or.status();
      permissions = std::move(*request_or);
    } else {
      return absl::InvalidArgumentError(absl::StrFormat(
          "policy contains unknown field \"%s\" in \"rule\".", object.first));
    }
  }
  if (policy_name->empty()) {
    return absl::InvalidArgumentError(absl::StrCat("\"name\" is not present."));
  }
  if (!principals.has_value()) {
    principals = Rbac::Principal::MakeAnyPrincipal();
  }
  if (!permissions.has_value()) {
    permissions = Rbac::Permission::MakeAnyPermission();
  }
  return Rbac::Policy(std::move(*permissions), std::move(*principals));
}

// Parses an array of rules into a map of policy name to Policy objects.
absl::StatusOr<std::map<std::string, Rbac::Policy>> ParseRulesArray(
    const Json& json) {
  if (json.array().empty()) {
    return absl::InvalidArgumentError("rules is empty.");
  }
  std::map<std::string, Rbac::Policy> policies;
  for (size_t i = 0; i < json.array().size(); ++i) {
    const Json& child = json.array().at(i);
    if (child.type() != Json::Type::kObject) {
      return absl::InvalidArgumentError(
          absl::StrCat("rules ", i, ": is not an object."));
    }
    std::string policy_name;
    auto policy_or = ParseRule(child, &policy_name);
    if (!policy_or.ok()) {
      return absl::Status(
          policy_or.status().code(),
          absl::StrCat("rules ", i, ": ", policy_or.status().message()));
    }
    policies[policy_name] = std::move(policy_or.value());
  }
  return std::move(policies);
}

// Parses an array of deny rules into an Rbac object with deny action.
absl::StatusOr<Rbac> ParseDenyRulesArray(const Json& json,
                                         absl::string_view name) {
  auto policies_or = ParseRulesArray(json);
  if (!policies_or.ok()) return policies_or.status();
  return Rbac(std::string(name), Rbac::Action::kDeny,
              std::move(policies_or.value()));
}

// Parses an array of allow rules into an Rbac object with allow action.
absl::StatusOr<Rbac> ParseAllowRulesArray(const Json& json,
                                          absl::string_view name) {
  auto policies_or = ParseRulesArray(json);
  if (!policies_or.ok()) return policies_or.status();
  return Rbac(std::string(name), Rbac::Action::kAllow,
              std::move(policies_or.value()));
}

// Parses an audit logger configuration from JSON.
absl::StatusOr<std::unique_ptr<experimental::AuditLoggerFactory::Config>>
ParseAuditLogger(const Json& json, size_t pos) {
  if (json.type() != Json::Type::kObject) {
    return absl::InvalidArgumentError(
        absl::StrFormat("\"audit_loggers[%d]\" is not an object.", pos));
  }
  for (const auto& object : json.object()) {
    if (object.first != "name" && object.first != "is_optional" &&
        object.first != "config") {
      return absl::InvalidArgumentError(
          absl::StrFormat("policy contains unknown field \"%s\" in "
                          "\"audit_logging_options.audit_loggers[%d]\".",
                          object.first, pos));
    }
  }
  bool is_optional = false;
  auto it = json.object().find("is_optional");
  if (it != json.object().end()) {
    switch (it->second.type()) {
      case Json::Type::kBoolean:
        is_optional = it->second.boolean();
        break;
      default:
        return absl::InvalidArgumentError(absl::StrFormat(
            "\"audit_loggers[%d].is_optional\" is not a boolean.", pos));
    }
  }
  it = json.object().find("name");
  if (it == json.object().end()) {
    return absl::InvalidArgumentError(
        absl::StrFormat("\"audit_loggers[%d].name\" is required.", pos));
  }
  if (it->second.type() != Json::Type::kString) {
    return absl::InvalidArgumentError(
        absl::StrFormat("\"audit_loggers[%d].name