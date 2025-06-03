Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/lib/security/authorization/rbac_policy.h"

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

// Constructor for Rbac class that initializes name, action, policies, and sets audit_condition to kNone
Rbac::Rbac(std::string name, Rbac::Action action,
           std::map<std::string, Policy> policies)
    : name(std::move(name)),
      action(action),
      policies(std::move(policies)),
      audit_condition(Rbac::AuditCondition::kNone) {}

// Move constructor for Rbac class
Rbac::Rbac(Rbac&& other) noexcept
    : name(std::move(other.name)),
      action(other.action),
      policies(std::move(other.policies)),
      audit_condition(other.audit_condition),
      logger_configs(std::move(other.logger_configs)) {}

// Move assignment operator for Rbac class
Rbac& Rbac::operator=(Rbac&& other) noexcept {
  name = std::move(other.name);
  action = other.action;
  policies = std::move(other.policies);
  audit_condition = other.audit_condition;
  logger_configs = std::move(other.logger_configs);
  return *this;
}

// Converts Rbac object to a human-readable string representation
std::string Rbac::ToString() const {
  std::vector<std::string> contents;
  absl::string_view condition_str;
  switch (audit_condition) {
    case Rbac::AuditCondition::kNone:
      condition_str = "None";
      break;
    case AuditCondition::kOnDeny:
      condition_str = "OnDeny";
      break;
    case AuditCondition::kOnAllow:
      condition_str = "OnAllow";
      break;
    case AuditCondition::kOnDenyAndAllow:
      condition_str = "OnDenyAndAllow";
      break;
  }
  contents.push_back(absl::StrFormat(
      "Rbac name=%s action=%s audit_condition=%s{", name,
      action == Rbac::Action::kAllow ? "Allow" : "Deny", condition_str));
  for (const auto& p : policies) {
    contents.push_back(absl::StrFormat("{\n  policy_name=%s\n%s\n}", p.first,
                                       p.second.ToString()));
  }
  for (const auto& config : logger_configs) {
    contents.push_back(absl::StrFormat("{\n  audit_logger=%s\n%s\n}",
                                       config->name(), config->ToString()));
  }
  contents.push_back("}");
  return absl::StrJoin(contents, "\n");
}

// Constructor for CidrRange with address prefix and prefix length
Rbac::CidrRange::CidrRange(std::string address_prefix, uint32_t prefix_len)
    : address_prefix(std::move(address_prefix)), prefix_len(prefix_len) {}

// Move constructor for CidrRange
Rbac::CidrRange::CidrRange(Rbac::CidrRange&& other) noexcept
    : address_prefix(std::move(other.address_prefix)),
      prefix_len(other.prefix_len) {}

// Move assignment operator for CidrRange
Rbac::CidrRange& Rbac::CidrRange::operator=(Rbac::CidrRange&& other) noexcept {
  address_prefix = std::move(other.address_prefix);
  prefix_len = other.prefix_len;
  return *this;
}

// Converts CidrRange object to string representation
std::string Rbac::CidrRange::ToString() const {
  return absl::StrFormat("CidrRange{address_prefix=%s,prefix_len=%d}",
                         address_prefix, prefix_len);
}

// Creates an AND permission from a vector of permissions
Rbac::Permission Rbac::Permission::MakeAndPermission(
    std::vector<std::unique_ptr<Permission>> permissions) {
  Permission permission;
  permission.type = Permission::RuleType::kAnd;
  permission.permissions = std::move(permissions);
  return permission;
}

// Creates an OR permission from a vector of permissions
Rbac::Permission Rbac::Permission::MakeOrPermission(
    std::vector<std::unique_ptr<Permission>> permissions) {
  Permission permission;
  permission.type = Permission::RuleType::kOr;
  permission.permissions = std::move(permissions);
  return permission;
}

// Creates a NOT permission from another permission
Rbac::Permission Rbac::Permission::MakeNotPermission(Permission permission) {
  Permission not_permission;
  not_permission.type = Permission::RuleType::kNot;
  not_permission.permissions.push_back(
      std::make_unique<Rbac::Permission>(std::move(permission)));
  return not_permission;
}

