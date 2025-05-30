// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_GRPC_AUTHORIZATION_ENGINE_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_GRPC_AUTHORIZATION_ENGINE_H

#include <grpc/grpc_audit_logging.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <memory>
#include <string>
#include <vector>

#include "src/core/lib/security/authorization/authorization_engine.h"
#include "src/core/lib/security/authorization/evaluate_args.h"
#include "src/core/lib/security/authorization/matchers.h"
#include "src/core/lib/security/authorization/rbac_policy.h"

namespace grpc_core {

using experimental::AuditLogger;

class GrpcAuthorizationEngine : public AuthorizationEngine {
 public:

  explicit GrpcAuthorizationEngine(Rbac::Action action)
      : action_(action), audit_condition_(Rbac::AuditCondition::kNone) {}

  explicit GrpcAuthorizationEngine(Rbac policy);

  GrpcAuthorizationEngine(GrpcAuthorizationEngine&& other) noexcept;
  GrpcAuthorizationEngine& operator=(GrpcAuthorizationEngine&& other) noexcept;

  Rbac::Action action() const { return action_; }

  size_t num_policies() const { return policies_.size(); }

  Rbac::AuditCondition audit_condition() const { return audit_condition_; }

  const std::vector<std::unique_ptr<AuditLogger>>& audit_loggers() const {
    return audit_loggers_;
  }

  Decision Evaluate(const EvaluateArgs& args) const override;

 private:
  struct Policy {
    std::string name;
    std::unique_ptr<AuthorizationMatcher> matcher;
  };

  std::string name_;
  Rbac::Action action_;
  std::vector<Policy> policies_;
  Rbac::AuditCondition audit_condition_;
  std::vector<std::unique_ptr<AuditLogger>> audit_loggers_;
};

}

#endif
