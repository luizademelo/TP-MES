// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_CEL_EXPR_BUILDER_FACTORY_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_CEL_EXPR_BUILDER_FACTORY_H

#include <grpc/support/port_platform.h>

#include <memory>

#include "src/core/lib/security/authorization/mock_cel/cel_expression.h"
#include "src/core/lib/security/authorization/mock_cel/flat_expr_builder.h"

namespace grpc_core {
namespace mock_cel {

struct InterpreterOptions {
  bool short_circuiting = true;
};

inline std::unique_ptr<CelExpressionBuilder> CreateCelExpressionBuilder(
    const InterpreterOptions& options) {
  return std::make_unique<FlatExprBuilder>();
}

}
}

#endif
