// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_FLAT_EXPR_BUILDER_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_FLAT_EXPR_BUILDER_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <set>
#include <string>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "google/api/expr/v1alpha1/syntax.upb.h"
#include "src/core/lib/security/authorization/mock_cel/cel_expression.h"
#include "src/core/lib/security/authorization/mock_cel/evaluator_core.h"

namespace grpc_core {
namespace mock_cel {

class FlatExprBuilder : public CelExpressionBuilder {
 public:
  FlatExprBuilder() = default;

  absl::StatusOr<std::unique_ptr<CelExpression>> CreateExpression(
      const google_api_expr_v1alpha1_Expr* expr,
      const google_api_expr_v1alpha1_SourceInfo* source_info) const override {
    ExecutionPath path;
    return std::make_unique<CelExpressionFlatImpl>(nullptr, path, 0,
                                                   std::set<std::string>{});
  }

  absl::StatusOr<std::unique_ptr<CelExpression>> CreateExpression(
      const google_api_expr_v1alpha1_Expr* expr,
      const google_api_expr_v1alpha1_SourceInfo* source_info,
      std::vector<absl::Status>* warnings) const override {
    ExecutionPath path;
    return std::make_unique<CelExpressionFlatImpl>(nullptr, path, 0,
                                                   std::set<std::string>{});
  }
};

}
}

#endif
