Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC headers
#include <grpc/grpc.h>
#include <grpc/status.h>
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/client_interceptor.h>
#include <grpcpp/support/config.h>

// Standard C++ headers
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Internal implementation header
#include "src/cpp/client/create_channel_internal.h"

namespace grpc {

/// @brief Creates a gRPC channel with default arguments
/// @param target The server address (e.g., "localhost:50051")
/// @param creds Channel credentials (e.g., SSL or insecure credentials)
/// @return Shared pointer to the created Channel object
std::shared_ptr<grpc::Channel> CreateChannel(
    const grpc::string& target,
    const std::shared_ptr<grpc::ChannelCredentials>& creds) {
  return CreateCustomChannel(target, creds, grpc::ChannelArguments());
}

/// @brief Creates a gRPC channel with custom arguments
/// @param target The server address (e.g., "localhost:50051")
/// @param creds Channel credentials (e.g., SSL or insecure credentials)
/// @param args Custom channel arguments for configuration
/// @return Shared pointer to the created Channel object
/// @note Initializes gRPC library automatically. Returns a "lame" channel if credentials are invalid.
std::shared_ptr<grpc::Channel> CreateCustomChannel(
    const grpc::string& target,
    const std::shared_ptr<grpc::ChannelCredentials>& creds,
    const grpc::ChannelArguments& args) {
  // Initialize gRPC library (RAII pattern)
  grpc::internal::GrpcLibrary init_lib;
  
  // Create channel with credentials if valid, otherwise create a "lame" channel
  return creds ? creds->CreateChannelImpl(target, args)
               : grpc::CreateChannelInternal(
                     "",
                     grpc_lame_client_channel_create(
                         nullptr, GRPC_STATUS_INVALID_ARGUMENT,
                         "Invalid credentials."),
                     std::vector<std::unique_ptr<
                         grpc::experimental::
                             ClientInterceptorFactoryInterface>>());
}

namespace experimental {

/// @brief Creates a gRPC channel with custom arguments and interceptors
/// @param target The server address (e.g., "localhost:50051")
/// @param creds Channel credentials (e.g., SSL or insecure credentials)
/// @param args Custom channel arguments for configuration
/// @param interceptor_creators Factory objects for creating client interceptors
/// @return Shared pointer to the created Channel object
/// @note Initializes gRPC library automatically. Returns a "lame" channel if credentials are invalid.
std::shared_ptr<grpc::Channel> CreateCustomChannelWithInterceptors(
    const std::string& target,
    const std::shared_ptr<grpc::ChannelCredentials>& creds,
    const grpc::ChannelArguments& args,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators) {
  // Initialize gRPC library (RAII pattern)
  grpc::internal::GrpcLibrary init_lib;
  
  // Create channel with interceptors if credentials are valid, otherwise create a "lame" channel
  return creds ? creds->CreateChannelWithInterceptors(
                     target, args, std::move(interceptor_creators))
               : grpc::CreateChannelInternal(
                     "",
                     grpc_lame_client_channel_create(
                         nullptr, GRPC_STATUS_INVALID_ARGUMENT,
                         "Invalid credentials."),
                     std::move(interceptor_creators));
}

}  // namespace experimental

}  // namespace grpc
```

Key improvements in the comments:
1. Added detailed function documentation with @brief, @param, @return, and @note tags
2. Explained the purpose of each function and its parameters
3. Noted the automatic gRPC library initialization
4. Explained the fallback to "lame" channel when credentials are invalid
5. Added namespace closing comments for better readability
6. Explained the RAII pattern used for GrpcLibrary initialization
7. Added comments about the standard and gRPC-specific headers