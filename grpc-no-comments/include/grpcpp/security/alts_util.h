
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_SECURITY_ALTS_UTIL_H
#define GRPCPP_SECURITY_ALTS_UTIL_H

#include <grpc/grpc_security_constants.h>
#include <grpcpp/security/alts_context.h>
#include <grpcpp/security/auth_context.h>
#include <grpcpp/support/status.h>

#include <memory>

struct grpc_gcp_AltsContext;

namespace grpc {
namespace experimental {

std::unique_ptr<AltsContext> GetAltsContextFromAuthContext(
    const std::shared_ptr<const AuthContext>& auth_context);

grpc::Status AltsClientAuthzCheck(
    const std::shared_ptr<const AuthContext>& auth_context,
    const std::vector<std::string>& expected_service_accounts);

}
}

#endif
