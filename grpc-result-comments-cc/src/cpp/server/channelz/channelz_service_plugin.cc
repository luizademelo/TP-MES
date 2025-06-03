Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Include necessary headers
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

// Plugin class for integrating ChannelzService with gRPC server
class ChannelzServicePlugin : public grpc::ServerBuilderPlugin {
 public:
  // Constructor initializes a new ChannelzService instance
  ChannelzServicePlugin() : channelz_service_(new grpc::ChannelzService()) {}

  // Returns the name of this plugin
  std::string name() override { return "channelz_service"; }

  // Registers the ChannelzService with the server during initialization
  void InitServer(grpc::ServerInitializer* si) override {
    si->RegisterService(channelz_service_);
  }

  // No-op implementation for Finish hook
  void Finish(grpc::ServerInitializer* ) override {}

  // No-op implementation for ChangeArguments hook
  void ChangeArguments(const std::string& , void* ) override {}

  // Checks if the service has synchronous methods
  bool has_sync_methods() const override {
    if (channelz_service_) {
      return channelz_service_->has_synchronous_methods();
    }
    return false;
  }

  // Checks if the service has asynchronous methods
  bool has_async_methods() const override {
    if (channelz_service_) {
      return channelz_service_->has_async_methods();
    }
    return false;
  }

 private:
  // Shared pointer to the ChannelzService instance
  std::shared_ptr<grpc::ChannelzService> channelz_service_;
};

// Factory function to create a new ChannelzServicePlugin instance
static std::unique_ptr<grpc::ServerBuilderPlugin>
CreateChannelzServicePlugin() {
  return std::unique_ptr<grpc::ServerBuilderPlugin>(
      new ChannelzServicePlugin());
}

// Initialization function for ChannelzService plugin
void InitChannelzService() {
  // Static initializer ensures registration happens only once
  static struct Initializer {
    Initializer() {
      // Register the plugin factory with ServerBuilder
      grpc::ServerBuilder::InternalAddPluginFactory(
          &grpc::channelz::experimental::CreateChannelzServicePlugin);
    }
  } initialize;
}

}  // namespace experimental
}  // namespace channelz
}  // namespace grpc
```

Key improvements made:
1. Added class-level comment explaining the purpose of ChannelzServicePlugin
2. Added detailed comments for each method explaining their functionality
3. Added comments for private member variables
4. Documented the factory function and initialization function
5. Added namespace closing comments for better readability
6. Explained the purpose of the static Initializer struct
7. Clarified no-op implementations where applicable

The comments now provide a clear understanding of:
- The plugin's role in the gRPC ecosystem
- How the service gets registered with the server
- The initialization process
- The method type detection functionality
- The ownership model of the ChannelzService instance