
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/client_interceptor.h>

#include <memory>

namespace grpc {
namespace {
class InsecureChannelCredentialsImpl final : public ChannelCredentials {
 public:
  InsecureChannelCredentialsImpl()
      : ChannelCredentials(grpc_insecure_credentials_create()) {}

 private:
  std::shared_ptr<Channel> CreateChannelWithInterceptors(
      const std::string& target, const ChannelArguments& args,
      std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators) override {
    grpc_channel_args channel_args;
    args.SetChannelArgs(&channel_args);
    return grpc::CreateChannelInternal(
        "", grpc_channel_create(target.c_str(), c_creds(), &channel_args),
        std::move(interceptor_creators));
  }
};
}

std::shared_ptr<ChannelCredentials> InsecureChannelCredentials() {
  return std::make_shared<InsecureChannelCredentialsImpl>();
}

}
