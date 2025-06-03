Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/cpp/server/csds/csds.h"

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/slice.h>

#include <string>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace grpc {
namespace xds {
namespace experimental {

// Import protobuf message types for client status requests and responses
using envoy::service::status::v3::ClientStatusRequest;
using envoy::service::status::v3::ClientStatusResponse;

namespace {

// Helper function that dumps the current xDS client configuration and returns it
// as a ClientStatusResponse proto message.
// Returns:
//   - On success: ClientStatusResponse containing the xDS configuration
//   - On failure: absl::Status with error details
absl::StatusOr<ClientStatusResponse> DumpClientStatusResponse() {
  ClientStatusResponse response;
  // Get serialized xDS configuration from gRPC core
  grpc_slice serialized_client_config = grpc_dump_xds_configs();
  // Convert the slice to a string
  std::string bytes = StringFromCopiedSlice(serialized_client_config);
  // Release the slice memory
  grpc_slice_unref(serialized_client_config);
  // Parse the string into the protobuf message
  if (!response.ParseFromString(bytes)) {
    return absl::InternalError("Failed to parse ClientStatusResponse.");
  }
  return response;
}

}  // namespace

// Implementation of the streaming RPC method for client status discovery.
// This method handles a bidirectional stream of ClientStatusRequest and
// ClientStatusResponse messages.
// Args:
//   - context: Server context (unused)
//   - stream: Bidirectional stream for reading requests and writing responses
// Returns:
//   - Status::OK on successful completion
//   - Error status if any critical failure occurs
Status ClientStatusDiscoveryService::StreamClientStatus(
    ServerContext* /*context*/,
    ServerReaderWriter<ClientStatusResponse, ClientStatusRequest>* stream) {
  ClientStatusRequest request;
  // Continuously read requests from the stream
  while (stream->Read(&request)) {
    // Get the current xDS configuration
    absl::StatusOr<ClientStatusResponse> response = DumpClientStatusResponse();
    if (!response.ok()) {
      // If xDS is not available, send empty response and continue
      if (response.status().code() == absl::StatusCode::kUnavailable) {
        stream->Write(ClientStatusResponse());
        continue;
      }
      // For other errors, return the error status
      return Status(static_cast<StatusCode>(response.status().raw_code()),
                    response.status().ToString());
    }
    // Send the successful response
    stream->Write(*response);
  }
  return Status::OK;
}

// Implementation of the unary RPC method for client status discovery.
// Args:
//   - context: Server context (unused)
//   - request: Client status request (unused)
//   - response: Output parameter for the client status response
// Returns:
//   - Status::OK on successful completion or when xDS is unavailable
//   - Error status if any critical failure occurs
Status ClientStatusDiscoveryService::FetchClientStatus(
    ServerContext* /*context*/, const ClientStatusRequest* /*request*/,
    ClientStatusResponse* response) {
  // Get the current xDS configuration
  absl::StatusOr<ClientStatusResponse> s = DumpClientStatusResponse();
  if (!s.ok()) {
    // If xDS is not available, return OK with empty response
    if (s.status().code() == absl::StatusCode::kUnavailable) {
      return Status::OK;
    }
    // For other errors, return the error status
    return Status(static_cast<StatusCode>(s.status().raw_code()),
                  s.status().ToString());
  }
  // Move the successful response to the output parameter
  *response = std::move(*s);
  return Status::OK;
}

}  // namespace experimental
}  // namespace xds
}  // namespace grpc
```