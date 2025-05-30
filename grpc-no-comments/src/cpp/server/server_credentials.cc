// Copyright 2024 The gRPC Authors

#include <grpc/support/port_platform.h>
#include <grpcpp/security/server_credentials.h>

#include "src/core/util/crash.h"

namespace grpc {

ServerCredentials::ServerCredentials(grpc_server_credentials* creds)
    : c_creds_(creds) {}

ServerCredentials::~ServerCredentials() {
  grpc_server_credentials_release(c_creds_);
}

void ServerCredentials::SetAuthMetadataProcessor(
    const std::shared_ptr<grpc::AuthMetadataProcessor>& ) {
  grpc_core::Crash("Not Supported");
}

int ServerCredentials::AddPortToServer(const std::string& addr,
                                       grpc_server* server) {
  return grpc_server_add_http2_port(server, addr.c_str(), c_creds_);
}

}
