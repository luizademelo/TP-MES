
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

class CelAuthorizationEngine {
 public:

  static std::unique_ptr<CelAuthorizationEngine> CreateCelAuthorizationEngine(
      const std::vector<envoy_config_rbac_v3_RBAC*>& rbac_policies);

  explicit CelAuthorizationEngine(
      const std::vector<envoy_config_rbac_v3_RBAC*>& rbac_policies);

 private:
  enum Action {
    kAllow,
    kDeny,
  };

  std::unique_ptr<mock_cel::Activation> CreateActivation(
      const EvaluateArgs& args);

  std::map<const std::string, const google_api_expr_v1alpha1_Expr*>
      deny_if_matched_;
  std::map<const std::string, const google_api_expr_v1alpha1_Expr*>
      allow_if_matched_;
  upb::Arena arena_;
  absl::flat_hash_set<std::string> envoy_attributes_;
  absl::flat_hash_set<std::string> header_keys_;
  std::unique_ptr<mock_cel::CelMap> headers_;
};

}

#endif
