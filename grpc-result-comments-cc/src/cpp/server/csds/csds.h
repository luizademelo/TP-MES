Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CPP_SERVER_CSDS_CSDS_H
#define GRPC_SRC_CPP_SERVER_CSDS_CSDS_H

// Include necessary gRPC platform support and C++ interface headers
#include <grpc/support/port_platform.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

// Include the generated protobuf service definition for CSDS (Client Status Discovery Service)
#include "src/proto/grpc/testing/xds/v3/csds.grpc.pb.h"

namespace grpc {
namespace xds {
namespace experimental {

// ClientStatusDiscoveryService implements the CSDS gRPC service which provides
// information about xDS clients' status and configuration.
// This is the C++ implementation of the service defined in csds.proto.
class ClientStatusDiscoveryService final
    : public envoy::service::status::v3::ClientStatusDiscoveryService::Service {
 public:
  // Handles a bidirectional streaming RPC for client status updates.
  // Parameters:
  //   - context: Server context for this RPC (unused in this declaration)
  //   - stream: Bidirectional stream for reading requests and writing responses
  // Returns:
  //   - Status object indicating success or failure of the RPC
  Status StreamClientStatus(
      ServerContext* ,
      ServerReaderWriter<envoy::service::status::v3::ClientStatusResponse,
                         envoy::service::status::v3::ClientStatusRequest>*
          stream) override;

  // Handles a unary RPC for fetching client status.
  // Parameters:
  //   - context: Server context for this RPC (unused in this declaration)
  //   - request: The status request from client
  //   - response: The status response to be filled by the server
  // Returns:
  //   - Status object indicating success or failure of the RPC
  Status FetchClientStatus(
      ServerContext* ,
      const envoy::service::status::v3::ClientStatusRequest* ,
      envoy::service::status::v3::ClientStatusResponse* response) override;
};

}  // namespace experimental
}  // namespace xds
}  // namespace grpc

#endif  // GRPC_SRC_CPP_SERVER_CSDS_CSDS_H
```

Key improvements made:
1. Added explanation of the header guard purpose
2. Documented the purpose of each included header
3. Added a class-level comment explaining what ClientStatusDiscoveryService is
4. Added detailed comments for each method including parameters and return values
5. Added namespace closing comments for better readability
6. Added comment for the closing header guard
7. Explained the relationship with the protobuf service definition

The comments now provide a clear understanding of:
- What this service does
- How the methods are intended to be used
- The purpose of each component
- The structure of the code