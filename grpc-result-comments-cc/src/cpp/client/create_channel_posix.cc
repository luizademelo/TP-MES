Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Include necessary gRPC headers
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_posix.h>
#include <grpc/grpc_security.h>
#include <grpcpp/channel.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/client_interceptor.h>

// Standard library includes
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Internal implementation header
#include "src/cpp/client/create_channel_internal.h"

namespace grpc {

// Forward declaration
class ChannelArguments;

// Only compile this code if the platform supports channels from file descriptors
#ifdef GPR_SUPPORT_CHANNELS_FROM_FD

/**
 * Creates an insecure gRPC channel from a file descriptor.
 * 
 * @param target The target address for the channel (unused for FD channels)
 * @param fd The file descriptor to use for communication
 * @return shared_ptr<Channel> A shared pointer to the created channel
 */
std::shared_ptr<Channel> CreateInsecureChannelFromFd(const std::string& target,
                                                     int fd) {
  // Initialize gRPC library
  internal::GrpcLibrary init_lib;
  // Create insecure credentials
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  // Create channel from file descriptor with no additional arguments or interceptors
  auto channel = CreateChannelInternal(
      "", grpc_channel_create_from_fd(target.c_str(), fd, creds, nullptr),
      std::vector<
          std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>());
  // Release credentials as they're no longer needed
  grpc_channel_credentials_release(creds);
  return channel;
}

/**
 * Creates an insecure gRPC channel from a file descriptor with custom arguments.
 * 
 * @param target The target address for the channel (unused for FD channels)
 * @param fd The file descriptor to use for communication
 * @param args Channel configuration arguments
 * @return shared_ptr<Channel> A shared pointer to the created channel
 */
std::shared_ptr<Channel> CreateCustomInsecureChannelFromFd(
    const std::string& target, int fd, const grpc::ChannelArguments& args) {
  // Initialize gRPC library
  internal::GrpcLibrary init_lib;
  // Convert C++ ChannelArguments to C grpc_channel_args
  grpc_channel_args channel_args;
  args.SetChannelArgs(&channel_args);
  // Create insecure credentials
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  // Create channel from file descriptor with custom arguments and no interceptors
  auto channel = CreateChannelInternal(
      "", grpc_channel_create_from_fd(target.c_str(), fd, creds, &channel_args),
      std::vector<
          std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>());
  // Release credentials as they're no longer needed
  grpc_channel_credentials_release(creds);

  return channel;
}

namespace experimental {

/**
 * Creates an insecure gRPC channel from a file descriptor with custom arguments 
 * and interceptors.
 * 
 * @param target The target address for the channel (unused for FD channels)
 * @param fd The file descriptor to use for communication
 * @param args Channel configuration arguments
 * @param interceptor_creators Factories for creating client interceptors
 * @return shared_ptr<Channel> A shared pointer to the created channel
 */
std::shared_ptr<Channel> CreateCustomInsecureChannelWithInterceptorsFromFd(
    const std::string& target, int fd, const ChannelArguments& args,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators) {
  // Initialize gRPC library
  internal::GrpcLibrary init_lib;
  // Convert C++ ChannelArguments to C grpc_channel_args
  grpc_channel_args channel_args;
  args.SetChannelArgs(&channel_args);
  // Create insecure credentials
  grpc_channel_credentials* creds = grpc_insecure_credentials_create();
  // Create channel from file descriptor with custom arguments and interceptors
  auto channel = CreateChannelInternal(
      "", grpc_channel_create_from_fd(target.c_str(), fd, creds, &channel_args),
      std::move(interceptor_creators));
  // Release credentials as they're no longer needed
  grpc_channel_credentials_release(creds);
  return channel;
}

}  // namespace experimental

#endif  // GPR_SUPPORT_CHANNELS_FROM_FD

}  // namespace grpc
```

Key improvements made:
1. Added detailed function-level comments explaining purpose, parameters, and return values
2. Added comments for important code blocks
3. Documented the namespace scope and experimental namespace
4. Added comments for platform-specific compilation (#ifdef)
5. Added comments for resource management (credentials release)
6. Added comments for standard library includes
7. Added clear indication of namespace closing braces
8. Documented the forward declaration
9. Added comments for internal library initialization

The comments now provide a clear understanding of:
- What each function does
- What parameters are used for
- Resource management considerations
- Platform-specific behavior
- The role of different code blocks
- The overall structure of the code