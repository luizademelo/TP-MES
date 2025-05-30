// Copyright 2024 The gRPC Authors

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>
#include <string>
#include <vector>

namespace grpc {

ChannelCredentials::ChannelCredentials(grpc_channel_credentials* c_creds)
    : c_creds_(c_creds) {}

ChannelCredentials::~ChannelCredentials() {
  grpc_channel_credentials_release(c_creds_);
}

std::shared_ptr<Channel> ChannelCredentials::CreateChannelWithInterceptors(
    const std::string& target, const ChannelArguments& args,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators) {
  grpc_channel_args channel_args;
  args.SetChannelArgs(&channel_args);
  return grpc::CreateChannelInternal(
      args.GetSslTargetNameOverride(),
      grpc_channel_create(target.c_str(), c_creds_, &channel_args),
      std::move(interceptor_creators));
}

}
