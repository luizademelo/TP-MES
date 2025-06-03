Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_CEL_AUTHORIZATION_ENGINE_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_CEL_AUTHORIZATION_ENGINE_H

#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "envoy/config/rbac/v3/rbac.upb.h"
#include "google/api/expr/v1alpha1/syntax.upb.h"
#include "src/core/lib/security/authorization/evaluate_args.h"
#include "src/core/lib/security/authorization/mock_cel/activation.h"
#include "src/core/lib/security/authorization/mock_cel/cel_value.h"
#include "upb/mem/arena.hpp"

namespace grpc_core {

// CelAuthorizationEngine implements authorization logic using Common Expression Language (CEL).
// It evaluates RBAC (Role-Based Access Control) policies to determine if a request should be
// allowed or denied.
class CelAuthorizationEngine {
 public:
  // Creates a new CelAuthorizationEngine instance from a set of RBAC policies.
  // Returns a unique_ptr to the created engine.
  static std::unique_ptr<CelAuthorizationEngine> CreateCelAuthorizationEngine(
      const std::vector<envoy_config_rbac_v3_RBAC*>& rbac_policies);

  // Constructs a CelAuthorizationEngine directly from RBAC policies.
  explicit CelAuthorizationEngine(
      const std::vector<envoy_config_rbac_v3_RBAC*>& rbac_policies);

 private:
  // Possible authorization actions that can be taken.
  enum Action {
    kAllow,  // Request is allowed
    kDeny,   // Request is denied
  };

  // Creates an activation context for CEL expression evaluation.
  // The activation provides variable bindings and function implementations
  // during expression evaluation.
  std::unique_ptr<mock_cel::Activation> CreateActivation(
      const EvaluateArgs& args);

  // Map of policy names to CEL expressions for deny conditions.
  // If any expression evaluates to true, the request will be denied.
  std::map<const std::string, const google_api_expr_v1alpha1_Expr*>
      deny_if_matched_;

  // Map of policy names to CEL expressions for allow conditions.
  // If any expression evaluates to true, the request will be allowed.
  std::map<const std::string, const google_api_expr_v1alpha1_Expr*>
      allow_if_matched_;

  // Memory arena used for protobuf message allocation.
  upb::Arena arena_;

  // Set of Envoy-specific attributes that can be referenced in CEL expressions.
  absl::flat_hash_set<std::string> envoy_attributes_;

  // Set of HTTP header keys that can be referenced in CEL expressions.
  absl::flat_hash_set<std::string> header_keys_;

  // Map of HTTP headers that can be referenced in CEL expressions.
  std::unique_ptr<mock_cel::CelMap> headers_;
};

}

#endif
```