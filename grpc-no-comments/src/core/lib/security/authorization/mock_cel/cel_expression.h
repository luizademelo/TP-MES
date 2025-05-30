// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_CEL_EXPRESSION_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_CEL_EXPRESSION_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "google/api/expr/v1alpha1/syntax.upb.h"
#include "src/core/lib/security/authorization/mock_cel/activation.h"
#include "src/core/lib/security/authorization/mock_cel/cel_value.h"

namespace grpc_core {
namespace mock_cel {

class CelExpression {
 public:
  virtual ~CelExpression() = default;

  virtual absl::StatusOr<CelValue> Evaluate(
      const BaseActivation& activation) const = 0;
};

class CelExpressionBuilder {
 public:
  virtual ~CelExpressionBuilder() = default;

  virtual absl::StatusOr<std::unique_ptr<CelExpression>> CreateExpression(
      const google_api_expr_v1alpha1_Expr* expr,
      const google_api_expr_v1alpha1_SourceInfo* source_info) const = 0;

  virtual absl::StatusOr<std::unique_ptr<CelExpression>> CreateExpression(
      const google_api_expr_v1alpha1_Expr* expr,
      const google_api_expr_v1alpha1_SourceInfo* source_info,
      std::vector<absl::Status>* warnings) const = 0;
};

}
}

#endif
