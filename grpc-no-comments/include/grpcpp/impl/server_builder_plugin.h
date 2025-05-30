
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_IMPL_SERVER_BUILDER_PLUGIN_H
#define GRPCPP_IMPL_SERVER_BUILDER_PLUGIN_H

#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/config.h>

#include <memory>

namespace grpc {

class ServerBuilder;
class ServerInitializer;

class ServerBuilderPlugin {
 public:
  virtual ~ServerBuilderPlugin() {}
  virtual std::string name() = 0;

  virtual void UpdateServerBuilder(ServerBuilder* ) {}

  virtual void InitServer(ServerInitializer* si) = 0;

  virtual void Finish(ServerInitializer* si) = 0;

  virtual void ChangeArguments(const std::string& name, void* value) = 0;

  virtual void UpdateChannelArguments(ChannelArguments* ) {}

  virtual bool has_sync_methods() const { return false; }
  virtual bool has_async_methods() const { return false; }
};

}

#endif
