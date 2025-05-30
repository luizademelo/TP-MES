
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/security/auth_context.h>

#include <memory>

namespace grpc {

std::shared_ptr<const AuthContext> CreateAuthContext(grpc_call* call) {
  (void)call;
  return std::shared_ptr<const AuthContext>();
}

}
