
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_CREATE_AUTH_CONTEXT_H
#define GRPCPP_IMPL_CREATE_AUTH_CONTEXT_H

#include <grpc/impl/grpc_types.h>
#include <grpcpp/security/auth_context.h>

#include <memory>

namespace grpc {

std::shared_ptr<const AuthContext> CreateAuthContext(grpc_call* call);

}

#endif
