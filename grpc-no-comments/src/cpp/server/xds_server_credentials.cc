
// Copyright 2020 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/server_credentials.h>

#include <memory>

#include "absl/log/check.h"

namespace grpc {

std::shared_ptr<ServerCredentials> XdsServerCredentials(
    const std::shared_ptr<ServerCredentials>& fallback_credentials) {
  CHECK_NE(fallback_credentials, nullptr);
  CHECK_NE(fallback_credentials->c_creds_, nullptr);
  return std::shared_ptr<ServerCredentials>(new ServerCredentials(
      grpc_xds_server_credentials_create(fallback_credentials->c_creds_)));
}

namespace experimental {

std::shared_ptr<ServerCredentials> XdsServerCredentials(
    const std::shared_ptr<ServerCredentials>& fallback_credentials) {
  return grpc::XdsServerCredentials(fallback_credentials);
}

}
}