// Creates an ANY permission (matches any request)
Rbac::Permission Rbac::Permission::MakeAnyPermission() {
  Permission permission;
  permission.type = Permission::RuleType::kAny;
  return permission;
}

// Creates a header-based permission using a header matcher
Rbac::Permission Rbac::Permission::MakeHeaderPermission(
    HeaderMatcher header_matcher) {
  Permission permission;
  permission.type = Permission::RuleType::kHeader;
  permission.header_matcher = std::move(header_matcher);
  return permission;
}

// Creates a path-based permission using a string matcher
Rbac::Permission Rbac::Permission::MakePathPermission(
    StringMatcher string_matcher) {
  Permission permission;
  permission.type = Permission::RuleType::kPath;
  permission.string_matcher = std::move(string_matcher);
  return permission;
}

// Creates a destination IP-based permission using a CIDR range
Rbac::Permission Rbac::Permission::MakeDestIpPermission(CidrRange ip) {
  Permission permission;
  permission.type = Permission::RuleType::kDestIp;
  permission.ip = std::move(ip);
  return permission;
}

// Creates a destination port-based permission
Rbac::Permission Rbac::Permission::MakeDestPortPermission(int port) {
  Permission permission;
  permission.type = Permission::RuleType::kDestPort;
  permission.port = port;
  return permission;
}

// Creates a metadata-based permission with optional inversion
Rbac::Permission Rbac::Permission::MakeMetadataPermission(bool invert) {
  Permission permission;
  permission.type = Permission::RuleType::kMetadata;
  permission.invert = invert;
  return permission;
}

// Creates a requested server name permission using a string matcher
Rbac::Permission Rbac::Permission::MakeReqServerNamePermission(
    StringMatcher string_matcher) {
  Permission permission;
  permission.type = Permission::RuleType::kReqServerName;
  permission.string_matcher = std::move(string_matcher);
  return permission;
}

// Move constructor for Permission
Rbac::Permission::Permission(Rbac::Permission&& other) noexcept
    : type(other.type), invert(other.invert) {
  switch (type) {
    case RuleType::kAnd:
    case RuleType::kOr:
    case RuleType::kNot:
      permissions = std::move(other.permissions);
      break;
    case RuleType::kAny:
      break;
    case RuleType::kHeader:
      header_matcher = std::move(other.header_matcher);
      break;
    case RuleType::kPath:
    case RuleType::kReqServerName:
      string_matcher = std::move(other.string_matcher);
      break;
    case RuleType::kDestIp:
      ip = std::move(other.ip);
      break;
    default:
      port = other.port;
  }
}

// Move assignment operator for Permission
Rbac::Permission& Rbac::Permission::operator=(
    Rbac::Permission&& other) noexcept {
  type = other.type;
  invert = other.invert;
  switch (type) {
    case RuleType::kAnd:
    case RuleType::kOr:
    case RuleType::kNot:
      permissions = std::move(other.permissions);
      break;
    case RuleType::kAny:
      break;
    case RuleType::kHeader:
      header_matcher = std::move(other.header_matcher);
      break;
    case RuleType::kPath:
    case RuleType::kReqServerName:
      string_matcher = std::move(other.string_matcher);
      break;
    case RuleType::kDestIp:
      ip = std::move(other.ip);
      break;
    default:
      port = other.port;
  }
  return *this;
}

