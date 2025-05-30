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

struct Rbac {
  enum class Action {
    kAllow,
    kDeny,
  };

  enum class AuditCondition {
    kNone,
    kOnDeny,
    kOnAllow,
    kOnDenyAndAllow,
  };

  struct CidrRange {
    CidrRange() = default;
    CidrRange(std::string address_prefix, uint32_t prefix_len);

    CidrRange(CidrRange&& other) noexcept;
    CidrRange& operator=(CidrRange&& other) noexcept;

    std::string ToString() const;

    std::string address_prefix;
    uint32_t prefix_len;
  };

  struct Permission {
    enum class RuleType {
      kAnd,
      kOr,
      kNot,
      kAny,
      kHeader,
      kPath,
      kDestIp,
      kDestPort,
      kMetadata,
      kReqServerName,
    };

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

    std::string ToString() const;

    RuleType type = RuleType::kAnd;
    HeaderMatcher header_matcher;
    StringMatcher string_matcher;
    CidrRange ip;
    int port;

    std::vector<std::unique_ptr<Permission>> permissions;

    bool invert = false;
  };

  struct Principal {
    enum class RuleType {
      kAnd,
      kOr,
      kNot,
      kAny,
      kPrincipalName,
      kSourceIp,
      kDirectRemoteIp,
      kRemoteIp,
      kHeader,
      kPath,
      kMetadata,
    };

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

    std::string ToString() const;

    RuleType type = RuleType::kAnd;
    HeaderMatcher header_matcher;
    std::optional<StringMatcher> string_matcher;
    CidrRange ip;

    std::vector<std::unique_ptr<Principal>> principals;

    bool invert = false;
  };

  struct Policy {
    Policy() = default;
    Policy(Permission permissions, Principal principals);

    Policy(Policy&& other) noexcept;
    Policy& operator=(Policy&& other) noexcept;

    std::string ToString() const;

    Permission permissions;
    Principal principals;
  };

  Rbac() = default;
  Rbac(std::string name, Rbac::Action action,
       std::map<std::string, Policy> policies);

  Rbac(Rbac&& other) noexcept;
  Rbac& operator=(Rbac&& other) noexcept;

  std::string ToString() const;

  std::string name;

  Action action;
  std::map<std::string, Policy> policies;

  AuditCondition audit_condition;
  std::vector<std::unique_ptr<experimental::AuditLoggerFactory::Config>>
      logger_configs;
};

}

#endif
