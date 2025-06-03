Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/lib/security/authorization/grpc_authorization_engine.h"

#include <grpc/support/port_platform.h>

#include <algorithm>
#include <map>
#include <utility>

#include "absl/log/check.h"
#include "src/core/lib/security/authorization/audit_logging.h"
#include "src/core/lib/security/authorization/authorization_engine.h"

namespace grpc_core {

using experimental::AuditContext;
using experimental::AuditLoggerRegistry;

namespace {

using Decision = AuthorizationEngine::Decision;

// Determines whether an audit log should be written based on the decision and audit condition.
// Returns true if:
// 1. Audit condition is set to log on both allow and deny, OR
// 2. Decision is ALLOW and audit condition is set to log on allow, OR
// 3. Decision is DENY and audit condition is set to log on deny
bool ShouldLog(const Decision& decision,
               const Rbac::AuditCondition& condition) {
  return condition == Rbac::AuditCondition::kOnDenyAndAllow ||
         (decision.type == Decision::Type::kAllow &&
          condition == Rbac::AuditCondition::kOnAllow) ||
         (decision.type == Decision::Type::kDeny &&
          condition == Rbac::AuditCondition::kOnDeny);
}

}  // namespace

// Constructs a GrpcAuthorizationEngine from an RBAC policy.
// Initializes:
// - Engine name from policy.name
// - Action (ALLOW/DENY) from policy.action
// - Audit logging condition from policy.audit_condition
// Converts each sub-policy into Policy objects with matchers
// Initializes audit loggers from logger configurations
GrpcAuthorizationEngine::GrpcAuthorizationEngine(Rbac policy)
    : name_(std::move(policy.name)),
      action_(policy.action),
      audit_condition_(policy.audit_condition) {
  // Convert each sub-policy into Policy objects with matchers
  for (auto& sub_policy : policy.policies) {
    Policy policy;
    policy.name = sub_policy.first;
    policy.matcher = std::make_unique<PolicyAuthorizationMatcher>(
        std::move(sub_policy.second));
    policies_.push_back(std::move(policy));
  }
  // Create and store audit loggers from configurations
  for (auto& logger_config : policy.logger_configs) {
    auto logger =
        AuditLoggerRegistry::CreateAuditLogger(std::move(logger_config));
    CHECK(logger != nullptr);  // Ensure logger creation succeeded
    audit_loggers_.push_back(std::move(logger));
  }
}

// Move constructor - transfers ownership of resources from another engine
GrpcAuthorizationEngine::GrpcAuthorizationEngine(
    GrpcAuthorizationEngine&& other) noexcept
    : name_(std::move(other.name_)),
      action_(other.action_),
      policies_(std::move(other.policies_)),
      audit_condition_(other.audit_condition_),
      audit_loggers_(std::move(other.audit_loggers_)) {}

// Move assignment operator - transfers ownership of resources from another engine
GrpcAuthorizationEngine& GrpcAuthorizationEngine::operator=(
    GrpcAuthorizationEngine&& other) noexcept {
  name_ = std::move(other.name_);
  action_ = other.action_;
  policies_ = std::move(other.policies_);
  audit_condition_ = other.audit_condition_;
  audit_loggers_ = std::move(other.audit_loggers_);
  return *this;
}

// Evaluates authorization for given request arguments
// Returns Decision containing:
// - ALLOW/DENY based on policy action and matching result
// - Name of the matching policy (if any)
// Logs audit events based on audit condition and decision
AuthorizationEngine::Decision GrpcAuthorizationEngine::Evaluate(
    const EvaluateArgs& args) const {
  Decision decision;
  bool matches = false;
  
  // Check each policy to find a match
  for (const auto& policy : policies_) {
    if (policy.matcher->Matches(args)) {
      matches = true;
      decision.matching_policy_name = policy.name;
      break;  // First match wins
    }
  }
  
  // Determine decision type based on action and match result:
  // - For ALLOW action: match -> ALLOW, no match -> DENY
  // - For DENY action: match -> DENY, no match -> ALLOW
  decision.type = (matches == (action_ == Rbac::Action::kAllow))
                      ? Decision::Type::kAllow
                      : Decision::Type::kDeny;
  
  // Log audit event if conditions are met
  if (ShouldLog(decision, audit_condition_)) {
    for (auto& logger : audit_loggers_) {
      logger->Log(AuditContext(args.GetPath(), args.GetSpiffeId(), name_,
                               decision.matching_policy_name,
                               decision.type == Decision::Type::kAllow));
    }
  }
  return decision;
}

}  // namespace grpc_core
```