// Converts Permission object to string representation
std::string Rbac::Permission::ToString() const {
  switch (type) {
    case RuleType::kAnd: {
      std::vector<std::string> contents;
      contents.reserve(permissions.size());
      for (const auto& permission : permissions) {
        contents.push_back(permission->ToString());
      }
      return absl::StrFormat("and=[%s]", absl::StrJoin(contents, ","));
    }
    case RuleType::kOr: {
      std::vector<std::string> contents;
      contents.reserve(permissions.size());
      for (const auto& permission : permissions) {
        contents.push_back(permission->ToString());
      }
      return absl::StrFormat("or=[%s]", absl::StrJoin(contents, ","));
    }
    case RuleType::kNot:
      return absl::StrFormat("not %s", permissions[0]->ToString());
    case RuleType::kAny:
      return "any";
    case RuleType::kHeader:
      return absl::StrFormat("header=%s", header_matcher.ToString());
    case RuleType::kPath:
      return absl::StrFormat("path=%s", string_matcher.ToString());
    case RuleType::kDestIp:
      return absl::StrFormat("dest_ip=%s", ip.ToString());
    case RuleType::kDestPort:
      return absl::StrFormat("dest_port=%d", port);
    case RuleType::kMetadata:
      return absl::StrFormat("%smetadata", invert ? "invert " : "");
    case RuleType::kReqServerName:
      return absl::StrFormat("requested_server_name=%s",
                             string_matcher.ToString());
    default:
      return "";
  }
}

// Creates an AND principal from a vector of principals
Rbac::Principal Rbac::Principal::MakeAndPrincipal(
    std::vector<std::unique_ptr<Principal>> principals) {
  Principal principal;
  principal.type = Principal::RuleType::kAnd;
  principal.principals = std::move(principals);
  return principal;
}

// Creates an OR principal from a vector of principals
Rbac::Principal Rbac::Principal::MakeOrPrincipal(
    std::vector<std::unique_ptr<Principal>> principals) {
  Principal principal;
  principal.type = Principal::RuleType::kOr;
  principal.principals = std::move(principals);
  return principal;
}

// Creates a NOT principal from another principal
Rbac::Principal Rbac::Principal::MakeNotPrincipal(Principal principal) {
  Principal not_principal;
  not_principal.type = Principal::RuleType::kNot;
  not_principal.principals.push_back(
      std::make_unique<Rbac::Principal>(std::move(principal)));
  return not_principal;
}

// Creates an ANY principal (matches any principal)
Rbac::Principal Rbac::Principal::MakeAnyPrincipal() {
  Principal principal;
  principal.type = Principal::RuleType::kAny;
  return principal;
}

// Creates an authenticated principal with optional string matcher
Rbac::Principal Rbac::Principal::MakeAuthenticatedPrincipal(
    std::optional<StringMatcher> string_matcher) {
  Principal principal;
  principal.type = Principal::RuleType::kPrincipalName;
  principal.string_matcher = std::move(string_matcher);
  return principal;
}

// Creates a source IP principal using a CIDR range
Rbac::Principal Rbac::Principal::MakeSourceIpPrincipal(CidrRange ip) {
  Principal principal;
  principal.type = Principal::RuleType::kSourceIp;
  principal.ip = std::move(ip);
  return principal;
}

// Creates a direct remote IP principal using a CIDR range
Rbac::Principal Rbac::Principal::MakeDirectRemoteIpPrincipal(CidrRange ip) {
  Principal principal;
  principal.type = Principal::RuleType::kDirectRemoteIp;
  principal.ip = std::move(ip);
  return principal;
}

// Creates a remote IP principal using a CIDR range
Rbac::Principal Rbac::Principal::MakeRemoteIpPrincipal(CidrRange ip) {
  Principal principal;
  principal.type = Principal::RuleType::kRemoteIp;
  principal.ip = std::move(ip);
  return principal;
}

// Creates a header-based principal using a header matcher
Rbac::Principal Rbac::Principal::MakeHeaderPrincipal(
    HeaderMatcher header_matcher) {
  Principal principal;
  principal.type = Principal::RuleType::kHeader;
  principal.header_matcher = std::move(header_matcher);
  return principal;
}

// Creates a path-based principal using a string matcher
Rbac::Principal Rbac::Principal::MakePathPrincipal(
    StringMatcher string_matcher) {
  Principal principal;
  principal.type = Principal::RuleType::kPath;
  principal.string_matcher = std::move(string_matcher);
  return principal;
}

