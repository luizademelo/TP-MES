Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MATCHERS_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MATCHERS_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/security/authorization/evaluate_args.h"
#include "src/core/lib/security/authorization/rbac_policy.h"
#include "src/core/util/matchers.h"

namespace grpc_core {

// Abstract base class for authorization matchers.
// Defines interface for evaluating whether a request matches authorization rules.
class AuthorizationMatcher {
 public:
  virtual ~AuthorizationMatcher() = default;

  // Evaluates whether the given arguments match the authorization rules.
  virtual bool Matches(const EvaluateArgs& args) const = 0;

  // Factory methods to create matchers from RBAC permissions or principals.
  static std::unique_ptr<AuthorizationMatcher> Create(
      Rbac::Permission permission);

  static std::unique_ptr<AuthorizationMatcher> Create(
      Rbac::Principal principal);
};

// Matcher that always returns true (allows all requests).
class AlwaysAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit AlwaysAuthorizationMatcher() = default;

  bool Matches(const EvaluateArgs&) const override { return true; }
};

// Logical AND matcher that combines multiple matchers.
// Returns true only if all child matchers match.
class AndAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit AndAuthorizationMatcher(
      std::vector<std::unique_ptr<AuthorizationMatcher>> matchers)
      : matchers_(std::move(matchers)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  std::vector<std::unique_ptr<AuthorizationMatcher>> matchers_;
};

// Logical OR matcher that combines multiple matchers.
// Returns true if any of the child matchers match.
class OrAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit OrAuthorizationMatcher(
      std::vector<std::unique_ptr<AuthorizationMatcher>> matchers)
      : matchers_(std::move(matchers)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  std::vector<std::unique_ptr<AuthorizationMatcher>> matchers_;
};

// Logical NOT matcher that inverts the result of its child matcher.
class NotAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit NotAuthorizationMatcher(
      std::unique_ptr<AuthorizationMatcher> matcher)
      : matcher_(std::move(matcher)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  std::unique_ptr<AuthorizationMatcher> matcher_;
};

// Matcher for metadata that simply returns its inverted flag.
// Primarily used as a base for more complex metadata matchers.
class MetadataAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit MetadataAuthorizationMatcher(bool invert) : invert_(invert) {}

  bool Matches(const EvaluateArgs&) const override { return invert_; }

 private:
  const bool invert_;
};

// Matcher for evaluating request headers against a header pattern.
class HeaderAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit HeaderAuthorizationMatcher(HeaderMatcher matcher)
      : matcher_(std::move(matcher)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  const HeaderMatcher matcher_;
};

// Matcher for evaluating IP addresses against CIDR ranges.
// Can match different types of IPs (source, destination, remote, etc.)
class IpAuthorizationMatcher : public AuthorizationMatcher {
 public:
  enum class Type {
    kDestIp,          // Destination IP
    kSourceIp,        // Source IP
    kDirectRemoteIp,  // Direct remote IP
    kRemoteIp,        // Remote IP (potentially through proxies)
  };

  IpAuthorizationMatcher(Type type, Rbac::CidrRange range);

  bool Matches(const EvaluateArgs& args) const override;

 private:
  const Type type_;                // Which IP to check
  grpc_resolved_address subnet_address_;  // Subnet address to match against
  const uint32_t prefix_len_;      // CIDR prefix length
};

// Matcher for evaluating port numbers.
class PortAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit PortAuthorizationMatcher(int port) : port_(port) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  const int port_;  // Port number to match against
};

// Matcher for evaluating authentication information.
class AuthenticatedAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit AuthenticatedAuthorizationMatcher(std::optional<StringMatcher> auth)
      : matcher_(std::move(auth)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  const std::optional<StringMatcher> matcher_;  // Optional pattern for auth info
};

// Matcher for evaluating requested server names.
class ReqServerNameAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit ReqServerNameAuthorizationMatcher(
      StringMatcher requested_server_name)
      : matcher_(std::move(requested_server_name)) {}

  bool Matches(const EvaluateArgs&) const override;

 private:
  const StringMatcher matcher_;  // Pattern for server name matching
};

// Matcher for evaluating request paths.
class PathAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit PathAuthorizationMatcher(StringMatcher path)
      : matcher_(std::move(path)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  const StringMatcher matcher_;  // Pattern for path matching
};

// Matcher that combines permission and principal rules from an RBAC policy.
class PolicyAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit PolicyAuthorizationMatcher(Rbac::Policy policy)
      : permissions_(
            AuthorizationMatcher::Create(std::move(policy.permissions))),
        principals_(
            AuthorizationMatcher::Create(std::move(policy.principals))) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  std::unique_ptr<AuthorizationMatcher> permissions_;  // Permission rules
  std::unique_ptr<AuthorizationMatcher> principals_;  // Principal rules
};

}  // namespace grpc_core

#endif
```

The comments I've added:
1. Explain the purpose of each class and its role in authorization
2. Describe the logical operations (AND, OR, NOT) for composite matchers
3. Clarify the different IP address types that can be matched
4. Note the purpose of each matcher's fields
5. Provide context for how the matchers are used in the authorization system
6. Explain the factory methods in the base class
7. Document the simple matchers that serve as building blocks

The comments are designed to help future developers understand:
- What each matcher does
- How the matchers relate to each other
- The expected behavior of each matcher
- The purpose of each class member
- The overall architecture of the authorization system