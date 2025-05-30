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

class AuthorizationMatcher {
 public:
  virtual ~AuthorizationMatcher() = default;

  virtual bool Matches(const EvaluateArgs& args) const = 0;

  static std::unique_ptr<AuthorizationMatcher> Create(
      Rbac::Permission permission);

  static std::unique_ptr<AuthorizationMatcher> Create(
      Rbac::Principal principal);
};

class AlwaysAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit AlwaysAuthorizationMatcher() = default;

  bool Matches(const EvaluateArgs&) const override { return true; }
};

class AndAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit AndAuthorizationMatcher(
      std::vector<std::unique_ptr<AuthorizationMatcher>> matchers)
      : matchers_(std::move(matchers)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  std::vector<std::unique_ptr<AuthorizationMatcher>> matchers_;
};

class OrAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit OrAuthorizationMatcher(
      std::vector<std::unique_ptr<AuthorizationMatcher>> matchers)
      : matchers_(std::move(matchers)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  std::vector<std::unique_ptr<AuthorizationMatcher>> matchers_;
};

class NotAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit NotAuthorizationMatcher(
      std::unique_ptr<AuthorizationMatcher> matcher)
      : matcher_(std::move(matcher)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  std::unique_ptr<AuthorizationMatcher> matcher_;
};

class MetadataAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit MetadataAuthorizationMatcher(bool invert) : invert_(invert) {}

  bool Matches(const EvaluateArgs&) const override { return invert_; }

 private:
  const bool invert_;
};

class HeaderAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit HeaderAuthorizationMatcher(HeaderMatcher matcher)
      : matcher_(std::move(matcher)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  const HeaderMatcher matcher_;
};

class IpAuthorizationMatcher : public AuthorizationMatcher {
 public:
  enum class Type {
    kDestIp,
    kSourceIp,
    kDirectRemoteIp,
    kRemoteIp,
  };

  IpAuthorizationMatcher(Type type, Rbac::CidrRange range);

  bool Matches(const EvaluateArgs& args) const override;

 private:
  const Type type_;

  grpc_resolved_address subnet_address_;
  const uint32_t prefix_len_;
};

class PortAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit PortAuthorizationMatcher(int port) : port_(port) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  const int port_;
};

class AuthenticatedAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit AuthenticatedAuthorizationMatcher(std::optional<StringMatcher> auth)
      : matcher_(std::move(auth)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  const std::optional<StringMatcher> matcher_;
};

class ReqServerNameAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit ReqServerNameAuthorizationMatcher(
      StringMatcher requested_server_name)
      : matcher_(std::move(requested_server_name)) {}

  bool Matches(const EvaluateArgs&) const override;

 private:
  const StringMatcher matcher_;
};

class PathAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit PathAuthorizationMatcher(StringMatcher path)
      : matcher_(std::move(path)) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  const StringMatcher matcher_;
};

class PolicyAuthorizationMatcher : public AuthorizationMatcher {
 public:
  explicit PolicyAuthorizationMatcher(Rbac::Policy policy)
      : permissions_(
            AuthorizationMatcher::Create(std::move(policy.permissions))),
        principals_(
            AuthorizationMatcher::Create(std::move(policy.principals))) {}

  bool Matches(const EvaluateArgs& args) const override;

 private:
  std::unique_ptr<AuthorizationMatcher> permissions_;
  std::unique_ptr<AuthorizationMatcher> principals_;
};

}

#endif