// Creates a metadata-based principal with optional inversion
Rbac::Principal Rbac::Principal::MakeMetadataPrincipal(bool invert) {
  Principal principal;
  principal.type = Principal::RuleType::kMetadata;
  principal.invert = invert;
  return principal;
}

// Move constructor for Principal
Rbac::Principal::Principal(Rbac::Principal&& other) noexcept
    : type(other.type), invert(other.invert) {
  switch (type) {
    case RuleType::kAnd:
    case RuleType::kOr:
    case RuleType::kNot:
      principals = std::move(other.principals);
      break;
    case RuleType::kAny:
      break;
    case RuleType::kHeader:
      header_matcher = std::move(other.header_matcher);
      break;
    case RuleType::kPrincipalName:
    case RuleType::kPath:
      string_matcher = std::move(other.string_matcher);
      break;
    default:
      ip = std::move(other.ip);
  }
}

// Move assignment operator for Principal
Rbac::Principal& Rbac::Principal::operator=(Rbac::Principal&& other) noexcept {
  type = other.type;
  invert = other.invert;
  switch (type) {
    case RuleType::kAnd:
    case RuleType::kOr:
    case RuleType::kNot:
      principals = std::move(other.principals);
      break;
    case RuleType::kAny:
      break;
    case RuleType::kHeader:
      header_matcher = std::move(other.header_matcher);
      break;
    case RuleType::kPrincipalName:
    case RuleType::kPath:
      string_matcher = std::move(other.string_matcher);
      break;
    default:
      ip = std::move(other.ip);
  }
  return *this;
}

// Converts Principal object to string representation
std::string Rbac::Principal::ToString() const {
  switch (type) {
    case RuleType::kAnd: {
      std::vector<std::string> contents;
      contents.reserve(principals.size());
      for (const auto& principal : principals) {
        contents.push_back(principal->ToString());
      }
      return absl::StrFormat("and=[%s]", absl::StrJoin(contents, ","));
    }
    case RuleType::kOr: {
      std::vector<std::string> contents;
      contents.reserve(principals.size());
      for (const auto& principal : principals) {
        contents.push_back(principal->ToString());
      }
      return absl::StrFormat("or=[%s]", absl::StrJoin(contents, ","));
    }
    case RuleType::kNot:
      return absl::StrFormat("not %s", principals[0]->ToString());
    case RuleType::kAny:
      return "any";
    case RuleType::kPrincipalName:
      return absl::StrFormat("principal_name=%s", string_matcher->ToString());
    case RuleType::kSourceIp:
      return absl::StrFormat("source_ip=%s", ip.ToString());
    case RuleType::kDirectRemoteIp:
      return absl::StrFormat("direct_remote_ip=%s", ip.ToString());
    case RuleType::kRemoteIp:
      return absl::StrFormat("remote_ip=%s", ip.ToString());
    case RuleType::kHeader:
      return absl::StrFormat("header=%s", header_matcher.ToString());
    case RuleType::kPath:
      return absl::StrFormat("path=%s", string_matcher->ToString());
    case RuleType::kMetadata:
      return absl::StrFormat("%smetadata", invert ? "invert " : "");
    default:
      return "";
  }
}

// Constructor for Policy that takes permissions and principals
Rbac::Policy::Policy(Permission permissions, Principal principals)
    : permissions(std::move(permissions)), principals(std::move(principals)) {}

// Move constructor for Policy
Rbac::Policy::Policy(Rbac::Policy&& other) noexcept
    : permissions(std::move(other.permissions)),
      principals(std::move(other.principals)) {}

// Move assignment operator for Policy
Rbac::Policy& Rbac::Policy::operator=(Rbac::Policy&& other) noexcept {
  permissions = std::move(other.permissions);
  principals = std::move(other.principals);
  return *this;
}

// Converts Policy object to string representation
std::string Rbac::Policy::ToString() const {
  return absl::StrFormat(
      "  Policy  {\n    Permissions{%s}\n    Principals{%s}\n  }",
      permissions.ToString(), principals.ToString());
}

}
```