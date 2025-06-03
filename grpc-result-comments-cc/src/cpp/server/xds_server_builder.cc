Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

// Include necessary gRPC headers
#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/xds_server_builder.h>

// Include xDS server implementation
#include "src/core/xds/grpc/xds_enabled_server.h"

namespace grpc {

// Builds and returns channel arguments for an xDS-enabled server
ChannelArguments XdsServerBuilder::BuildChannelArgs() {
  // Start with the base channel arguments from ServerBuilder
  ChannelArguments args = ServerBuilder::BuildChannelArgs();
  
  // If drain grace time is specified (non-negative), set it in the channel args
  // This controls how long the server waits for existing RPCs to complete during shutdown
  if (drain_grace_time_ms_ >= 0) {
    args.SetInt(GRPC_ARG_SERVER_CONFIG_CHANGE_DRAIN_GRACE_TIME_MS,
                drain_grace_time_ms_);
  }
  
  // Enable xDS functionality by setting the xDS enabled flag
  args.SetInt(GRPC_ARG_XDS_ENABLED_SERVER, 1);
  
  // Get the underlying C channel arguments for xDS fetcher creation
  grpc_channel_args c_channel_args = args.c_channel_args();
  
  // Create an xDS server config fetcher with:
  // - Callback for serving status updates (OnServingStatusUpdate)
  // - Notifier object for status updates
  // - The channel arguments we just configured
  grpc_server_config_fetcher* fetcher = grpc_server_config_fetcher_xds_create(
      {OnServingStatusUpdate, notifier_}, &c_channel_args);
  
  // If fetcher was successfully created, set it for the server
  if (fetcher != nullptr) set_fetcher(fetcher);
  
  // Return the configured channel arguments
  return args;
}

}  // namespace grpc
```

The comments explain:
1. The overall purpose of the function
2. Each major step in the process
3. The significance of key parameters and operations
4. The flow of data through the function
5. Error handling (null check for fetcher)
6. The relationship between different components

The comments are kept concise while providing enough context for future maintainers to understand both what the code does and why it does it.