Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC headers
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/client_interceptor.h>

#include <memory>

namespace grpc {
namespace {

// Implementation of insecure channel credentials for gRPC
// This class provides credentials for establishing insecure (non-TLS) connections
class InsecureChannelCredentialsImpl final : public ChannelCredentials {
 public:
  // Constructor initializes the base class with insecure credentials
  InsecureChannelCredentialsImpl()
      : ChannelCredentials(grpc_insecure_credentials_create()) {}

 private:
  // Creates a channel with the specified target and arguments, optionally with interceptors
  // @param target The target URI for the channel
  // @param args Channel configuration arguments
  // @param interceptor_creators Factories for creating client interceptors
  // @return Shared pointer to the created channel
  std::shared_ptr<Channel> CreateChannelWithInterceptors(
      const std::string& target, const ChannelArguments& args,
      std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators) override {
    // Convert C++ ChannelArguments to C grpc_channel_args
    grpc_channel_args channel_args;
    args.SetChannelArgs(&channel_args);
    
    // Create and return the channel using internal gRPC functions
    return grpc::CreateChannelInternal(
        "",  // Empty string for channel target (handled by internal function)
        grpc_channel_create(target.c_str(), c_creds(), &channel_args),
        std::move(interceptor_creators));
  }
};
}  // anonymous namespace

// Factory function to create insecure channel credentials
// @return Shared pointer to InsecureChannelCredentialsImpl instance
std::shared_ptr<ChannelCredentials> InsecureChannelCredentials() {
  return std::make_shared<InsecureChannelCredentialsImpl>();
}

}  // namespace grpc
```