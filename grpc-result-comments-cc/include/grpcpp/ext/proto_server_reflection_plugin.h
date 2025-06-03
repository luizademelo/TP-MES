Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_EXT_PROTO_SERVER_REFLECTION_PLUGIN_H
#define GRPCPP_EXT_PROTO_SERVER_REFLECTION_PLUGIN_H

// Include necessary headers
#include <grpcpp/impl/server_builder_plugin.h>  // Base class for server builder plugins
#include <grpcpp/support/config.h>              // GRPC configuration support

#include <memory>  // For std::shared_ptr

// gRPC namespace
namespace grpc {
// Forward declarations
class ProtoServerReflection;
class ProtoServerReflectionBackend;
class ProtoServerReflectionV1;
class ServerInitializer;

// Reflection namespace
namespace reflection {

// Plugin class for Proto Server Reflection functionality
// Inherits from ServerBuilderPlugin to integrate with gRPC server builder
class ProtoServerReflectionPlugin : public grpc::ServerBuilderPlugin {
 public:
  // Constructor
  ProtoServerReflectionPlugin();

  // Returns the name of this plugin
  ::std::string name() override;

  // Initializes the server with reflection services
  void InitServer(ServerInitializer* si) override;

  // Cleans up when server initialization is complete
  void Finish(ServerInitializer* si) override;

  // Allows changing plugin arguments
  void ChangeArguments(const ::std::string& name, void* value) override;

  // Indicates if this plugin has asynchronous methods
  bool has_async_methods() const override;

  // Indicates if this plugin has synchronous methods
  bool has_sync_methods() const override;

 private:
  // Backend implementation for the reflection service
  std::shared_ptr<grpc::ProtoServerReflectionBackend> backend_;

  // Reflection service implementations for different versions
  std::shared_ptr<grpc::ProtoServerReflection> reflection_service_v1alpha_;
  std::shared_ptr<grpc::ProtoServerReflectionV1> reflection_service_v1_;
};

// Initialization function for the server reflection plugin
// Should be called to register the plugin with the ServerBuilder
void InitProtoReflectionServerBuilderPlugin();

}  // namespace reflection
}  // namespace grpc

#endif  // GRPCPP_EXT_PROTO_SERVER_REFLECTION_PLUGIN_H
```

The comments explain:
1. The purpose of each include directive
2. The overall structure and purpose of the class
3. The role of each public method (inherited from ServerBuilderPlugin)
4. The purpose of private member variables
5. The initialization function that needs to be called to use the plugin
6. Namespace organization

The comments are designed to help future developers understand:
- How this plugin integrates with gRPC's server builder system
- What functionality this plugin provides (server reflection)
- How to properly use and initialize the plugin
- The versioning scheme used for the reflection services