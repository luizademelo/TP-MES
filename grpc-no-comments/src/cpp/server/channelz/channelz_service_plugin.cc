
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>
#include <grpcpp/ext/channelz_service_plugin.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/impl/server_initializer.h>
#include <grpcpp/server_builder.h>

#include <memory>
#include <string>

#include "src/cpp/server/channelz/channelz_service.h"

namespace grpc {
namespace channelz {
namespace experimental {

class ChannelzServicePlugin : public grpc::ServerBuilderPlugin {
 public:
  ChannelzServicePlugin() : channelz_service_(new grpc::ChannelzService()) {}

  std::string name() override { return "channelz_service"; }

  void InitServer(grpc::ServerInitializer* si) override {
    si->RegisterService(channelz_service_);
  }

  void Finish(grpc::ServerInitializer* ) override {}

  void ChangeArguments(const std::string& , void* ) override {}

  bool has_sync_methods() const override {
    if (channelz_service_) {
      return channelz_service_->has_synchronous_methods();
    }
    return false;
  }

  bool has_async_methods() const override {
    if (channelz_service_) {
      return channelz_service_->has_async_methods();
    }
    return false;
  }

 private:
  std::shared_ptr<grpc::ChannelzService> channelz_service_;
};

static std::unique_ptr<grpc::ServerBuilderPlugin>
CreateChannelzServicePlugin() {
  return std::unique_ptr<grpc::ServerBuilderPlugin>(
      new ChannelzServicePlugin());
}

void InitChannelzService() {
  static struct Initializer {
    Initializer() {
      grpc::ServerBuilder::InternalAddPluginFactory(
          &grpc::channelz::experimental::CreateChannelzServicePlugin);
    }
  } initialize;
}

}
}
}
