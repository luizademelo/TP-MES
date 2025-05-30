
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/auth_metadata_processor.h>
#include <grpcpp/security/server_credentials.h>

#include <memory>

namespace grpc {
namespace {
class InsecureServerCredentialsImpl final : public ServerCredentials {
 public:
  InsecureServerCredentialsImpl()
      : ServerCredentials(grpc_insecure_server_credentials_create()) {}
};
}

std::shared_ptr<ServerCredentials> InsecureServerCredentials() {
  return std::make_shared<InsecureServerCredentialsImpl>();
}

}
