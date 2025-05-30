
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/auth_context.h>

#include <memory>

#include "src/core/transport/auth_context.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/cpp/common/secure_auth_context.h"

namespace grpc {

std::shared_ptr<const AuthContext> CreateAuthContext(grpc_call* call) {
  if (call == nullptr) {
    return std::shared_ptr<const AuthContext>();
  }
  grpc_core::RefCountedPtr<grpc_auth_context> ctx(grpc_call_auth_context(call));
  return std::make_shared<SecureAuthContext>(ctx.get());
}

}
