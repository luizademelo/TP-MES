Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/lib/security/authorization/matchers.h"

#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <string>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"

namespace grpc_core {

// Creates an AuthorizationMatcher based on the given permission rule.
// Handles all permission types defined in Rbac::Permission::RuleType.
std::unique_ptr<AuthorizationMatcher> AuthorizationMatcher::Create(
    Rbac::Permission permission) {
  switch (permission.type) {
    case Rbac::Permission::RuleType::kAnd: {
      // For AND rules, create matchers for all sub-permissions and combine them
      std::vector<std::unique_ptr<AuthorizationMatcher>> matchers;
      matchers.reserve(permission.permissions.size());
      for (const auto& rule : permission.permissions) {
        matchers.push_back(AuthorizationMatcher::Create(std::move(*rule)));
      }
      return std::make_unique<AndAuthorizationMatcher>(std::move(matchers));
    }
    case Rbac::Permission::RuleType::kOr: {
      // For OR rules, create matchers for all sub-permissions and combine them
      std::vector<std::unique_ptr<AuthorizationMatcher>> matchers;
      matchers.reserve(permission.permissions.size());
      for (const auto& rule : permission.permissions) {
        matchers.push_back(AuthorizationMatcher::Create(std::move(*rule)));
      }
      return std::make_unique<OrAuthorizationMatcher>(std::move(matchers));
    }
    case Rbac::Permission::RuleType::kNot:
      // For NOT rules, create a matcher that inverts the result of the sub-permission
      return std::make_unique<NotAuthorizationMatcher>(
          AuthorizationMatcher::Create(std::move(*permission.permissions[0])));
    case Rbac::Permission::RuleType::kAny:
      // For ANY rules, create a matcher that always matches
      return std::make_unique<AlwaysAuthorizationMatcher>();
    case Rbac::Permission::RuleType::kHeader:
      // For HEADER rules, create a header matcher
      return std::make_unique<HeaderAuthorizationMatcher>(
          std::move(permission.header_matcher));
    case Rbac::Permission::RuleType::kPath:
      // For PATH rules, create a path matcher
      return std::make_unique<PathAuthorizationMatcher>(
          std::move(permission.string_matcher));
    case Rbac::Permission::RuleType::kDestIp:
      // For DEST_IP rules, create an IP matcher for destination IP
      return std::make_unique<IpAuthorizationMatcher>(
          IpAuthorizationMatcher::Type::kDestIp, std::move(permission.ip));
    case Rbac::Permission::RuleType::kDestPort:
      // For DEST_PORT rules, create a port matcher
      return std::make_unique<PortAuthorizationMatcher>(permission.port);
    case Rbac::Permission::RuleType::kMetadata:
      // For METADATA rules, create a metadata matcher
      return std::make_unique<MetadataAuthorizationMatcher>(permission.invert);
    case Rbac::Permission::RuleType::kReqServerName:
      // For REQ_SERVER_NAME rules, create a server name matcher
      return std::make_unique<ReqServerNameAuthorizationMatcher>(
          std::move(permission.string_matcher));
  }
  return nullptr;
}

// Creates an AuthorizationMatcher based on the given principal rule.
// Handles all principal types defined in Rbac::Principal::RuleType.
std::unique_ptr<AuthorizationMatcher> AuthorizationMatcher::Create(
    Rbac::Principal principal) {
  switch (principal.type) {
    case Rbac::Principal::RuleType::kAnd: {
      // For AND rules, create matchers for all sub-principals and combine them
      std::vector<std::unique_ptr<AuthorizationMatcher>> matchers;
      matchers.reserve(principal.principals.size());
      for (const auto& id : principal.principals) {
        matchers.push_back(AuthorizationMatcher::Create(std::move(*id)));
      }
      return std::make_unique<AndAuthorizationMatcher>(std::move(matchers));
    }
    case Rbac::Principal::RuleType::kOr: {
      // For OR rules, create matchers for all sub-principals and combine them
      std::vector<std::unique_ptr<AuthorizationMatcher>> matchers;
      matchers.reserve(principal.principals.size());
      for (const auto& id : principal.principals) {
        matchers.push_back(AuthorizationMatcher::Create(std::move(*id)));
      }
      return std::make_unique<OrAuthorizationMatcher>(std::move(matchers));
    }
    case Rbac::Principal::RuleType::kNot:
      // For NOT rules, create a matcher that inverts the result of the sub-principal
      return std::make_unique<NotAuthorizationMatcher>(
          AuthorizationMatcher::Create(std::move(*principal.principals[0])));
    case Rbac::Principal::RuleType::kAny:
      // For ANY rules, create a matcher that always matches
      return std::make_unique<AlwaysAuthorizationMatcher>();
    case Rbac::Principal::RuleType::kPrincipalName:
      // For PRINCIPAL_NAME rules, create an authenticated principal matcher
      return std::make_unique<AuthenticatedAuthorizationMatcher>(
          std::move(principal.string_matcher));
    case Rbac::Principal::RuleType::kSourceIp:
      // For SOURCE_IP rules, create an IP matcher for source IP
      return std::make_unique<IpAuthorizationMatcher>(
          IpAuthorizationMatcher::Type::kSourceIp, std::move(principal.ip));
    case Rbac::Principal::RuleType::kDirectRemoteIp:
      // For DIRECT_REMOTE_IP rules, create an IP matcher for direct remote IP
      return std::make_unique<IpAuthorizationMatcher>(
          IpAuthorizationMatcher::Type::kDirectRemoteIp,
          std::move(principal.ip));
    case Rbac::Principal::RuleType::kRemoteIp:
      // For REMOTE_IP rules, create an IP matcher for remote IP
      return std::make_unique<IpAuthorizationMatcher>(
          IpAuthorizationMatcher::Type::kRemoteIp, std::move(principal.ip));
    case Rbac::Principal::RuleType::kHeader:
      // For HEADER rules, create a header matcher
      return std::make_unique<HeaderAuthorizationMatcher>(
          std::move(principal.header_matcher));
    case Rbac::Principal::RuleType::kPath:
      // For PATH rules, create a path matcher
      return std::make_unique<PathAuthorizationMatcher>(
          std::move(principal.string_matcher.value()));
    case Rbac::Principal::RuleType::kMetadata:
      // For METADATA rules, create a metadata matcher
      return std::make_unique<MetadataAuthorizationMatcher>(principal.invert);
  }
  return nullptr;
}

// Implementation of AND matcher - returns true only if all sub-matchers match
bool AndAuthorizationMatcher::Matches(const EvaluateArgs& args) const {
  for (const auto& matcher : matchers_) {
    if (!matcher->Matches(args)) {
      return false;
    }
  }
  return true;
}

// Implementation of OR matcher - returns true if any sub-matcher matches
bool OrAuthorizationMatcher::Matches(const EvaluateArgs& args) const {
  for (const auto& matcher : matchers_) {
    if (matcher->Matches(args)) {
      return true;
    }
  }
  return false;
}

// Implementation of NOT matcher - returns inverse of the sub-matcher's result
bool NotAuthorizationMatcher::Matches(const EvaluateArgs& args) const {
  return !matcher_->Matches(args);
}

// Implementation of header matcher - checks if header matches the pattern
bool HeaderAuthorizationMatcher::Matches(const EvaluateArgs& args) const {
  std::string concatenated_value;
  return matcher_.Match(
      args.GetHeaderValue(matcher_.name(), &concatenated_value));
}

// Constructor for IP matcher - converts CIDR range to subnet address
IpAuthorizationMatcher::IpAuthorizationMatcher(Type type, Rbac::CidrRange range)
    : type_(type), prefix_len_(range.prefix_len) {
  auto address =
      StringToSockaddr(range.address_prefix, 0);
  if (!address.ok()) {
    VLOG(2) << "CidrRange address \"" << range.address_prefix
            << "\" is not IPv4/IPv6. Error: " << address.status();
    memset(&subnet_address_, 0, sizeof(subnet_address_));
    return;
  }
  subnet_address_ = *address;
  grpc_sockaddr_mask_bits(&subnet_address_, prefix_len_);
}

// Implementation of IP matcher - checks if peer/local IP matches the subnet
bool IpAuthorizationMatcher::Matches(const EvaluateArgs& args) const {
  grpc_resolved_address address;
  switch (type_) {
    case Type::kDestIp: {
      address = args.GetLocalAddress();
      break;
    }
    case Type::kSourceIp:
    case Type::kDirectRemoteIp:
    case Type::kRemoteIp: {
      address = args.GetPeerAddress();
      break;
    }
    default:
      return false;
  }
  return grpc_sockaddr_match_subnet(&address, &subnet_address_, prefix_len_);
}

// Implementation of port matcher - checks if port matches
bool PortAuthorizationMatcher::Matches(const EvaluateArgs& args) const {
  return port_ == args.GetLocalPort();
}

// Implementation of authenticated principal matcher
// Checks if peer is authenticated and matches the principal name pattern
bool AuthenticatedAuthorizationMatcher::Matches(
    const EvaluateArgs& args) const {
  // Only SSL/TLS connections are considered authenticated
  if (args.GetTransportSecurityType() != GRPC_SSL_TRANSPORT_SECURITY_TYPE &&
      args.GetTransportSecurityType() != GRPC_TLS_TRANSPORT_SECURITY_TYPE) {
    return false;
  }
  // If no specific principal name is required, any authenticated peer matches
  if (!matcher_.has_value()) {
    return true;
  }
  // Check URI SANs (Subject Alternative Names)
  std::vector<absl::string_view> uri_sans = args.GetUriSans();
  if (!uri_sans.empty()) {
    for (const auto& uri : uri_sans) {
      if (matcher_->Match(uri)) {
        return true;
      }
    }
  }
  // Check DNS SANs (Subject Alternative Names)
  std::vector<absl::string_view> dns_sans = args.GetDnsSans();
  if (!dns_sans.empty()) {
    for (const auto& dns : dns_sans) {
      if (matcher_->Match(dns)) {
        return true;
      }
    }
  }
  // Check the subject name
  return matcher_->Match(args.GetSubject());
}

// Implementation of server name matcher - currently matches empty string
bool ReqServerNameAuthorizationMatcher::Matches(const EvaluateArgs&) const {
  // TODO: Implement proper server name matching
  return matcher_.Match("");
}

// Implementation of path matcher - checks if request path matches the pattern
bool PathAuthorizationMatcher::Matches(const EvaluateArgs& args) const {
  absl::string_view path = args.GetPath();
  if (!path.empty()) {
    return matcher_.Match(path);
  }
  return false;
}

// Implementation of policy matcher - checks both permissions and principals
bool PolicyAuthorizationMatcher::Matches(const EvaluateArgs& args) const {
  return permissions_->Matches(args) && principals_->Matches(args);
}

}  // namespace grpc_core
```