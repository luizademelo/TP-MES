Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_RBAC_POLICY_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_RBAC_POLICY_H

#include <grpc/grpc_audit_logging.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "src/core/util/matchers.h"

namespace grpc_core {

// Role-Based Access Control (RBAC) policy definition.
// This struct defines the structure for RBAC policies used in authorization.
struct Rbac {
  // Possible actions for the RBAC policy.
  enum class Action {
    kAllow,  // Allow the request if conditions are met
    kDeny,   // Deny the request if conditions are met
  };

  // Conditions for audit logging of RBAC decisions.
  enum class AuditCondition {
    kNone,             // No audit logging
    kOnDeny,           // Audit only denied requests
    kOnAllow,          // Audit only allowed requests
    kOnDenyAndAllow,   // Audit both denied and allowed requests
  };

  // Represents a CIDR range for IP address matching.
  struct CidrRange {
    CidrRange() = default;
    // Constructs a CIDR range with specified address prefix and prefix length.
    CidrRange(std::string address_prefix, uint32_t prefix_len);

    CidrRange(CidrRange&& other) noexcept;
    CidrRange& operator=(CidrRange&& other) noexcept;

    // Returns a string representation of the CIDR range.
    std::string ToString() const;

    std::string address_prefix;  // IP address prefix (e.g., "192.168.1.0")
    uint32_t prefix_len;         // Prefix length (e.g., 24 for /24)
  };

  // Defines permission rules for RBAC policies.
  struct Permission {
    // Types of permission rules.
    enum class RuleType {
      kAnd,             // Logical AND of multiple permissions
      kOr,              // Logical OR of multiple permissions
      kNot,             // Logical NOT of a permission
      kAny,             // Matches any request
      kHeader,          // Matches based on header
      kPath,            // Matches based on path
      kDestIp,          // Matches based on destination IP
      kDestPort,        // Matches based on destination port
      kMetadata,        // Matches based on metadata
      kReqServerName,   // Matches based on requested server name
    };

    // Factory methods for creating different types of permissions:
    static Permission MakeAndPermission(
        std::vector<std::unique_ptr<Permission>> permissions);
    static Permission MakeOrPermission(
        std::vector<std::unique_ptr<Permission>> permissions);
    static Permission MakeNotPermission(Permission permission);
    static Permission MakeAnyPermission();
    static Permission MakeHeaderPermission(HeaderMatcher header_matcher);
    static Permission MakePathPermission(StringMatcher string_matcher);
    static Permission MakeDestIpPermission(CidrRange ip);
    static Permission MakeDestPortPermission(int port);
    static Permission MakeMetadataPermission(bool invert);
    static Permission MakeReqServerNamePermission(StringMatcher string_matcher);

    Permission() = default;

    Permission(Permission&& other) noexcept;
    Permission& operator=(Permission&& other) noexcept;

    // Returns a string representation of the permission.
    std::string ToString() const;

    RuleType type = RuleType::kAnd;  // Type of this permission rule
    HeaderMatcher header_matcher;    // For header-based permissions
    StringMatcher string_matcher;    // For string-based permissions
    CidrRange ip;                   // For IP-based permissions
    int port;                       // For port-based permissions

    // List of child permissions (used for AND/OR/NOT rules)
    std::vector<std::unique_ptr<Permission>> permissions;

    bool invert = false;  // Whether to invert the match result
  };

  // Defines principal rules for RBAC policies.
  struct Principal {
    // Types of principal rules.
    enum class RuleType {
      kAnd,             // Logical AND of multiple principals
      kOr,              // Logical OR of multiple principals
      kNot,             // Logical NOT of a principal
      kAny,             // Matches any principal
      kPrincipalName,   // Matches based on principal name
      kSourceIp,        // Matches based on source IP
      kDirectRemoteIp,  // Matches based on direct remote IP
      kRemoteIp,        // Matches based on remote IP
      kHeader,          // Matches based on header
      kPath,            // Matches based on path
      kMetadata,        // Matches based on metadata
    };

    // Factory methods for creating different types of principals:
    static Principal MakeAndPrincipal(
        std::vector<std::unique_ptr<Principal>> principals);
    static Principal MakeOrPrincipal(
        std::vector<std::unique_ptr<Principal>> principals);
    static Principal MakeNotPrincipal(Principal principal);
    static Principal MakeAnyPrincipal();
    static Principal MakeAuthenticatedPrincipal(
        std::optional<StringMatcher> string_matcher);
    static Principal MakeSourceIpPrincipal(CidrRange ip);
    static Principal MakeDirectRemoteIpPrincipal(CidrRange ip);
    static Principal MakeRemoteIpPrincipal(CidrRange ip);
    static Principal MakeHeaderPrincipal(HeaderMatcher header_matcher);
    static Principal MakePathPrincipal(StringMatcher string_matcher);
    static Principal MakeMetadataPrincipal(bool invert);

    Principal() = default;

    Principal(Principal&& other) noexcept;
    Principal& operator=(Principal&& other) noexcept;

    // Returns a string representation of the principal.
    std::string ToString() const;

    RuleType type = RuleType::kAnd;  // Type of this principal rule
    HeaderMatcher header_matcher;    // For header-based principals
    std::optional<StringMatcher> string_matcher;  // For string-based principals
    CidrRange ip;                   // For IP-based principals

    // List of child principals (used for AND/OR/NOT rules)
    std::vector<std::unique_ptr<Principal>> principals;

    bool invert = false;  // Whether to invert the match result
  };

  // Combines permissions and principals into a complete policy.
  struct Policy {
    Policy() = default;
    // Constructs a policy with specified permissions and principals.
    Policy(Permission permissions, Principal principals);

    Policy(Policy&& other) noexcept;
    Policy& operator=(Policy&& other) noexcept;

    // Returns a string representation of the policy.
    std::string ToString() const;

    Permission permissions;  // What actions are allowed/denied
    Principal principals;    // Who the policy applies to
  };

  Rbac() = default;
  // Constructs an RBAC policy with name, action, and policies.
  Rbac(std::string name, Rbac::Action action,
       std::map<std::string, Policy> policies);

  Rbac(Rbac&& other) noexcept;
  Rbac& operator=(Rbac&& other) noexcept;

  // Returns a string representation of the RBAC policy.
  std::string ToString() const;

  std::string name;  // Name of the RBAC policy

  Action action;  // Whether to allow or deny matching requests
  std::map<std::string, Policy> policies;  // Map of named policies

  AuditCondition audit_condition;  // When to audit this policy's decisions
  std::vector<std::unique_ptr<experimental::AuditLoggerFactory::Config>>
      logger_configs;  // Configuration for audit loggers
};

}  // namespace grpc_core

#endif
```