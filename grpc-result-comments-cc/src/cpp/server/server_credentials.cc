Here's the commented version of the code snippet:

```c++
// Copyright 2024 The gRPC Authors

#include <grpc/support/port_platform.h>
#include <grpcpp/security/server_credentials.h>

#include "src/core/util/crash.h"

namespace grpc {

// Constructor for ServerCredentials that takes a raw grpc_server_credentials pointer
// and stores it internally. The caller retains ownership of the credentials.
// @param creds: Raw pointer to grpc_server_credentials to be wrapped
ServerCredentials::ServerCredentials(grpc_server_credentials* creds)
    : c_creds_(creds) {}

// Destructor for ServerCredentials that releases the underlying 
// grpc_server_credentials resources using the gRPC core API
ServerCredentials::~ServerCredentials() {
  grpc_server_credentials_release(c_creds_);
}

// Sets an authentication metadata processor for these credentials
// Note: This implementation intentionally crashes as it's not supported
// @param processor: Shared pointer to AuthMetadataProcessor (unused)
void ServerCredentials::SetAuthMetadataProcessor(
    const std::shared_ptr<grpc::AuthMetadataProcessor>& ) {
  grpc_core::Crash("Not Supported");
}

// Adds a port to the server with these credentials
// @param addr: The address/port to bind to (e.g., "0.0.0.0:50051")
// @param server: The gRPC server to which the port should be added
// @return: The port number on success, 0 on failure
int ServerCredentials::AddPortToServer(const std::string& addr,
                                       grpc_server* server) {
  return grpc_server_add_http2_port(server, addr.c_str(), c_creds_);
}

} // namespace grpc
```