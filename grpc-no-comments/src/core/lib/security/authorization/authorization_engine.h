// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_AUTHORIZATION_ENGINE_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_AUTHORIZATION_ENGINE_H

#include <grpc/support/port_platform.h>

#include <string>

#include "src/core/lib/security/authorization/evaluate_args.h"
#include "src/core/util/ref_counted.h"

namespace grpc_core {

class AuthorizationEngine : public RefCounted<AuthorizationEngine> {
 public:
  struct Decision {
    enum class Type {
      kAllow,
      kDeny,
    };
    Type type;
    std::string matching_policy_name;
  };

  virtual Decision Evaluate(const EvaluateArgs& args) const = 0;
};

}

#endif
