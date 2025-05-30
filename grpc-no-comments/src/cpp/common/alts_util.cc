
// Copyright 2019 gRPC authors.

#include <grpc/grpc_security_constants.h>
#include <grpcpp/security/alts_context.h>
#include <grpcpp/security/alts_util.h>
#include <grpcpp/security/auth_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/string_ref.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "absl/log/log.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker.h"
#include "src/proto/grpc/gcp/altscontext.upb.h"
#include "upb/mem/arena.hpp"

namespace grpc {
namespace experimental {

std::unique_ptr<AltsContext> GetAltsContextFromAuthContext(
    const std::shared_ptr<const AuthContext>& auth_context) {
  if (auth_context == nullptr) {
    LOG(ERROR) << "auth_context is nullptr.";
    return nullptr;
  }
  std::vector<string_ref> ctx_vector =
      auth_context->FindPropertyValues(TSI_ALTS_CONTEXT);
  if (ctx_vector.size() != 1) {
    LOG(ERROR) << "contains zero or more than one ALTS context.";
    return nullptr;
  }
  upb::Arena context_arena;
  grpc_gcp_AltsContext* ctx = grpc_gcp_AltsContext_parse(
      ctx_vector[0].data(), ctx_vector[0].size(), context_arena.ptr());
  if (ctx == nullptr) {
    LOG(ERROR) << "fails to parse ALTS context.";
    return nullptr;
  }
  if (grpc_gcp_AltsContext_security_level(ctx) < GRPC_SECURITY_MIN ||
      grpc_gcp_AltsContext_security_level(ctx) > GRPC_SECURITY_MAX) {
    LOG(ERROR) << "security_level is invalid.";
    return nullptr;
  }
  return std::make_unique<AltsContext>(AltsContext(ctx));
}

grpc::Status AltsClientAuthzCheck(
    const std::shared_ptr<const AuthContext>& auth_context,
    const std::vector<std::string>& expected_service_accounts) {
  std::unique_ptr<AltsContext> alts_ctx =
      GetAltsContextFromAuthContext(auth_context);
  if (alts_ctx == nullptr) {
    return grpc::Status(grpc::StatusCode::PERMISSION_DENIED,
                        "fails to parse ALTS context.");
  }
  if (std::find(expected_service_accounts.begin(),
                expected_service_accounts.end(),
                alts_ctx->peer_service_account()) !=
      expected_service_accounts.end()) {
    return grpc::Status::OK;
  }
  return grpc::Status(
      grpc::StatusCode::PERMISSION_DENIED,
      "client " + alts_ctx->peer_service_account() + " is not authorized.");
}

}
}
