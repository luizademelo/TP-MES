Here's the commented version of the code:

```c++
// Copyright 2025 gRPC authors.

#include <grpc/grpc.h>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/server/server.h"

/// @brief Adds an HTTP/2 port to a gRPC server with specified credentials
/// @param server The gRPC server instance to add the port to
/// @param addr The address to listen on (e.g., "0.0.0.0:50051")
/// @param creds The server credentials to use for secure connections
/// @return The port number on success, 0 on failure
int grpc_server_add_http2_port(grpc_server* server, const char* addr,
                               grpc_server_credentials* creds) {
  // Initialize execution context for the current thread
  grpc_core::ExecCtx exec_ctx;
  
  // Security connector for secure connections
  grpc_core::RefCountedPtr<grpc_server_security_connector> sc;
  
  // Convert C-style server to core server instance
  grpc_core::Server* core_server = grpc_core::Server::FromC(server);
  
  // Get the server's channel arguments
  grpc_core::ChannelArgs args = core_server->channel_args();
  
  // Log the API call for debugging purposes
  GRPC_TRACE_LOG(api, INFO) << "grpc_server_add_http2_port(server=" << server
                            << ", addr=" << addr << ", creds=" << creds << ")";
  
  // Validate credentials are provided for secure server
  if (creds == nullptr) {
    LOG(ERROR)
        << "Failed to add port to server: No credentials specified for secure "
           "server port (creds==NULL)";
    return 0;
  }

  // Handle configuration based on whether config fetcher is present
  if (core_server->config_fetcher() != nullptr) {
    // When using config fetcher, just add credentials to args
    args = args.SetObject(creds->Ref());
  } else {
    // Without config fetcher, create a security connector
    sc = creds->create_security_connector(grpc_core::ChannelArgs());
    if (sc == nullptr) {
      LOG(ERROR) << "Unable to create secure server with credentials of type ",
          creds->type().name();
      return 0;
    }
    // Add both credentials and security connector to args
    args = args.SetObject(creds->Ref()).SetObject(sc);
  }
  
  // Parse preferred transport protocols (default to "h2" if not specified)
  std::vector<absl::string_view> transport_preferences = absl::StrSplit(
      args.GetString(GRPC_ARG_PREFERRED_TRANSPORT_PROTOCOLS).value_or("h2"),
      ',');
      
  // Currently only support exactly one transport protocol
  if (transport_preferences.size() != 1) {
    LOG(ERROR) << "Failed to add port to server: "
                  "Only one preferred transport name is currently supported: "
                  "requested='"
               << *args.GetString(GRPC_ARG_PREFERRED_TRANSPORT_PROTOCOLS)
               << "'";
    return 0;
  }
  
  // Get the transport implementation for the preferred protocol
  auto* transport = grpc_core::CoreConfiguration::Get()
                        .endpoint_transport_registry()
                        .GetTransport(transport_preferences[0]);
  if (transport == nullptr) {
    LOG(ERROR) << "Failed to add port to server: unknown protocol '"
               << transport_preferences[0] << "'";
    return 0;
  }
  
  // Attempt to add the port using the selected transport
  auto r = transport->AddPort(core_server, addr, args);
  if (!r.ok()) {
    LOG(ERROR) << "Failed to add port to server: " << r.status().message();
    return 0;
  }
  
  // Return the successfully bound port number
  return *r;
}
```

Key aspects covered in the comments:
1. Function purpose and parameters
2. Major steps in the execution flow
3. Error handling cases
4. Configuration variations (with/without config fetcher)
5. Transport protocol selection logic
6. Return value explanation

The comments are designed to help future maintainers understand:
- The overall workflow of adding an HTTP/2 port
- The security considerations
- The configuration options
- The error cases
- The transport protocol selection mechanism