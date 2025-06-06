// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_EVALUATOR_CORE_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_EVALUATOR_CORE_H

#include <grpc/support/port_platform.h>

#include <set>
#include <string>

#include "absl/status/statusor.h"
#include "google/api/expr/v1alpha1/syntax.upb.h"
#include "src/core/lib/security/authorization/mock_cel/activation.h"
#include "src/core/lib/security/authorization/mock_cel/cel_expression.h"
#include "src/core/lib/security/authorization/mock_cel/cel_value.h"

namespace grpc_core {
namespace mock_cel {

class ExecutionPath {
 public:
  ExecutionPath() = default;
};

class CelExpressionFlatImpl : public CelExpression {

 public:
  CelExpressionFlatImpl(const google_api_expr_v1alpha1_Expr* root_expr,
                        ExecutionPath path, int max_iterations,
                        std::set<std::string> iter_variable_names,
                        bool enable_unknowns = false,
                        bool enable_unknown_function_results = false) {}

  absl::StatusOr<CelValue> Evaluate(
      const BaseActivation& activation) const override {
    return CelValue::CreateNull();
  }
};

}
}

#endif
