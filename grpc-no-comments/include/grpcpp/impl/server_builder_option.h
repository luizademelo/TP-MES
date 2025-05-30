
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_SERVER_BUILDER_OPTION_H
#define GRPCPP_IMPL_SERVER_BUILDER_OPTION_H

#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/support/channel_arguments.h>

#include <map>
#include <memory>

namespace grpc {

class ServerBuilderOption {
 public:
  virtual ~ServerBuilderOption() {}

  virtual void UpdateArguments(grpc::ChannelArguments* args) = 0;

  virtual void UpdatePlugins(
      std::vector<std::unique_ptr<grpc::ServerBuilderPlugin>>* plugins) = 0;
};

}

#endif
